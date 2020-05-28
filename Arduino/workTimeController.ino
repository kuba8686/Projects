#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<8> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

int pinDHT11 = 7;
SimpleDHT11 dht11;

int mode_selection;

unsigned long time_from;
unsigned long time_from_2;

int start = 1;

byte zm_1 = 0;
byte zm_2 = 0;
byte zm_3 = 0;
byte zm_4 = 0;
byte zm_5 = 0;

unsigned long x1 = 0;
unsigned long x2 = 0;
unsigned long x_ext = 0;

unsigned long w_1 = 0;
unsigned long w_2 = 0;
unsigned long w_3 = 0;
unsigned long w_4 = 0;
unsigned long w_5 = 0;


void setup()
{
  // initialize the LCD

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  
  lcd.begin();
  Serial.begin(9600);
  
  // Turn on the blacklight and print a message.
  lcd.backlight();

}

void loop()
{
    
    float absolute_x;
    float proc;
    float a;
    float X_W;
    int procint;
    
    while (digitalRead(6) == LOW) {
        rgb_Light_ON(255,0,0);
        if (mode_selection != 1) {
            x2 = millis()/1000;
            x_ext = x2 - x1;
            switch(mode_selection) { 
                case 2: w_2 = w_2 + x_ext; break;
                case 3: w_3 = w_3 + x_ext; break;
                case 4: w_4 = w_4 + x_ext; break;
                case 5: w_5 = w_5 + x_ext;break;
            }
            x1 = millis()/1000;
        }
        mode_selection = 1;
        lcd.clear();
        mode_selection_x(mode_selection);
        delay(200);
        rgb_Light_ON(255,0,0);
    }
  
    while (digitalRead(5) == LOW) {
        rgb_Light_ON(0,255,0);
        if (mode_selection != 2) {
            x2 = millis()/1000;
            x_ext = x2 - x1;
            switch(mode_selection) { 
                case 1: w_1 = w_1 + x_ext;break;
                case 3: w_3 = w_3 + x_ext;break;
                case 4: w_4 = w_4 + x_ext;break;
                case 5: w_5 = w_5 + x_ext;break;
            }

            x1 = millis()/1000;
        }
        mode_selection = 2;
        lcd.clear();
        mode_selection_x(mode_selection);

        delay(200);
    }
    while (digitalRead(4) == LOW) {
        rgb_Light_ON(0,0,255);
        if (mode_selection != 3) {
            x2 = millis()/1000;
            x_ext = x2 - x1;
            switch(mode_selection) { 
                case 1: w_1 = w_1 + x_ext;break;
                case 2: w_2 = w_2 + x_ext;break;
                case 4: w_4 = w_4 + x_ext;break;
                case 5: w_5 = w_5 + x_ext;break;
            }

            x1 = millis()/1000;
        }
        mode_selection = 3;
        lcd.clear();
        mode_selection_x(mode_selection);
           
        delay(200);
    }
    while (digitalRead(3) == LOW) {
        rgb_Light_ON(255,0,255);
        if (mode_selection != 4) {
            x2 = millis()/1000;
            x_ext = x2 - x1;
            switch(mode_selection) { 
                case 1: w_1 = w_1 + x_ext;break;
                case 2: w_2 = w_2 + x_ext;break;
                case 3: w_3 = w_3 + x_ext;break;
                case 5: w_5 = w_5 + x_ext;break;
        }

        x1 = millis()/1000;
        }

        mode_selection = 4;
        lcd.clear();
        mode_selection_x(mode_selection);
            
        delay(200);
    }
  
    while (digitalRead(2) == LOW || start == 1) {

        rgb_Light_ON(255,255,0);
        if (mode_selection != 5) {
            x2 = millis()/1000;
            x_ext = x2 - x1;
            switch(mode_selection) { 
                case 1: w_1 = w_1 + x_ext;break;
                case 2: w_2 = w_2 + x_ext;break;
                case 3: w_3 = w_3 + x_ext;break;
                case 4: w_4 = w_4 + x_ext;break;
            }

            x1 = millis()/1000;
        }
        
        while (digitalRead(3) == LOW) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("1:");
            
            show_time(w_1);
            absolute_x = float(w_1)/3600;
            
            lcd.print(absolute_x);
            lcd.print(" ");
            
            a = millis()/1000;
            X_W = float(w_1);
            proc = X_W/a*100;
            procint = int(proc);
            
            lcd.print(procint);
            lcd.print("%");
            lcd.setCursor(0, 1);
            lcd.print("2:");
            
            show_time(w_2);
            absolute_x = float(w_2)/3600;
            
            lcd.print(absolute_x);
            lcd.print(" ");
            
            a = millis()/1000;
            X_W = float(w_2);
            proc = X_W/a*100;
            procint = int(proc);
            
            lcd.print(procint);
            lcd.print("%");

            delay(20);
            while (digitalRead(4) == HIGH) {
                delay(40);
            }
            delay(100);

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("3:");
            
            show_time(w_3);
            absolute_x = float(w_3)/3600;
            
            lcd.print(absolute_x);
            lcd.print(" ");
            
            a = millis()/1000;
            X_W = float(w_3);
            proc = X_W/a*100;
            procint = int(proc);
            
            lcd.print(procint);
            lcd.print("%");
            lcd.setCursor(0, 1);
            lcd.print("4:");
            
            show_time(w_4);
            absolute_x = float(w_4)/3600;
            
            lcd.print(absolute_x);
            lcd.print(" ");
            
            a = millis()/1000;
            X_W = float(w_4);
            proc = X_W/a*100;
            procint = int(proc);
            
            lcd.print(procint);
            lcd.print("%");

            delay(20);
            while (digitalRead(4) == HIGH) {
                delay(20);
            }
            delay(100);

            lcd.setCursor(0, 0);
            lcd.print("5:");
            
            int break_hlpM = millis()/1000 - w_1 - w_2 - w_3 - w_4;
            show_time(break_hlpM);
            absolute_x = float(break_hlpM)/3600;
            
            lcd.print(absolute_x);
            lcd.print(" ");
            
            a = millis()/1000;
            X_W = float(break_hlpM);
            proc = X_W/a*100;
            procint = int(proc);
            
            lcd.print(procint);
            lcd.print("%");
            lcd.setCursor(0, 1);
            lcd.print("                 ");



            delay(20);
            while (digitalRead(4) == HIGH) {
                delay(20);
            }
        }
        mode_selection = 5;
        lcd.clear();
        mode_selection_x(mode_selection);
        start = 0;
        rgb_Light_ON(255,255,0);    
        delay(200);
    }

    time_from = millis()/1000 - x1;
    
    int y = x1 + time_from - 1;
    int y2;

    lcd.setCursor(0, 0);
    
    switch(mode_selection) {
        case 1: lcd.print("Reklama"); y2 = time_from + w_1; break;
        case 2: lcd.print("Drogi"); y2 = time_from + w_2; break;
        case 3: lcd.print("Nie swoje"); y2 = time_from + w_3; break;
        case 4: lcd.print("Inne"); y2 = time_from + w_4; break;
        case 5: lcd.print("Przerwa"); y2 = time_from + w_5; break;
    }


    lcd.setCursor(11, 0);
    show_time(time_from);

    lcd.setCursor(0, 1);
    show_time(y2);

    float y_f = float(y);
    float y2_f = float(y2);
    float prc_hlp  = (y2_f/y_f)*100;
    int prc = int(prc_hlp);

    lcd.print(prc);
    lcd.print("% ");

    lcd.setCursor(11, 1);
    show_time(y);

}

