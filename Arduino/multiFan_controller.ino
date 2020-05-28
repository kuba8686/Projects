#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_I2C_ByVac.h>
#include <LiquidCrystal_SI2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR1W.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <SI2CIO.h>
#include <SoftI2CMaster.h>
#include <Wire.h>
#include <PCF8574.h>
#include <SPI.h>
#include "DHT.h"

#define BACKLIGHT_PIN 3
#define ONE_WIRE_BUS 2

LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7);
PCF8574 expander1;     
PCF8574 expander2;
PCF8574 expander3;
PCF8574 expander4;

String readString;

/* defining innitial parameters */
int t_sensor =   30;        /* sensors quantity */
float mode_on =  2;         /* fun on time [sek] - during normal mode */
float tempLimit_HIGH = 28;  /* temp - when fun starts */
float tempLimit_LOW = 25;   /* temp - when fun stops */
float testDelayOn = 1;      /* fun on time [sek] - during test mode */
float testDelayOff = 1;     /* delay after next fun starts to run during test mode */

/* defining PIN's */
int PrimaryPin = 22;        /* pin where first fun is connected, have to be even! */
int ledSensorFailure = 8;   /* LED indicator for failure - RED */
int ledNormalMode = 9;      /* LED indicator for normal mode - GREEN */
int ledTest = 10;           /* LED indicator dor test mode - BLUE */
int pinTest = 11;           /* pin for switch to make fun - all on */
int pinTestt_sensori = 12;  /* pin for temperature sensor test */

/* ancillary variable's */

int t_sensorConst = t_sensor;
int t_sensorTemp = t_sensor;
int PrimaryPinConst = PrimaryPin;
int PrimaryPinTemp = PrimaryPin;
bool t_sensorOverheat = 0;  /* var for overheating, true = overheating */


bool sensor_test = 0;       /* false - sensor efficient; true - sensor failure */
int sensorError = 0;        /* equals 1 if at least one sensor is failure */
int t_sensorLedOn;    

int expanderInfo[40][5];

void expanderConf() {

    if (t_sensorConst >= 1) {
        expander1.begin(0x20);
        for ( int i = 0; i <= 7; i++) {
            expander1.pinMode(i, OUTPUT);
        }
    }
    if (t_sensorConst >= 9) {
        expander2.begin(0x21);
        for ( int i = 0; i <= 7; i++) {
            expander2.pinMode(i, OUTPUT);
        }
    }
    if (t_sensorConst >= 18) {
        expander3.begin(0x22);
        for ( int i = 0; i <= 7; i++) {
            expander3.pinMode(i, OUTPUT);
        }
    }
    if (t_sensorConst >= 25) {
        expander4.begin(0x23);
        for ( int i = 0; i <= 7; i++) {
            expander4.pinMode(i, OUTPUT);
        }
    }
      
    expander4.enableInterrupt(4, onInterrupt);

    expander1.set();
    expander2.set();
    expander3.set();
    expander4.set();
}

void onInterrupt()
{
    expander1.checkForInterrupt();
}

