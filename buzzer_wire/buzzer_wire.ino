/**
 * A buzzer wire game in which score represents the time it takes to finish the track
 * Author: Huan Le
 * 
 * MIT License
 * 
 * Copyright (c) 2022 kimhuanle
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#include <LowPower.h>
#include <LiquidCrystal_I2C.h>                                                         
#include <Wire.h>

// Initialize game state
const uint8_t INIT = 0;
const uint8_t GAME = 1;
const uint8_t WIN  = 2;
const uint8_t LOST = 3;
uint8_t game_state;

// Declare timer for scoring and other delays
int timer;
unsigned long last_timer;
unsigned long last_check;
unsigned long last_blink;
bool is_blink = true;
uint8_t blink_time;
unsigned long last_tone;
uint8_t tone_index;
unsigned long interrupt;

// Declare start and stop pins
uint8_t start_input;
uint8_t stop_input;

// Declare number of hearts
uint8_t heart_count;

// Declare boolean for writing to lcd
bool show = true;

// Setting up pins
LiquidCrystal_I2C lcd(0x27,20,4);
const uint8_t segments[8]  = {3,4,5,6,7,8,9,A1};
const uint8_t digits[4]    = {13,12,11,10};
const uint8_t left        = A3;
const uint8_t right       = A2;
const uint8_t wire        = 2;
const uint8_t buzzer      = A0;
const uint8_t green       = 1;
const uint8_t red         = 0;

// Create special chars for lcd
uint8_t heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
uint8_t heart_empty[8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

// Melody for winning and losing
float win_tone[10] = {523.25, 523.25, 523.25, 523.25, 415.30, 466.16, 523.25, 0, 466.16, 523.25};
uint16_t win_duration[11] = {0, 133, 133, 133, 400, 400, 400, 133, 133, 133, 1200};
float lose_tone[8] = {587.33, 554.37, 523.25, 493.883, 0, 493.883, 493.883, 493.883};
uint16_t lose_duration[9] = {0, 500, 500, 500, 200, 50, 130, 130, 130};

/**
 * Setup function
 */
void setup() {
  CLKPR = 0x80; // (1000 0000) enable change in clock frequency
  CLKPR = 0x02; // (0000 0001) use clock division factor 4 to reduce the frequency from 16 MHz to 4 MHz
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, heart);
  lcd.createChar(1, heart_empty);
  for (int i = 0; i < 8; i++)
    pinMode(segments[i], OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(digits[i], OUTPUT);
  pinMode(left  , INPUT);
  pinMode(right , INPUT);
  pinMode(wire  , INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red   , OUTPUT);
  pinMode(green , OUTPUT);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(1000/4);
  game_state = INIT;
}

void wakeUp() {
  interrupt = millis();  
}

void loop(){
  attachInterrupt(0, wakeUp, HIGH);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  detachInterrupt(0); 
  
  while(!(game_state == INIT && millis() - interrupt >= 5000/4))
    game();
}

/**
 * Game loop
 */
void game() {
  switch(game_state) {
    case INIT:
      if (show) {
        timer = 0;
        heart_count = 10;
        digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        lcd_init();
        display_num(timer);
        tone_index = 0;
      }
      check_input();
      break;
    case GAME:
      display_num(timer);
      if(millis() - last_timer >= 100/4) {
        last_timer = millis();
        timer++;
      }
      check_wire();
      if (show) {
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        lcd_game();
      }
      check_input();
      break;
    case WIN:
      display_win();
      lcd_win();  
      tone_win();
      break;
    case LOST:
      if (show) {
        display_lose();
        lcd_lose();
      }
      tone_lose();
      break;
    default:
      break;
  }
}
