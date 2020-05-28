/* PINS Description 

Pin A1 - external sun sensor
Pin A4 - I2C - SDA
Pin A5 - I2C - SCL

Pin 1 - OneWire for DS11B20 - external temp sensor
Pin 3 - DHT11 temp and moisture sensor (NO 1 - internal)
Pin 5 - DHT11 temp and moisture sensor (NO 2 - external)

Pin 2 - Output for relay 3 (lamp near enter)
Pin 6 - Output for relay 1 (window lights - bell) switch PIN 
Pin 7 - Output for relay 2 (window lights - christmas tree) switch PIN  

Pin 4 - not work with Ethernet Shield!
Pin 10-13 - not allowed with Ethernet Shield!

*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "PCF8574.h" 
#include <SPI.h>
#include <OneWire.h>
#include "DHT.h"
#include <SPI.h>
#include <Ethernet.h>

#define BACKLIGHT_PIN 3
#define ONE_WIRE_BUS 2

OneWire  ds(1);
PCF8574 expander;
LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 0, 13);
EthernetServer server(80);

int d = 2;
int t1 = 0; // variable for temp sensor DHT 1 
int t2 = 0; // variable for temp sensor DHT 2 
int h1 = 0; // variable for temp sensor DHT 1 
int h2 = 0; // variable for temp sensor DHT 2 

int turn_on = 20;
int relayQty = 3;

int relay[][9] = {
    {0,    0,    0,    0,          0,    0,     0,    0,      0},
    {0,    1,    2,    turn_on,    0,    0,     6,    888,    0},
    {0,    2,    0,    turn_on,    0,    0,     7,    9,      0},
    {0,    3,    0,    turn_on,    0,    0,     2,    8,      0}
};

// innitial states
int p1 = 2;     //  state at na relay 1 (0 - off, 1 - on, 2 - auto)
int p2 = 0;     //  as above - relay 2
int p3 = 0;     //  as above - relay 3


void setup() {

    int i;
    
    lcd.begin (16, 2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home ();

    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip);
    server.begin();
    lcd.print(Ethernet.localIP());
    delay(1000);
    lcd.clear();

    

    for(i = 1; i <= relayQty; i++) {
        pinMode(relay[i][6], OUTPUT);
        if(relay[i][7] != 888) 
            pinMode(relay[i][7], INPUT_PULLUP); 
    }
   
    String readString;
}

void loop() {
    String readString;

    // read from DS11B20 (PIN 1) - BEGIN
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius, fahrenheit;
    if ( !ds.search(addr)) {
        ds.reset_search();
        return;
    }
    type_s = 0;
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);      
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);        
    for ( i = 0; i < 9; i++) {           
        data[i] = ds.read();
    }
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) {
        raw = raw << 3;
        if (data[7] == 0x10) {
            raw = (raw & 0xFFF0) + 12 - data[6];
        }
    } else {
        byte cfg = (data[4] & 0x60);
        if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    } 
 
    celsius = (float)raw / 16.0;
    lcd.setCursor(0, 0);
    lcd.print(celsius);
    // ------ read from DS11B20 - END --------
  
   
    // READ FROM SUN SENSOR (PIN A1)
    int swiatlo = analogRead(A1);
    int swiatlo1 = map(swiatlo, 0, 1023, 0, 100);
    lcd.setCursor(0, 1);
    lcd.print(swiatlo1);
    lcd.print("% ");
    // ----------- READ FROM SUN SENSOR --------- END

    // READ FORM SOIL MOISTURE SENSOR (PIN A2)
    int wilgGleby = analogRead(A2);
    int wilgGleby1 = map(wilgGleby, 0, 700, 0, 100);
    lcd.setCursor(4, 1);
    lcd.print(wilgGleby1);
    lcd.print("% ");
    // ----------- READ FORM SOIL MOISTURE SENSOR --------- END
   
    // READ FORM TEMP AND MOISTURE SENSOR - DHT (PIN 3 i 5) 
 
    for (i = 5; i >= 3; i--) {

        DHT dht(i, DHT11); 
        dht.begin();
        int t = dht.readTemperature();
        int h = dht.readHumidity();
        int a = 0;

        if (i == 5) { 
            a = 8; 
            t1 = t;
            h1 = h;
        }

        if (i == 4) { 
            a = 17; 
        }

        if (i==3) { 
            a = 12; 
            t2 = t;
            h2 = h;
        }

        lcd.setCursor(a, 0);
        lcd.print(t);
        lcd.print("'C");

        lcd.setCursor(a, 1);
        lcd.print(h);
        lcd.print("%");
    }
  
   
  
    for (i=1; i<=relayQty; i++) {

        if (relay[i][2] == 2) {  // check if auto mode is active for relay
            if(swiatlo1<=turn_on && relay[i][8] != 1 && relay[i][8] != 888) {  
                digitalWrite(relay[i][6], HIGH); 
            }
            if(swiatlo1>turn_on && relay[i][8] != 1 && relay[i][8] != 888) {
                digitalWrite(relay[i][6], LOW); 
            }
        }
 
        byte sw = 1;
        if (relay[i][7] != 888) {    //sprawdzenia czy dla przekaźnika dostepny jest switch
         
            if (digitalRead(relay[i][7]) == sw) {  //kontrola czy wcisnieto switch
                delay(20);
                boolean stan = digitalRead(relay[i][6]);
                stan =! stan;
                relay[i][8]++;
                digitalWrite(relay[i][6], stan);
                while(digitalRead(relay[i][7]) == sw)
                    delay(20);
            }
            if (relay[i][8] == 2) {
                relay[i][8] = 0;
            }
        }
    }

    EthernetClient client = server.available();
    
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) 
                char c = client.read();
            if (readString.length() < 100) {
                readString += c;     } 
            if (c == '\n' && currentLineIsBlank) {
                client.println("HTTP/1.1 200 OK Content-Type: text/html Connection: close");
                client.println();
                client.println("<!DOCTYPE HTML>");
                client.println("<html>");
                client.print("Tz1: <b>");
                client.print(celsius);
                client.print("'C ");
                client.print("</b>");
                client.print("Tz2: <b>");
                client.print(t1);
                client.print("'C ");
                client.print("</b>Wz: <b>");
                client.print(h1);
                client.print("% ");
                client.print("</b>");
                client.print("N: <b>");
                client.print(swiatlo1);
                client.print("% ");
                client.print("</b><br>");
                client.print("Tw: <b>");
                client.print(t2);
                client.print("'C ");
                client.print("</b>");
                client.print("Ww: <b>");
                client.print(h2);
                client.print("% ");
                client.print("</b>");
                client.print("Wch: <b>");
                client.print(wilgGleby1);
                client.print("% ");
                client.print("</b>");
                client.print("<br>P: <b>1 (o)</b> S: <b>");
                byte d = digitalRead(relay[1][6]);
                client.print(d);
                client.print(" </b>T: <b>");
                client.print(relay[1][2]);
                client.print("</b><a href=\"/?p1_off\"\"> 0  </a><a href=\"/?p1_on\"\">1</a><a href=\"/?p1_auto\"\"> A </a>"); 
                client.print("</b><br>P: <b>2 (l ok)</b> S: <b>");
                d = digitalRead(relay[2][6]);
                client.print(d);
                client.print("</b> T: <b>");
                client.print(relay[2][2]);
                client.print("</b><a href=\"/?p2_off\"\"> 0 </a><a href=\"/?p2_on\"\">1</a><a href=\"/?p2_auto\"\"> A </a>"); 
                client.print("</b><br>P: <b>3 (l dz)</b> S: <b>");
                d = digitalRead(relay[3][6]);
                client.print(d);
                client.print(" </b>T: <b>");
                client.print(relay[3][2]);
                client.print("</b><a href=\"/?p3_off\"\"> 0 </a><a href=\"/?p3_on\"\">1</a><a href=\"/?p3_auto\"\"> A </a><br>"); 
                client.print("<a href=\"http://192.168.0.13\">L </a>"); 
                client.print("<a href=\"http://89.79.164.123\">Z</a>"); 
                client.println("</html>");
                break;
            }
            if (c == '\n') {
                currentLineIsBlank = true;
            } 
            else if (c != '\r') {
                currentLineIsBlank = false;
            }
        }
    }
   
    delay(1);
    client.stop();
 
    // setting relay 1
    if(readString.indexOf("?p1_on") >0) {
        digitalWrite(relay[1][6], HIGH); 
        relay[1][2] = 1;
    }
    if(readString.indexOf("?p1_off") >0){
        digitalWrite(relay[1][6], LOW); 
        relay[1][2] = 0;
    }
    if(readString.indexOf("?p1_auto") >0) {
        relay[1][2] = 2;
    }
    
    // setting relay 2
    if(readString.indexOf("?p2_on") >0) {
        digitalWrite(relay[2][6], HIGH); 
        relay[2][2] = 1;
    }
    if(readString.indexOf("?p2_off") >0){
        digitalWrite(relay[2][6], LOW); 
        relay[2][2] = 0;
    }
    if(readString.indexOf("?p2_auto") >0) {
        relay[2][2] = 2;
    }
    
    // setting relay 3
    if(readString.indexOf("?p3_on") >0) {
      digitalWrite(relay[3][6], HIGH); 
      relay[3][2] = 1;
    }
    if(readString.indexOf("?p3_off") >0){
      digitalWrite(relay[3][6], LOW); 
      relay[3][2] = 0;
    }
    if(readString.indexOf("?p3_auto") >0) {
      relay[3][2] = 2;
    }

    readString="";

}



