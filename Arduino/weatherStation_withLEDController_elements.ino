#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// -- LED RGB --
#include <PololuLedStrip.h>
PololuLedStrip<10> ledStrip;  // PIN for RGB Led
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

// -- LCD Screen --
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN 3
LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

// -- DHT 11 --
#include "DHT.h"

// -- DS11B20 --
#include <SPI.h>
#define ONE_WIRE_BUS 2
#include <OneWire.h>
OneWire  ds(2);

// variable for control

int RGB_dark = 255;  
int LCD_dark = 30;  

// ancillary variables

byte stat = 1;
byte lcd_shOn = 0;
int lcd_count = 1;
float celsius = 999;
float celsius_temp = -7;
float y;
int maxx;  


void setup() {
    
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  
  lcd.begin (16, 2);
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();
  lcd.setCursor(0, 0);
  lcd.print("I:");
  lcd.setCursor(7, 0);
  lcd.print("O:");

}



void loop() {
  
 
  // -- lcd brightness control 
  while (digitalRead(6) == HIGH) {
       lcd_shOn = 1;
       delay(20);
  }
  if (lcd_shOn == 1) {
      analogWrite(5, 1023);
      maxx = 255;
      lcd_count++;
      if (lcd_count >= 10) {
         lcd_shOn = 0; 
         lcd_count = 0;
      }
  }
  if (lcd_shOn == 0) {
      analogWrite(5, LCD_dark);
      maxx = RGB_dark;
  }
  

  
  // -- lcd blink - signal for proper working
  stat = !stat;
  if (stat == 1) {
    lcd.setCursor(15, 1);
    lcd.print("*");
  }
  if (stat == 0) {
    lcd.setCursor(15, 1);
    lcd.print(" ");
  }
  
  // -- signals fron DHT 11 --  
    for (int i = 3; i<=4; i++) {

      DHT dht(i, DHT11); 
      dht.begin();
      int t = dht.readTemperature();
      int h = dht.readHumidity();
      if (i==3) {

          lcd.setCursor(6, 0);
          lcd.print(t);
          lcd.print("C ");
          lcd.setCursor(2, 0);
          lcd.print(h);
          lcd.print("%");

      }
      if (i==4) {
        lcd.setCursor(3, 0);
        lcd.print(t);
        lcd.print("C ");
        lcd.setCursor(3, 1);
        lcd.print(h);
        lcd.print("%");
      }
    }
      
      
  // -- end --
     
  // -- signal from DS11B20 --
      
      byte i;
      byte present = 0;
      byte type_s;
      byte data[12];
      byte addr[8];
      float celsius, fahrenheit;
      if ( !ds.search(addr)) {
        ds.reset_search();
        //delay(250);
        return;
      }
      type_s = 0;
      ds.reset();
      ds.select(addr);
      ds.write(0x44, 1);      
      //.delay(200); 
      present = ds.reset();
      ds.select(addr);    
      ds.write(0xBE);        
      for ( i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = ds.read();
      }
      int16_t raw = (data[1] << 8) | data[0];
      if (type_s) {
        raw = raw << 3; // 9 bit resolution default
        if (data[7] == 0x10) {
          // "count remain" gives full 12 bit resolution
          raw = (raw & 0xFFF0) + 12 - data[6];
        }
      } else {
        byte cfg = (data[4] & 0x60);
        // at lower res, the low bits are undefined, so let's zero them
        if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
        //// default is 12 bit resolution, 750 ms conversion time
      } 
     
        celsius = (float)raw / 16.0;
       
        bright_temp(celsius);
        
        if (celsius != 999) {
          if (celsius <= -10) {
            lcd.setCursor(9, 0);  
          }
          if (celsius > -10 && celsius <=0) {
            lcd.setCursor(9, 0);
            lcd.print(" ");
            lcd.setCursor(10, 0);  
          }
          if (celsius >= 0 && celsius <=10) {
            lcd.setCursor(9, 0);
            lcd.print("  ");
            lcd.setCursor(11, 0);  
          }
          if (celsius >= 10) {
            lcd.setCursor(9, 0);
            lcd.print(" ");
            lcd.setCursor(10, 0);  
          }
          
           lcd.print(celsius);
           lcd.print("C");
        } else {
          lcd.setCursor(9, 0);
          lcd.print("  ");
          lcd.setCursor(11, 0);
          lcd.print("Blad!");
        }
        
        
//   -- end --
        
        celsius = 999;

}

void bright_temp(float temp) {


   if (temp>=32) {
      Serial.println(temp);
      len_on_b(maxx,0,0);
   }
   if (temp<32 && temp >=25) {
      Serial.println(temp);
      temp=temp*10;
      y = map(temp, 250, 320, maxx, 0);
      len_on_b(maxx,y,0);
   }
   if (temp<25 && temp >=16) {
      Serial.println(temp);
      temp=temp*10;
      y = map(temp, 160, 250, 0, maxx);
      len_on_b(y,maxx,0);
   }
   if (temp<16 && temp >=0) {
      Serial.println(temp);
      temp=temp*10;
      y = map(temp, 0, 80, maxx, 0);
      int x = map(temp, 80, 160, maxx, 0);
      if (temp<=80) {
        x=maxx;
      }
      if (temp>=80) {
        y=0;
      }
      len_on_b(x,maxx-y,0.75*x);
   }
   if (temp<0 && temp >=-5) {
      Serial.println(temp);
      y = map(temp, -5, 0, 0, maxx);
      len_on_b(0,y,maxx);
   }
   if (temp<-5) {
      Serial.println(temp);
      len_on_b(0,0,maxx);
   }
  
}

void len_on_b(int r, int g, int b) {
    rgb_color color;
    color.red = g;
    color.green = r;
    color.blue = b;

    colors[0] = color;
    colors[1] = color;
    colors[2] = color;
    colors[3] = color;

    ledStrip.write(colors, LED_COUNT);
}