void mode_selection_x(int i) {

  if (i == 1) {
    zm_1 = 1;
    zm_2 = 0;
    zm_3 = 0;
    zm_4 = 0;
    zm_5 = 0;    
  }

  if (i == 2) {
    zm_1 = 0;
    zm_2 = 1;
    zm_3 = 0;
    zm_4 = 0;
    zm_5 = 0;    
  }

  if (i == 3) {
    zm_1 = 0;
    zm_2 = 0;
    zm_3 = 1;
    zm_4 = 0;
    zm_5 = 0;    
  }

  if (i == 4) {
    zm_1 = 0;
    zm_2 = 0;
    zm_3 = 0;
    zm_4 = 1;
    zm_5 = 0;    
  }

  if (i == 5) {
    zm_1 = 0;
    zm_2 = 0;
    zm_3 = 0;
    zm_4 = 0;
    zm_5 = 1;    
  }
  
}

void rgb_Light_ON(int r, int g, int b) {
    rgb_color color;
    
    color.red = g;
    color.green = r;
    color.blue = b;

    colors[0] = color;

    // Write to the LED strip.
    ledStrip.write(colors, LED_COUNT);

}

void show_time(long i) {
    int g = i/3600;
    int m = (i%3600)/60;
    int s = (i%3600)%60;

    if (i<3600) {
        lcd.print(m);
        lcd.print(":");
        if (s<10) {
            lcd.print("0");
        }
        lcd.print(s);
        lcd.print(" ");
    }

    if (i>=3600) {
        lcd.print(g);
        lcd.print(":");
        if (m<10) {
            lcd.print("0");
        }
        lcd.print(m);
        lcd.print(" ");
    }
}
