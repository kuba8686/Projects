#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN 3
#include "DHT.h"

#define DHTPIN 11 
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C  lcd(0x27, 2, 1, 0, 4, 5, 6, 7);


void setup() {
    dht.begin();

    lcd.begin (16, 2);
    lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.home ();

    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
}


void loop() {
  
    int funOff_cycle = analogRead(A0); // fun off in [sec]
    funOff_cycle = map(funOff_cycle, 0, 1000, 2, 120);
  
  
    for (int i = 1; i<=funOff_cycle+1; i++) {
      
        int d = analogRead(A1); // fun on [sec]
        d = map(d, 10, 1000, 2, 120);

        int t_cont = analogRead(A2); // temp when fun goes on
        t_cont = map(t_cont, 10, 1000, 20, 40);
      
        if (i < funOff_cycle+1) {
            delay(1000);
        }
        digitalWrite(12, LOW);

        int temp = dht.readTemperature();

        lcd.setCursor(6, 0);
        lcd.print("W:");
        lcd.print(funOff_cycle);
        lcd.print("s ");

        lcd.setCursor(0, 1);
        lcd.print(temp);
        lcd.print("C");
     
        if (i == funOff_cycle+1) {
            lcd.setCursor(13, 0);
            lcd.print("  ");
            lcd.setCursor(13, 1);
            lcd.print("0 ");
        } else {
            lcd.setCursor(13, 1);
            lcd.print("  ");
            lcd.setCursor(13, 0);
            lcd.print(i);
            lcd.print("  ");
        }
     
        lcd.setCursor(0, 0);
        lcd.print("Z:");
        lcd.print(t_cont);
        lcd.print("C");

        lcd.setCursor(6, 1);
        lcd.print("C:");
        lcd.print(d);
        lcd.print("s ");
     
        if (temp >= t_cont) {

            digitalWrite(13, HIGH);
            digitalWrite(12, LOW);
            t_cont = t_cont - 3;
            
            while(temp > t_cont) {
                temp = dht.readTemperature();
                lcd.setCursor(0, 1);
                lcd.print(temp);
                lcd.print("'C");
                delay(1000);
            }
        } else {
            digitalWrite(13, LOW);
        }
     
        if (i==funOff_cycle+1) {
            digitalWrite(12, HIGH);
            for (int a = 1; a<=d; a++) {
                delay(1000);
                lcd.setCursor(13, 1);
                lcd.print(a);
                lcd.print(" ");
            }
      
            lcd.setCursor(13, 0);
            lcd.print("0 ");
        } 
   }
}
