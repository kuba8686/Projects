// -- Expander pinów --
#include <Wire.h>
#include "PCF8574.h"
PCF8574 expander;

// -- DS11B20 --
#include <SPI.h>
#define ONE_WIRE_BUS 2
#include <OneWire.h>
OneWire  ds(10); // thermometer pin

// -- Basic Variables --

unsigned long basic_length = 20;         
int average_meas_time = 42;   

// -- Additional Variables --
int pins[14];  
int pin = 0;
float average[2] = {0,0};
float average_fin = 0;
unsigned long timeZero = 0; 
unsigned long timeNext = 0; 
unsigned long timeHlp = 0;
int init_hlp = 1;


void setup() {
  
    expander.begin(0x20);      

    // -- LED indicator pins -- 
    pins[0] = 12;
    pins[1] = 9;
    pins[2] = 6;
    pins[3] = 4;
    pins[4] = 3;
    pins[5] = 0;
    pins[6] = 1;
    pins[7] = 2;
    pins[8] = 5;
    pins[9] = 7;
    pins[10] = 17;
    pins[11] = 16;
    pins[12] = 15;
    pins[13] = 14;
    pins[14] = 13;
    // -- end

    // -- set Arduino PIN's mode:
    //LED
    for (int i=0; i<=14; i++) {  // diody LED, HIGH - dioda się pali, LOW - zgaszona
        pin = pins[i];
        pinMode(pin, OUTPUT);
    }
    
    //* seg digits
    pinMode(11,OUTPUT);     //dozens
    pinMode(8,OUTPUT);      //unity

    //EXPANDER
    for (int i=0; i<=7; i++) {  
        expander.pinMode(i, OUTPUT);
    }
    // -- end

    // -- Initial sequence (once) --

    //LED and digits test - ALL ON na dor 1 sec.
    all(pins,1,1);  
    delay(1000);
    all(pins,0,1);  //turn off

    pinMode(13, INPUT_PULLUP); 
    // alternative serial port mode on
    if (digitalRead(13) == HIGH) {
        Serial.begin(9600);
        delay(1000);
    }
    pinMode(13, OUTPUT);
}
   
void(* resetFunc)(void) = 0;  //reset function

void loop() {

Serial.println("TEST");

    // -- initialization, tmp_statedby mode --

    init_mode(60,333); 

    // --- Measure mode --

    pisk(100, 100, 4); 

    timeZero = millis()/1000;  
   
    for (int dioda; dioda<=14; dioda++) { 
        timeHlp = dioda*basic_length + basic_length;
        timeNext = millis()/1000 - timeZero;

        while (timeHlp > timeNext) {
      
            int t = temp();
            if (t < 60) {
            show_at_dig(t,1,0);
            }

            if (timeNext > average_meas_time) {  
                average[0] = average[0] + t;
                average[1] = average[1] + 1;
                average_fin = average[0] / average[1];
                show_at_dig(average_fin,1,1);
            } 
            Serial.print("temp:, ");
            Serial.print(t);
            Serial.print(",average temp: ,");
            Serial.print(average_fin);
            Serial.println(" ");

            timeNext = millis()/1000 - timeZero; 
        }

        digitalWrite(pins[dioda], HIGH);
    }


// --- End seq  --

  
    for (int i = 0; i<=10; i++) {  
        float t = 0.5;  
        all(pins,1,0);
        show_at_dig(average_fin,t,1);
        all(pins,0,0);
        show_at_dig(average_fin,t,1);
    }

    show_at_dig(average_fin,60,1);  

    average_fin = 0;   
    average[0] = 0;
    average[1] = 0;
    init_hlp = 0; 
        
    Serial.println("<-- Koniec -->");

          Serial.print("average temp:");
          Serial.print(average_fin);
          Serial.println(" ");

}



void switchStop(int p, byte tmp_state) { 
  
    pinMode(p, INPUT_PULLUP);  
    digitalWrite(p, LOW); 
    while (digitalRead(p) == tmp_state) {
        delay(10);
    } 
    pinMode(p, OUTPUT);   
    digitalWrite(p, LOW); 
}

void all(int pins[], byte tmp_state, byte cyfry) { 
    for (int i=0; i<=15; i++) {
        digitalWrite(pins[i], tmp_state);
    }
    digitalWrite(13, tmp_state);  //huj wie czemu pin 13 sie nie chce zapalić
    if (cyfry == 1) {
        tmp_state = !tmp_state;
        for (int i=0; i<=7; i++) {  
            expander.digitalWrite(i,tmp_state);
        }
        digitalWrite(8, HIGH);
        digitalWrite(11, HIGH);
    }
}


