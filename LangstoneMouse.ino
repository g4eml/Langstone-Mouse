// Rotary Encoder and Button Mouse Emulation for Langstone Transceiver. By Colin Durbridge G4EML
// for Arduino Pro Micro Board. (5V 16MHz Version) (won't work with all Arduinos. Needs the ATmega32U4 chip for USB Mouse emulation.  
// Needs the Encoder Library by Paul Stoffregen. (Search for Encoder in Library Manager)
// Rotary encoder (used as tuning knob) is read and scaled to suitable output pulses per revolution then sent as mouse scroll wheel movement every 20 ms.
// 3 Buttons (used to select tuning rate and dial lock) are read and sent as mouse clicks on the left, middle and right mouse buttons. 
//

#include <Mouse.h>
#include <Encoder.h>




#define encoderStepsPerRev 400                   //number of steps per revolution of the encoder. Change this to match your encoder.  


#define outputStepsPerRev  40                    //nuber of steps per revolution for tuning. 40 is a good number to start with. Change this if you want to adjust the tuning rate. 



#define RPHA 3                        //Rotary encoder A phase connected to Pin 2. Encoder Common connection to ground.  (do not change, needs the interrupt on this pin to work properly)
#define RPHB 2                        //Rotary encoder B phase connected to Pin 3. Swap these two pins to reverse the encoder direction.                                    
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

Encoder Enc(RPHA, RPHB);

void setup() 
{
 encoderDiv=(encoderStepsPerRev*4)/outputStepsPerRev;                     // calculate the requred encoder divisor. (Encoder library outputs 4 steps per input step)
 pinMode(LEFTBUTTON,INPUT_PULLUP);
 pinMode(RIGHTBUTTON,INPUT_PULLUP);
 pinMode(MIDDLEBUTTON,INPUT_PULLUP);
 leftButtonReleased=false;
 rightButtonReleased=false; 
 middleButtonReleased=false; 
 Mouse.begin();
}

void loop() 
{
delay(20);                              //delay to slow down the rate of USB messages. 50 per second is plenty. 
long counts = Enc.read()/encoderDiv;    //number of encoder counts since last sent to USB.

if(counts!=0)
  {
  Mouse.move(0,0,counts);
  Enc.write(0);                         //reset the encoder counts
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
