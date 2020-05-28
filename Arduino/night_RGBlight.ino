#include <PololuLedStrip.h>

/* Create an ledStrip object and specify the pin it will use. */
PololuLedStrip<2> ledStrip;

/* Create a buffer for holding the colors (3 bytes per color). */
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

int sw_max = 160;
int sw_min = 150;
int color_dis = 1;
int full_sh = 250;
int test = 61;

void setup()
{
    pinMode(1, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    led_setLight(0, 0, 0);
}


void loop() {

  int anal = analogRead(1);
 
    if(digitalRead(6) == LOW) {
        color_dis = random(1,12);
    }

    while (digitalRead(9) == LOW) {
              sub_settings();
    }          
    
    while (anal < sw_min) {

        while (digitalRead(9) == LOW) {
              sub_settings();
            }
        
        if (digitalRead(7) == LOW) {
            rainbow(50);
        } else {
            color(color_dis);
            delay (100);
        }
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
        }
        if (digitalRead(5) == LOW) {
            delay (100);
            color_dis++;
            if(color_dis>12) {
                color_dis = 1;
            }
        }
      
        anal = analogRead(1);

        if (anal >= sw_min && anal < sw_max) {
            anal = sw_min - 1;
        }
    }

    delay (250); 

    led_setLight(0,0,0);
}

void sub_settings() {
    int anal = analogRead(1);
    
    if (anal < sw_min) {
        led_setLight(0,255,0);
        delay(80);
        anal = analogRead(1);
    } else {
        led_setLight(255,0,0);
        delay(80);
    }

    if (digitalRead(1) == LOW) {
        delay(20);
        sw_min = sw_min - 10;
        if (sw_min <= 0) {
            sw_min = 0;
        }
        sw_max = sw_min + 10;
    }
    if (digitalRead(5) == LOW) {
        delay(20);
        sw_min = sw_min + 10;
        if (sw_min >=1000) {
            sw_min = 1000;
        }
        sw_max = sw_min + 10;
    }
}

void led_setLight(int r, int g, int b) {
      
    rgb_color color;
    color.red = g;
    color.green = r;
    color.blue = b;

    colors[0] = color;

    ledStrip.write(colors, LED_COUNT);

}

void color(int mode) {
    
    int r,g,b;

    if (mode == 1) {r = full_sh; g = 0; b = 0;}
    if (mode == 2) {r = full_sh; g = full_sh/2; b = 0;}
    if (mode == 3) {r = full_sh; g = full_sh; b = 0;}
    if (mode == 4) {r = full_sh/2; g = full_sh; b = 0;}
    if (mode == 5) {r = 0; g = full_sh; b = 0;}
    if (mode == 6) {r = 0; g = full_sh; b = full_sh/2;}
    if (mode == 7) {r = 0; g = full_sh; b = full_sh;}
    if (mode == 8) {r = 0; g = full_sh/2; b = full_sh;}
    if (mode == 9) {r = 0; g = 0; b = full_sh; }
    if (mode == 10) {r = full_sh/2; g = 0; b = full_sh; }
    if (mode == 11) {r = full_sh; g = 0; b = full_sh; }
    if (mode == 12) {r = full_sh; g = 0; b = full_sh/2; }
    
    led_setLight(r,g,b);
}

void full_sh_switch() {
    
    if(full_sh<=50) {
        full_sh = full_sh - 10;
    } else {
        full_sh = full_sh - 50;
    }
    if(full_sh<=0) {
        full_sh = 250;
    }
}
void min_switch() {

    if(full_sh<=50) {
        full_sh = full_sh + 10;
    } else {
        full_sh = full_sh + 50;
    }
    if(full_sh>=250) {
        full_sh = 10;
    }
}

void rainbow(int d) {
  int dd = (250/full_sh) * d;
    
    for (int i = 0; i<=full_sh; i++) {
        while (digitalRead(9) == LOW) {
                  sub_settings();
                }
        if (digitalRead(7) == HIGH) {
            break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
            led_setLight(0,0,0);
            break;
        }
        led_setLight(full_sh,i,0);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
        if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }
    for (int i = full_sh; i>=0; i--) {
        while (digitalRead(9) == LOW) {
             sub_settings();
        }
        if (digitalRead(7) == HIGH) {
              break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
            led_setLight(0,0,0);
            break;
        }
        led_setLight(i,full_sh,0);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
         if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }
  
    for (int i = 0; i<=full_sh; i++) {
        while (digitalRead(9) == LOW) {
                  sub_settings();
        }
        if (digitalRead(7) == HIGH) {
              break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
            led_setLight(0,0,0);
            break;
        }
        led_setLight(0,full_sh,i);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
        if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }
    for (int i = full_sh; i>=0; i--) {
        while (digitalRead(9) == LOW) {
                  sub_settings();
                }
        if (digitalRead(7) == HIGH) {
              break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
           led_setLight(0,0,0);
           break;
        }
        led_setLight(0,i,full_sh);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
         if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }
  
    for (int i = 0; i<=full_sh; i++) {
        while (digitalRead(9) == LOW) {
             sub_settings();
         }
        if (digitalRead(7) == HIGH) {
            break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
            led_setLight(0,0,0);
            break;
        }
        led_setLight(i,0,full_sh);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
        if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }
    
    for (int i = full_sh; i>=0; i--) {
        while (digitalRead(9) == LOW) {
           sub_settings();
        }
        if (digitalRead(7) == HIGH) {
              break;
        }
        int anal = analogRead(1);
        if (anal>sw_max) {
            led_setLight(0,0,0);
            break;
        }
        led_setLight(full_sh,0,i);
        delay(dd);
        if (digitalRead(1) == LOW) {
            delay (100);
            full_sh_switch();
            dd = (250/full_sh) * d;
        }
        if (digitalRead(5) == LOW) {
            delay (100);
            min_switch();
            dd = (250/full_sh) * d;
        }
    }

    if(digitalRead(6) == LOW) {
        color_dis = random(1,12);
    }
}
