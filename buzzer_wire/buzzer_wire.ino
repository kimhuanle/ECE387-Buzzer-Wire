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
int segments[] = {2,3,4,5,6,7,8,13};
int digits[] = {12,11,10,9};
int trigger = A1;
int count = 0;
unsigned long lastInc = 0;

void setup() {
  for (int i = 0; i < 8; i++)
    pinMode(segments[i], OUTPUT);
  for (int i = 0; i < 4; i++)
    pinMode(digits[i], OUTPUT);
  pinMode(trigger, INPUT);
//  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
//  displayNum(count);
//  if(millis() - lastInc >= 100) {
//    lastInc = millis();
//    count++;
//  }
//  Serial.println(digitalRead(trigger));
//  delay(200);
  if(digitalRead(trigger))
    displayNum(1111);
  else
    displayNum(0)
}