void sensor_testFnc() {

    int t_sensorTestC = t_sensorConst;
    int PrimaryPinTestC = PrimaryPinConst;
    int channel;
    float t;
    
    digitalWrite(ledNormalMode, LOW);
    digitalWrite(ledSensorFailure, HIGH);
    digitalWrite(ledTest, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("TEST:t_sensoriEr:");
    lcd.setCursor(0, 1);
  
    while (2 > 1) {
        while (t_sensorTestC > 0) {
            /* green led blinking when test mode on */
            if (t_sensorTestC % 2 == 0) { 
                digitalWrite(ledSensorFailure, LOW);
                digitalWrite(ledTest, LOW);
            }

            DHT dht(PrimaryPinTestC, DHT11);
            dht.begin(); 

            channel = abs(t_sensorTestC - (t_sensorConst + 1));
            t = dht.readTemperature();  /* reat temperature */

            Serial.println(t);

            if (isnan(t)) {
                digitalWrite(PrimaryPinTestC - 1, LOW);
                lcd.print(channel);
                lcd.print(",");
            } else {
                digitalWrite(PrimaryPinTestC - 1, HIGH);
            }

            t_sensorTestC--;     // informacje do kolejnej pÄ™tli while
            PrimaryPinTestC++;
            delay(0);

            digitalWrite(ledSensorFailure, HIGH);
            digitalWrite(ledTest, HIGH);
        }
        break;
    }
  
    while (2 > 1) {
        digitalWrite(ledTest, HIGH);

        if (digitalRead(pinTestt_sensori) == LOW) {
            PrimaryPinTestC = PrimaryPinConst;
            t_sensorTestC = t_sensorConst;
            for ( int i = 1; i <= t_sensorTestC; i++) {
                digitalWrite(PrimaryPinTestC, LOW);
                digitalWrite(ledTest, LOW);
                PrimaryPinTestC = PrimaryPinTestC + 2;
            }
          delay(400);
          break;
        }
    }
    lcd.clear();
}

void temperaturat_sensor () {

    int channel;
    float t;
    
    for ( int i = 0; i <= t_sensorConst; i++) {
        expanderInfo[i][0] = 0;
        expanderInfo[i][1] = i;
        expanderInfo[0][2] = 0;
        expanderInfo[0][3] = 0;
        expanderInfo[0][4] = 0;
        
        if (i >= 1 && i <= 8)
            expanderInfo[i][2] = 1;
        if (i >= 9 && i <= 16 && t_sensorConst > 8)
            expanderInfo[i][2] = 2;
        if (i >= 17 && i <= 24 && t_sensorConst > 12) 
            expanderInfo[i][2] = 3;
        if (i >= 25 && i <= 30 && t_sensorConst > 16)
            expanderInfo[i][2] = 4;
    }
    for ( int i = 0; i <= (t_sensorConst / 8 + 1); i++) {
        expanderInfo[1 + 8 * i][3] = 0;
        expanderInfo[2 + 8 * i][3] = 1;
        expanderInfo[3 + 8 * i][3] = 2;
        expanderInfo[4 + 8 * i][3] = 3;
        expanderInfo[5 + 8 * i][3] = 4;
        expanderInfo[6 + 8 * i][3] = 5;
        expanderInfo[7 + 8 * i][3] = 6;
        expanderInfo[8 + 8 * i][3] = 7;
    }
  
    PrimaryPinTemp = PrimaryPinConst;
    t_sensorTemp = t_sensorConst;     
  
    while (t_sensorTemp > 0) {
        channel = abs(t_sensorTemp - (t_sensorConst + 1));
        if (t_sensorTemp % 2 == 0) 
          digitalWrite(ledNormalMode, LOW);

        DHT dht(PrimaryPinTemp, DHT11);
        dht.begin(); 

        t = dht.readTemperature();  
    }
   
    /* establish if sensor failure */
    if (isnan(t)) {
        sensor_test = 1;
        sensorError = sensor_test;
        digitalWrite(ledSensorFailure, HIGH);
        digitalWrite(ledNormalMode, LOW);
    } else {
        sensor_test = 0;
    }

    /* establish if overheat */
    if (t > tempLimit_HIGH || expanderInfo[channel][4] == 1) {
        t_sensorOverheat = 1;
        expanderInfo[channel][4] = 1;
    }
    if (t < tempLimit_HIGH && expanderInfo[channel][4] == 1) {
        t_sensorOverheat = 1;
    }
    if (t < tempLimit_LOW) {
      t_sensorOverheat = 0;
      expanderInfo[channel][4] = 0;
    }

    /* if not failure - RED LED off, GREEN LED on */
    if (sensorError == 0) {         
        digitalWrite(ledSensorFailure, LOW);
        digitalWrite(ledNormalMode, HIGH);
    }

    if (t_sensorOverheat == 1 || sensor_test == 1) { 
        if (expanderInfo[channel][2] == 1) {
            expander1.digitalWrite(expanderInfo[channel][3], LOW);
        }
        if (expanderInfo[channel][2] == 2) {
            expander2.digitalWrite(expanderInfo[channel][3], LOW);
        }
        if (expanderInfo[channel][2] == 3) {
            expander3.digitalWrite(expanderInfo[channel][3], LOW);
        }
        if (expanderInfo[channel][2] == 4) {
            expander4.digitalWrite(expanderInfo[channel][3], LOW);
        }
    }
    
    if (t_sensorTemp != t_sensor && t_sensorOverheat == 0 && sensor_test == 0) {  
        if (expanderInfo[channel][2] == 1) {
            expander1.digitalWrite(expanderInfo[channel][3], HIGH);
        }
        if (expanderInfo[channel][2] == 2) {
            expander2.digitalWrite(expanderInfo[channel][3], HIGH);
        }
        if (expanderInfo[channel][2] == 3) {
            expander3.digitalWrite(expanderInfo[channel][3], HIGH);
        }
        if (expanderInfo[channel][2] == 4) {
           expander4.digitalWrite(expanderInfo[channel][3], HIGH);
        }
    }
    
    if (t_sensorTemp == t_sensor && (t_sensorOverheat == 1 || sensor_test == 1)) {
        t_sensorLedOn = 1;
    }
    
    if (t_sensorTemp == t_sensor) {
        lcd.setCursor(0, 1);
        lcd.print("K:");
        lcd.print(channel);
        lcd.print(" T:");
        lcd.print(t);
        lcd.print(" C  ");
        lcd.setCursor(15, 1);
        if (t_sensorOverheat == 1 || sensor_test == 1) {
            lcd.print("**");
        } else {
            lcd.print("  ");
        }
    }

    t_sensorTemp--;
    PrimaryPinTemp++;


    /* set RGB LED and LCD due to tests result and t_sensor's */
    if (sensorError == 0) {   // bez bĹ‚Ä™dĂłw - dioda zielona ON, czerwona OFF
        digitalWrite(ledSensorFailure, LOW);
        digitalWrite(ledNormalMode, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Normal Mode    ");
    } else {                    // bĹ‚Ä™dy - dioda czerwona ON, zielona OFF
        digitalWrite(ledSensorFailure, HIGH);
        digitalWrite(ledNormalMode, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Tryb Awaryjny !");
    }
}
  
void test() {
    
    int PrimaryPinTest = PrimaryPinConst;
    int t_sensorTest = t_sensorConst;
    int i;
    
    lcd.clear();
    lcd.print("TEST: All ON    ");

    digitalWrite(ledNormalMode, LOW);
    digitalWrite(ledSensorFailure, LOW);
    
    while (2 > 1) {
        for (i = 1; i <= t_sensorTest; i++) {
            if (expanderInfo[i][2] == 1) {
                expander1.digitalWrite(expanderInfo[i][3], LOW);
            }
            if (expanderInfo[i][2] == 2) {
                expander2.digitalWrite(expanderInfo[i][3], LOW);
            }
            if (expanderInfo[i][2] == 3) {
                expander3.digitalWrite(expanderInfo[i][3], LOW);
            }
            if (expanderInfo[i][2] == 4) {
              expander4.digitalWrite(expanderInfo[i][3], LOW);
            }
        
            digitalWrite(ledTest, HIGH);
            delay(150);
            digitalWrite(ledTest, LOW);
            PrimaryPinTest = PrimaryPinTest + 2;
            delay(testDelayOn * 1000 - 150);
        }
    
        digitalWrite(ledTest, HIGH);
        PrimaryPinTest = PrimaryPinConst;
        
        while (2 > 1) {
            if (digitalRead(pinTest) == LOW) {
                break;
            }
        }

        digitalWrite(ledTest, LOW);
    
        for (i = 1; i <= t_sensorTest; i++) {
            if (expanderInfo[i][2] == 1) {
                expander1.digitalWrite(expanderInfo[i][3], HIGH);
            }
            if (expanderInfo[i][2] == 2) {
                expander2.digitalWrite(expanderInfo[i][3], HIGH);
            }
            if (expanderInfo[i][2] == 3) {
                expander3.digitalWrite(expanderInfo[i][3], HIGH);
            }
            if (expanderInfo[i][2] == 4) {
                expander4.digitalWrite(expanderInfo[i][3], HIGH);
            }
            digitalWrite(ledTest, HIGH);
            delay(150);
            digitalWrite(ledTest, LOW);
            PrimaryPinTest = PrimaryPinTest + 2;
            delay(testDelayOff * 1000 - 150);
        }
        PrimaryPinTest = PrimaryPinConst;
        digitalWrite(ledNormalMode, HIGH);
        break;
    }
    lcd.clear();
}

void calib_mode() {
  
    int t_sensorAnalog;
    int t_sensorConstMap;
    int modeOnAnalog;
    int mode_onMap;
    int tempLimit_HIGHAnalog = analogRead(A5);
    int tempLimit_HIGHMap = map(tempLimit_HIGHAnalog, 20, 990, 25, 60);
    int tempLimit_LOWAnalog = analogRead(A4);
    int tempLimit_LOWMap = map(tempLimit_LOWAnalog, 20, 990, 20, 40);
    digitalWrite(ledTest, HIGH);
    digitalWrite(ledSensorFailure, HIGH);
    digitalWrite(ledNormalMode, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("calib_mode");
    delay(1000);
    lcd.clear();
  
    while (2 > 1) {
          
        t_sensorAnalog = analogRead(A2);
        t_sensorConstMap = map(t_sensorAnalog, 20, 990, 2, 30);
        modeOnAnalog = analogRead(A3);
        mode_onMap = map(modeOnAnalog, 20, 990, 5, 60);
        tempLimit_HIGHAnalog = analogRead(A5);
        tempLimit_HIGHMap = map(tempLimit_HIGHAnalog, 20, 990, 25, 60);
        tempLimit_LOWAnalog = analogRead(A4);
        tempLimit_LOWMap = map(tempLimit_LOWAnalog, 20, 990, 20, 40);
        
        lcd.print("CZ: Dl: tL: tH:");
        lcd.setCursor(0, 1);
        lcd.print(t_sensorConstMap);
        lcd.print("  ");
        lcd.setCursor(4, 1);
        lcd.print(mode_onMap);
        lcd.print("   ");
        lcd.setCursor(8, 1);
        lcd.print(tempLimit_LOWMap);
        lcd.print("  ");
        lcd.setCursor(12, 1);
        lcd.print(tempLimit_HIGHMap);
        lcd.print("  ");

        delay(100);

        t_sensorConst = t_sensorConstMap;
        
        if (t_sensorConstMap>30) {
          t_sensorConst = 30;
        }
        
        t_sensorTemp = t_sensorConstMap;
        mode_on = mode_onMap;
        tempLimit_HIGH = tempLimit_HIGHMap - 1;
        tempLimit_LOW = tempLimit_LOWMap + 1;
       
        if (digitalRead(pinTest) == LOW) {
            
            lcd.clear();
            lcd.print("Ladowanie");
            delay(2500);
            lcd.clear();
            break;
        }

    }

    digitalWrite(ledTest, LOW);
    digitalWrite(ledSensorFailure, LOW);
    digitalWrite(ledNormalMode, LOW);
  
}


void setup() {

    int i;
    int wynikOverheat[t_sensorConst + 1];

    lcd.begin (16, 2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home ();

    pinMode(pinTest, INPUT_PULLUP);
    pinMode(pinTestt_sensori, INPUT_PULLUP);
    pinMode(ledTest, OUTPUT);
    pinMode(ledSensorFailure, OUTPUT);
    pinMode(ledNormalMode, OUTPUT);

    calib_mode();

    expanderConf();
  
    for (i = 0; i <= (t_sensorConst / 8 + 1); i++) {
        expanderInfo[1 + 8 * i][4] = 0;
        expanderInfo[2 + 8 * i][4] = 0;
        expanderInfo[3 + 8 * i][4] = 0;
        expanderInfo[4 + 8 * i][4] = 0;
        expanderInfo[5 + 8 * i][4] = 0;
        expanderInfo[6 + 8 * i][4] = 0;
        expanderInfo[7 + 8 * i][4] = 0;
        expanderInfo[8 + 8 * i][4] = 0;
    }

    digitalWrite(ledNormalMode, HIGH);
    Serial.begin(9600); // inicjujemy poĹ‚Ä…czenie szeregowe

    t_sensor = t_sensorConst;
    PrimaryPin = PrimaryPinConst;
}

void loop() {

    float ZmDelay;
    int tchannel = PrimaryPin - PrimaryPinConst + 1;
    
    while (t_sensor > 0) {
        if (digitalRead(pinTest) == LOW) {
            test();
            break;
        }

        if (digitalRead(pinTestt_sensori) == LOW) {
            sensor_testFnc();
            break;
        }

        if (expanderInfo[tchannel][2] == 1) {
            expander1.digitalWrite(expanderInfo[tchannel][3], LOW);
        }
        if (expanderInfo[tchannel][2] == 2) {
            expander2.digitalWrite(expanderInfo[tchannel][3], LOW);
        }
        if (expanderInfo[tchannel][2] == 3) {
            expander3.digitalWrite(expanderInfo[tchannel][3], LOW);
        }
        if (expanderInfo[tchannel][2] == 4) {
            expander4.digitalWrite(expanderInfo[tchannel][3], LOW);
        }
         
        temperaturat_sensor();

        ZmDelay = mode_on * 1000 - t_sensorConst * 250;
        
        if (ZmDelay < 0) {
            ZmDelay = 0;
        }
        
        delay(ZmDelay);
        
        if (t_sensorLedOn == 0) {
            if (expanderInfo[tchannel][2] == 1) {
                expander1.digitalWrite(expanderInfo[tchannel][3], HIGH);
            }
            if (expanderInfo[tchannel][2] == 2) {
                expander2.digitalWrite(expanderInfo[tchannel][3], HIGH);
            }
            if (expanderInfo[tchannel][2] == 3) {
                expander3.digitalWrite(expanderInfo[tchannel][3], HIGH);
            }
            if (expanderInfo[tchannel][2] == 4) {
                expander4.digitalWrite(expanderInfo[tchannel][3], HIGH);
            }
        }
        t_sensorLedOn = 0;
        PrimaryPin = PrimaryPin + 2;
        t_sensor = t_sensor - 1;
        sensorError = 0;
        tchannel++;
    }
    t_sensor = t_sensorConst;
    PrimaryPin = PrimaryPinConst;
}












