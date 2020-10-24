// Rotary Encoder and Button Mouse Emulation for Langstone Transceiver. By Colin DurightButtonReleasedidge G4EML
// for Arduino Pro Micro Board. (5V 16MHz Version) (won't work with all Arduinos. Needs the ATmega32U4 chip for USB Mouse emulation.  
// Needs the Encoder Library by Paul Stoffregen. (Search for Encoder in Library Manager)
// Rotary encoder (used as tuning knob) is read and scaled to suitable output pulses per revolution then sent as mouse scroll wheel movement every 10 ms.
// 2 Buttons (used to select tuning rate) are read and sent as mouse clicks on the left and right mouse buttons. 
//

#include <Mouse.h>
#include <Encoder.h>




#define encoderStepsPerRev 400                   //number of steps per revolution of the encoder. Change this to match your encoder.  


#define outputStepsPerRev  40                    //nuber of steps per revolution for tuning. 40 is a good number to start with. Change this if you want to adjust the tuning rate. 



#define RPHA 2                        //Rotary encoder A phase connected to Pin 2. Encoder Common connection to ground.  (do not change, needs the interrupt on this pin to work properly)
#define RPHB 3                        //Rotary encoder B phase connected to Pin 3.                                     
#define LEFTBUTTON 4                //Left and right push buttons. Used by Langstone to select the tuning rate. 
#define RIGHTBUTTON 5               //Connect buttons between these two pins and ground. 

int encoderDiv;
int leftButton;
int rightButton;
int leftButtonReleased;
int rightButtonReleased;

Encoder Enc(RPHA, RPHB);

void setup() 
{
 encoderDiv=(encoderStepsPerRev*4)/outputStepsPerRev;                     // calculate the requred encoder divisor. (Encoder library outputs 4 steps per input step)
 pinMode(LEFTBUTTON,INPUT_PULLUP);
 pinMode(RIGHTBUTTON,INPUT_PULLUP);
 leftButtonReleased=false;
 rightButtonReleased=false; 
 Mouse.begin();
}

void loop() 
{
  delay(20);                            //delay to slow down the rate of USB messages. 50 per second is plenty. 
long counts = Enc.read()/encoderDiv;
if(counts!=0)
  {
  Mouse.move(0,0,counts);
  Enc.write(0);  
  }
  leftButton=digitalRead(LEFTBUTTON);
  rightButton=digitalRead(RIGHTBUTTON);
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

}
