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

## Diagram
![diagram](https://user-images.githubusercontent.com/48562065/168403196-9660c052-754b-4176-97f7-b7a528960991.png)

## Demonstration
[Demo of the Buzzer Wire Game/Toy](https://www.youtube.com/watch?v=JAsqjuH8NDU): This video shows all the compoenents of the game as well as the walkthrough of the gameplay (both lose and win).