void show_at_dig (int digit_inp, float basic_length, int dot) {

int s = (basic_length * 200) / 2;

    for (int r = 0; r<=s; r++) {
        if (digit_inp > 0) {

            int j = digit_inp % 10;;
            int d = (digit_inp % 100)/10;

            digitalWrite(11,HIGH);
            digitalWrite(8,LOW);

            digit(d);
            delay(1);

            for(int a = 0; a <= 7; a++) {
                expander.digitalWrite(a,HIGH);
            }

            digitalWrite(11,LOW);
            digitalWrite(8,HIGH);
            digit(j);
            
            if (dot == 1) {
                expander.digitalWrite(0,LOW);
            }
            delay(1);

            for(int a = 0; a <= 7; a++) {
                expander.digitalWrite(a,HIGH);
            }

        } else {
            digitalWrite(11,HIGH);
            digitalWrite(8,LOW);

            digit(11);
            delay(1);

            for(int a=0; a<=7; a++) {
                expander.digitalWrite(a,HIGH);
            }


            digitalWrite(11,LOW);
            digitalWrite(8,HIGH);
            digit(12);
            if (dot==1) {
              expander.digitalWrite(0,LOW);
            }
            delay(1);


            for(int a=0; a<=7; a++) {
                expander.digitalWrite(a,HIGH);
            }
        }

    }
          
}


void digit(int i) {

  if (i==1) {
    expander.digitalWrite(1,LOW);
    expander.digitalWrite(5,LOW);
  }

  if (i==2) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(4,LOW);
    expander.digitalWrite(3,LOW);
  }

  if (i==3) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(1,LOW);
  }

  if (i==4) {
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(1,LOW);
  }

  if (i==5) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(1,LOW);
  }

  if (i==6) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(4,LOW);
    expander.digitalWrite(1,LOW);
    expander.digitalWrite(3,LOW);
  }

  if (i==7) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(1,LOW);
  }

  if (i==8) {
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(1,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(4,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(7,LOW);
  }

  if (i==9) {
    expander.digitalWrite(1,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(5,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(7,LOW);
  }

  if (i==0) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(4,LOW);
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(1,LOW);
    expander.digitalWrite(5,LOW);
  }

  
  if (i==11) {
    expander.digitalWrite(7,LOW);
    expander.digitalWrite(6,LOW);
    expander.digitalWrite(2,LOW);
    expander.digitalWrite(3,LOW);
    expander.digitalWrite(4,LOW);
  }
  if (i==12) {
    expander.digitalWrite(4,LOW);
    expander.digitalWrite(2,LOW);

  }


}

int temp() {
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    float celsius, fahrenheit;
    
    if ( !ds.search(addr)) {
        ds.reset_search();
        delay(10);
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
        if (cfg == 0x00) raw = raw & ~7; 
        else if (cfg == 0x20) raw = raw & ~3; 
        else if (cfg == 0x40) raw = raw & ~1; 
    }

    celsius = (float)raw / 16.0;
    celsius = (int)celsius;

    return celsius;

}

int temp_init() {
    
    byte i;
    byte present = 0;
    byte type_s;
    byte data[12];
    byte addr[8];
    
    float celsius, fahrenheit;
    
    if ( !ds.search(addr)) {
        ds.reset_search();
        delay(10);
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
        if (cfg == 0x00) raw = raw & ~7; 
        else if (cfg == 0x20) raw = raw & ~3; 
        else if (cfg == 0x40) raw = raw & ~1; 
    }

    celsius = (float)raw / 16.0;
    celsius = (int)celsius;

    return celsius;

}

void init_mode(int measQty, int measTime ) {  
      
    int t_pom = 0;
    int measQty_pom = measQty + 1;
    int init_mode[measQty_pom];  
    
    for (int i = 0; i<measQty_pom; i++) {
        init_mode[i] = 0;
    }
    
    int x = 1;

    while(x<=measQty)  {
        digitalWrite(2, HIGH); 

        int t = temp_init(); 
        if (t>0 && t<70) {
            init_mode[x] = t; 
        } else {
            init_mode[x] = 0;
        }

        if (x>1) { 
            t_pom = init_mode[x] - init_mode[1]; 
            if (t_pom >= 2) {  
                if (init_hlp == 1) {  
                    digitalWrite(2, LOW);  
                    break; 
                }
            }
        }
        
        // standby mode
        pinMode(13, INPUT_PULLUP);  
        digitalWrite(13, LOW);  
        if (digitalRead(13) == HIGH ) {  
            pinMode(13, OUTPUT); 
            digitalWrite(2, LOW);
            for (int i = 0; i<=measQty_pom; i++) {  
                init_mode[i] = 0;
            }
            break;
        }

        pinMode(13, OUTPUT); 
        x++;
        if (x > measQty) {  
            x = 1;
            init_hlp = 1;
        }

        delay(measTime);

        Serial.print("lp:,");
        Serial.print(x);
        Serial.print(",temp:,");
        Serial.print(t);
        Serial.print(",czas:,");
        unsigned long xxx = millis();
        Serial.print(xxx);
        Serial.println(" ");

        if (millis() > 86400000) {   // reset układu co 24 godziny
            resetFunc();
        }
    }
}

void pisk(int dp, int dd, int p) {
    for (int i = 1; i<=p; i++) {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        delay(dp);
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        delay(dd);
    }
}
