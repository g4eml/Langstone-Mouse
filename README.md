# Langstone-Mouse
## Description

This design configures an Arduino Pro Micro or Raspberry Pi RP2040 (Pico) board to behave as if it is a USB mouse. This is optimised for use as the tuning control of the Langstone transceiver. 
A good qualty rotary encoder can be connected and used as the tuning knob. Such encoders often have a high number of pulses per revolution which can be more than is needed by the Langstone software. The arduino code allows the pulses per revolution to be reduced before feeding the Langstone. 

## Requirements

This code will only work on an ATmega32u4 processor such as used on the Pro Micro board or with an RP2040 based board.  Other processors do not support the mouse library that is needed.

Aduino Pro Micro boards are available for about £6 on ebay. Make sure you buy the 5V 16MHz version.

RP2040 Zero boards are also available for similar prices. Alternatively a Raspberry Pi RP2040 Pico board can be used although this is phisically larger. 

The Rotary encoder needs to have quadrature outputs that are either open collectors, switches to ground or TTL levels.

Connections for the rotary encoder and switches are shown in the schematic. Pin numbers shown are as marked on the arduino board. 

## Programming

First download, save and unzip the files from this repository 

https://github.com/g4eml/Langstone-Mouse/archive/main.zip

The board then needs to be programmed using the normal Arduino IDE. Download and install this from https://www.arduino.cc/en/Main/Software

## Support for the Pro Micro board needs to be added by doing the following:-

Start the Arduino IDE and open the preferences window (File > Preferences)

Copy and paste the following URL into the 'Additional Boards Manager URLs' input field.

```sh
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
```
Then Select (Tools> Board > Board Manager) Scroll down to "Sparkfun AVR Boards" and choose Install.

Wait for the instalation to complete then select Close

Then select (Tools > Board > Sparkfun AVR Boards > Sparkfun Pro Micro)

Make sure (Tools > Processor) is set to 'ATmega32u4 (5V, 16MHz)'

You will also need to add the library for handling the rotary encoder:-

Select (Tools > Manage Libraries)
Search for 'Encoder'
Scroll down to find the Encoder by Paul Stoffregen
Click Install

## Support for the RP2040 boards needs to be added by doing the following:-

Start the Arduino IDE and open the preferences window (File > Preferences)

Copy and paste the following URL into the 'Additional Boards Manager URLs' input field.

```sh
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```
Then Select (Tools> Board > Board Manager) 
Type 'Pico' into the search box and select 'Add'.

Wait for the instalation to complete then select Close

Then select (Tools > Board > Sparkfun AVR Boards > Sparkfun Pro Micro)

Make sure (Tools > Processor) is set to 'RP2040'

You will also need to add the library for handling the rotary encoder:-

Select (Tools > Manage Libraries)
Search for 'RP2040 Encoder'
Scroll down to find the rp2040-encoder-library by Giovanni di Dio Bruno
Click Install

## Building

Once all this is in place you should be able to build the LangstoneMouse.ino file  and upload it to the board. If using the RP2040 you may need to hold the Boot button down when connecting the board. 

When the upload has completed the board will be detected as a USB mouse. This should work alongside your existing mouse in Windows. The scroll wheel and buttons can be tested by opening a long test document. 

## Configuration

The code allows for adjusting the resolution of the encoder. 
At the beginning of the .ino file you will find the lines 

#define encoderStepsPerRev 400

#define outputStepsPerRev  40

#define reverse false



You can change these lines to match the resolution of your encoder. The software will then scale the output to a suitable value for Langstone. 
Changing reverse from false to true will reverse the tuning direction of the encoder. 











