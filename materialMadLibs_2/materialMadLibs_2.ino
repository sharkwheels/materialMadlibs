
/********************************
Creation Computation: 2016

Assignment one: Panic.

1 button that sends a heartbeat out to serial.
Processing reads it on the other side to manipulate audio.

If the button is on, send a heartbeat to increase a value every 500ms
Else, bring that value down in intervals over time until it is equal to 1. 

**********************************/


#include <elapsedMillis.h>

/********************/

unsigned long lastDebounceTime = 0;     // the last time the output pin was toggled
unsigned long debounceDelay = 20;      // the debounce time; increase if the output flickers

int btnPin = 2;         // the button Pin
int btnLed = 13;         // the button LED for testing
int buttonState;          
int lastButtonState;      

elapsedMillis timer0;
elapsedMillis timer1;
boolean wasGrabbed;
#define interval 500
int v;



void setup(){
  Serial.begin(9600);
  pinMode(btnPin, INPUT_PULLUP); 
  pinMode(btnLed, OUTPUT);
}

void loop(){

  int buttonReading = digitalRead(btnPin);

  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = buttonReading;
    if (buttonState == HIGH){
        /// BUTTON IS OFF /////////////////////
      digitalWrite(btnLed, LOW);
      timer0 = 0;
      /// count back down to 1 ////////////
      if(wasGrabbed && v > 1){
        if(timer1 > interval){
          timer1 -= interval; //reset the timer
          v--;
          Serial.println(v,DEC);
          if(v <= 1){
            v = 1;
            wasGrabbed = false;
          }
        }
      }
    } else {
      /// BUTTON IS ON ////////////////////////////
      digitalWrite(btnLed, HIGH);
      timer1 = 0;
      wasGrabbed = true;
      if(timer0 > interval){
        timer0 -= interval; //reset the timer
        v++;
        Serial.println(v,DEC);
        if(v >= 9){
          v = 9;
        }
        
      }
    
    }
  }
  lastButtonState = buttonReading;
}
