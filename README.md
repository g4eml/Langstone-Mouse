# Langstone-Mouse
## Description

This design configures an Arduino Pro Micro board to behave as if it is a USB mouse. This is optimised for use as the tuning control of the Langstone transceiver. 
A good qualty rotary encoder can be connected and used as the tuning knob. Such encoders often have a high number of pulses per revolution which can be more than is needed by the Langstone software. The arduino code allows the pulses per revolution to be reduced before feeding the Langstone. 

##Requirements

This code will only work on an ATmega32u4 processor such as used on the Pro Micro board. Other processors do not support the mouse library that is needed.
The Rotary encoder needs to have quadrature outputs that are either open collectors or switches to ground. 

##Programming

The Arduino Pro Micro board needs to be programmed using the normal Arduino IDE. Download and install this from https://www.arduino.cc/en/Main/Software

Support for the board needs to be added by doing the following:-

Start the Arduino IDE and open the preferences window (File > Preferences)
Copy and paste the following URL into the 'Additional Boards Manager URLs' input field.

'''sh
https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
'''

