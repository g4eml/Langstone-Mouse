// Rotary Encoder and Button Mouse Emulation for Langstone Transceiver. By Colin Durbridge G4EML
// for Arduino Pro Micro Board. (5V 16MHz Version) (won't work with all Arduinos. Needs the ATmega32U4 chip for USB Mouse emulation. 
// Needs the Encoder Library by Paul Stoffregen. (Search for Encoder in Library Manager)
//
// Now also supports RP2040 boards using the rp2040-encoder-library by Giovanni di Dio Bruno (search for rp2040 Encoder in :Library manager)
//
// Rotary encoder (used as tuning knob) is read and scaled to suitable output pulses per revolution then sent as mouse scroll wheel movement every 20 ms.
// 3 Buttons (used to select tuning rate and dial lock) are read and sent as mouse clicks on the left, middle and right mouse buttons. 
//



#include <Mouse.h>

#define encoderStepsPerRev 400                    //number of steps per revolution of the encoder. Change this value to match your encoder.  

#define outputStepsPerRev  40                    //nuber of steps per revolution for output . 40 is a good number to start with. Must be equal to or lower than encoderStepsPerRev. Change this if you want to adjust the tuning rate. 

#define reverse false                           // set to true to reverse the tuning direction of the encoder. 


#define RPHA 2                        //Rotary encoder A phase connected to Pin 2. Encoder Common connection to ground.  (do not change, needs the interrupt on this pin to work properly)
#define RPHB 3                        //Rotary encoder B phase connected to Pin 3.                                   
#define LEFTBUTTON 4                //Left, right and middle push buttons. Used by Langstone to select the tuning rate and dial lock. 
#define RIGHTBUTTON 5               //Connect buttons between these three pins and ground. 
#define MIDDLEBUTTON 6

int encoderDiv;
int leftButton;
int rightButton;
int middleButton;
int leftButtonReleased;
int rightButtonReleased;
int middleButtonReleased;

#ifdef ARDUINO_ARCH_RP2040

#include <pio_encoder.h> 
PioEncoder Enc(RPHA);
#define stepsPerClick 2
#define readEncoder Enc.getCount()
#define clearEncoder Enc.reset()
#define startEncoder Enc.begin()

#else

#include <Encoder.h>
Encoder Enc(RPHA, RPHB);
#define stepsPerClick 4
#define readEncoder Enc.read()
#define clearEncoder Enc.write(0)
#define startEncoder (void)0

#endif

void setup() 
{
 encoderDiv=(encoderStepsPerRev * stepsPerClick)/outputStepsPerRev;
 pinMode(LEFTBUTTON,INPUT_PULLUP);
 pinMode(RIGHTBUTTON,INPUT_PULLUP);
 pinMode(MIDDLEBUTTON,INPUT_PULLUP);
 leftButtonReleased=false;
 rightButtonReleased=false; 
 middleButtonReleased=false; 
 Mouse.begin();
 startEncoder;

}

void loop() 
{
delay(20);                               //delay to slow down the rate of USB messages. 50 per second is plenty. 
long counts = readEncoder/encoderDiv;    //number of encoder counts since last sent to USB.

if(counts!=0)
  {
  if(reverse) counts = 0-counts;
  Mouse.move(0,0,counts);
  clearEncoder;
  }
  
  leftButton=digitalRead(LEFTBUTTON);
  rightButton=digitalRead(RIGHTBUTTON);
  middleButton=digitalRead(MIDDLEBUTTON);

  if(leftButton==LOW)
    {
     if(leftButtonReleased>=3)
      {
       Mouse.click(MOUSE_LEFT); 
       leftButtonReleased=false; 
      }
    }
  else
    {
      if(leftButtonReleased<3) leftButtonReleased=leftButtonReleased+1;
    }

    
  if(rightButton==LOW)
    {
     if(rightButtonReleased>=3)
      {
       Mouse.click(MOUSE_RIGHT);  
       rightButtonReleased=false;
      }
    }
  else
    {
      if(rightButtonReleased<3) rightButtonReleased=rightButtonReleased+1;
    }


  if(middleButton==LOW)
    {
     if(middleButtonReleased>=3)
      {
       Mouse.click(MOUSE_MIDDLE);  
       middleButtonReleased=false;
      }
    }
  else
    {
      if(middleButtonReleased<3) middleButtonReleased=middleButtonReleased+1;
    }

}
