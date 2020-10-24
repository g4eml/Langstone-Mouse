# Langstone-Mouse
## Description

This design configures an Arduino Pro Micro board to behave as if it is a USB mouse. This is optimised for use as the tuning control of the Langstone transceiver. 
A good qualty rotary encoder can be connected and used as the tuning knob. Such encoders often have a high number of pulses per revolution which can be more than is needed by the Langstone software. The arduino code allows the pulses per revolution to be reduced before feeding the Langstone. 

## Requirements

This code will only work on an ATmega32u4 processor such as used on the Pro Micro board. Other processors do not support the mouse library that is needed.
The Rotary encoder needs to have quadrature outputs that are either open collectors or switches to ground.
Connections for the rotary encoder and switches are shown in the schematic. 

## Programming

First download, save and unzip the files from this repository 

https://github.com/g4eml/Langstone-Mouse/archive/main.zip

The Arduino Pro Micro board then needs to be programmed using the normal Arduino IDE. Download and install this from https://www.arduino.cc/en/Main/Software

Support for the Pro Micro board needs to be added by doing the following:-

Start the Arduino IDE and open the preferences window (File > Preferences)

Copy and paste the following URL into the 'Additional Boards Manager URLs' input field.

```sh
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
```
Then select (Tools > Board > Sparkfun AVR Boards > Sparkfun Pro Micro)

Make sure (Tools > Processor) is set to 'ATmega32u4 (5V, 16MHz)'

You will also need to add the library for handling the rotary encoder:-

Select (Tools > Manage Libraries)
Search for 'Encoder'
Scroll down to find the Encoder by Paul Stoffregen
Click Install

Once all this is in place you should be able to load the LangstoneMouse.ino file  and upload it to the Arduino. 

When the upload has completed the board will be detected as a USB mouse. This should work alongside your existing mouse in Windows. The scroll wheel and buttons can be tested by opening a long test document. 

## Configuration

The code allows for adjusting the resolution of the encoder. 
At the beginning of the .ino file you will find the line 

#define encoderStepsPerRev 400

You can change this line to match the resolution of your encoder. The software will then scale the output to a suitable value for Langstone. 










