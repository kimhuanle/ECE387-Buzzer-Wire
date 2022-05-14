# ECE387 Final Individual Project
## Buzzer Wire Game

## Author: Huan Le
## Date: 05/09/2022

![image](https://user-images.githubusercontent.com/48562065/168334271-ebfb0b38-0e47-485d-90f6-bcd72a58347b.jpg)

# Table of Contents

* [Introduction](#Introduction)
* [Components](#Components)
* [Installation](#Installation)
* [Implementation](#Implementation)
* [Process](#Process)
* [Diagram](#Diagram)
* [Demonstration](#Demonstration)
* [Reference](#Reference)
--------------------
## Introduction
This is an Arduino adaption of the classic carnival game Buzzer Wire. The idea came from an episode of Mr. Bean comedy show where Mr. Bean cheated in the Buzzer Wire game in a carnival. The concept is to move a copper wire loop along another copper wire "maze" without touching it and reach the end as soon as possible. In my version, you will have 10 hearts to play the game. Each time you touch the wire, you lose one heart. You have 400 milliseconds cooldown when touching the wire so that you do not lose another heart for your slow reaction 😂. The game has an LCD to display game message, a 4-digit-7-segment display to dislay the timer, a piezo buzzer that makes noise when you touch the wire and when the game ends, and two LEDs to indicate the game state.

## Components
* 1 x Arduino Uno R3<br><img src="https://umaine.edu/hackerspace/wp-content/uploads/sites/290/2017/11/ARDUINO_UNO_A06-300x211.png" width="300" height="200"/>
* 1 x Breadboard<br><img src="https://www.baldengineer.com/wp-content/uploads/2013/12/blank_breadboard.png" width="500" height="250"/>
* 1 x Copper/Steel Wire (length up to you)<br><img src="https://spcproducts.in/sub-images/tinplated-coppercoveredsteel-wire02.png" width="300" height="300"/>
* 1 x 20x4 LCD (I2C)<br><img src="https://cdn.bodanius.com/media/1/948102580_20x4-Karakters-lcd-module-blauw_x.png" width="400" height="250"/>
* 1 x 4-digit-7-segment display<br><img src="https://www.tandyonline.com/media/catalog/product/cache/590206bcb99d8cdaa34f04be73cd5181/4/d/4digit-led-display.png" width="200" height="200"/>
* 1 x Piezo Buzzer<br><img src="https://www.eitkw.com/wp-content/uploads/2018/10/Piezo-Buzzer1.png" width="150" height="160"/>
* 2 x LED (Red & Green)<br><img src="https://cdn-reichelt.de/bilder/web/xxl_ws/A500/LED5MM.png" width="150" height="150"/>
* 4 x AA Battery<br><img src="https://uniquephoto3.azureedge.net/resources/uniquephoto/images/products/processed/DUB942.detail.a.png" width="350" height="350"/>
* 20+ x Jumper cable<br><img src="https://cdn.shopify.com/s/files/1/0410/7888/2465/products/genius-robotics-jumper-wires-40-pins-male-to-male-breadboard-jumper-wires-20cm-011-223-19245926088865_1024x.png?v=1631567860" width="300" height="300"/>
* 3 x 1KΩ Resistor
* 2 x 220Ω Resistor<br><br><img src="https://www.tandyonline.com/media/catalog/product/cache/f27cd47a8c413763245cb9dc18265f6f/2/7/271-1321-1k-carbon-resistors-sml.png" width="200" height="200"/>

## Installation
You can clone this repository to test it out by running this command in your working directory:
```
git clone git@github.com:kimhuanle/ECE387-Buzzer-Wire.git
```
After that open the buzzer-wire.ino file in the buzzer-wire folder, which will open the Arduino IDE. Make sure that you have the ```Wire.h```, ```LiquidCrystal_I2C.h```,and ```LowPower.h``` libraries installed in your Arduino library Then, connect your Arduino microcontroller with everything set up and upload the code.
Here are the links to the libraries:
* [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
* [LowPower](https://github.com/rocketscream/Low-Power)

## Implementation
* To implement this kid toy, I included 5 main peripherals: LCD, 4-digit-7-segment display, switches(the wires), piezo buzzer, and LEDs.
* I implemented a finite state machine to switch between 4 states of the game: ```INIT``` (waiting mode), ```GAME``` (gameplay mode), ```WIN``` (winning mode), ```LOST``` (losing mode)
* In each state, I call different functions to print to the LCD, turn on LEDs, check for wire touch, display timer on the 4-digit-7-segment display, play sound on the piezo buzzer.
* In state ```INIT```, I print the welcome message on the LCD, turn on red LED, and constantly check for wire touch to start the game.
* In state ```GAME```, I print the number of hearts on the LCD, display the timer to the 4-digit-7-segment display (up to 1/10th of a second accuracy), and constantly check for the wire touch to decrease the number of hearts and make noise.
* In state ```WIN```, I flash the winning message on the LCD and the time it takes to win the game on both the LCD and the 4-digit-7-segment display, and play the victory melody on the piezo buzzer.
* In state ```LOST```, I print the losing message on the LCD, and play the loss melody on the piezo buzzer.
* To achieve the accuracy of the timer and to run multiple functions concurrently, I have to use the ```millis()``` function instead of the ```delay()``` function.

##  Process
* Though this project took me only 1 week to complete, it requires a long and cumbersome process of problem solving.
* First, I had to figure out how to detect the wire touch during the game, and to start and stop the timer. For this, I recalled researching about the switch and decided to emulate the pushbutton behavior on the 3 wires. I connected the start wire, the stop wire, and the maze wire such that they simulate one end of a pushbutton that is pulled down though a 10kΩ resistor and connected the wire ring to 5V VCC.
* The second problem that I had to solve involved displaying a timer on the 4-digit-7-segment display. To tackle this, I did some research on how the digits are selected and how to turn on each segment of the 7 segments. I created 3 functions to properly display a 4 digit number to the display. The first one will take in a number from 0 to 9 to display a digit. The second one takes in a number from 1 to 4 to select the placement of the digit being displayed. The third one takes in a number and display the last 4 digits of that number by cycling through them and select the corresponding placement and displaying the corresponding digit.
* The I2C LCD is another problem that I had to solve. This was fairly easy as I only needed to include an already written library from the Arduino forum.
* I also had to create 2 functions to detect the maze wire touch during the game as well as the wire touch to start and stop the game.
* For the buzzer, I simply had to use the tone and find 2 melodies for the win and loss state of the game.
* Another important part of the project was the finite state machine. For that, I chose the polling method to check for inputs and determine which state the game is in. The finite state machine is fairly simple. The game starts with the INIT state, then moves on to the GAME state. During the GAME state, I constantly check if the stop wire is touched to switch to the WIN state or if the number of hearts has reached 0 to switch to the LOSS state. The WIN and LOSS state call different functions to display different visuals to the LCD and the 4-digit-7-segment display, and play the corresponding melody.
* The trickiest part of all is to use the ```millis()``` function to keep track of the timer, display to the LCD and the 4-digit-7-segment-display, and play the melody concurrently.

## Diagram
Below is the wiring diagram of the whole game

![diagram](https://user-images.githubusercontent.com/48562065/168403196-9660c052-754b-4176-97f7-b7a528960991.png)
- The button on the right represents when the ring touches the wire maze
- The button in the middle represents whne the ring touches the start wire
- The button on the left represents when the ring touches the stop wire

## Demonstration
[Demo of the Buzzer Wire Game/Toy](https://www.youtube.com/watch?v=JAsqjuH8NDU): This video shows all the compoenents of the game as well as the walkthrough of the gameplay (both lose and win).

## Power Reduction Technique
* For this project, I decided to implement the power reduction technique to make it more viable for actual production. To do so, I chose to reduce the clock speed by 1/4 from 16MHz to 4MHz and implement sleeping meachanism for the game.
  * To reduce the clock speed of the Arduino, I added these two line to the setup function

        CLKPR = 0x80; // (1000 0000) enable change in clock frequency
        CLKPR = 0x02; // (0000 0001) use clock division factor 4 to reduce the frequency from 16 MHz to 4 MHz
    I also had to adjust the timing by dividing every delay by 4.
  * To implement the sleeping mechanism, I used the ```LowPower.h``` library available on the Arduino Forum. I used the maze wire as an external interrupt to enable the game. When no body touches the wire for 5 seconds before the game starts, the Arduino will enter the sleep mode. The Arduino stays sleeping until the maze wire touches the ring wire. Everything was made possible using this piece of code:

        attachInterrupt(0, wakeUp, HIGH);
        LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
        detachInterrupt(0); 
        
        while(!(game_state == INIT && millis() - interrupt >= 5000/4))
          game();
