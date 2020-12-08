#include "Arduino.h"
#include "config.h"
#include "LED.h"



// global Variable for the state of the button
bool buttonState;

void initButton( void ) {
  pinMode(pButton, INPUT); // drive pin with connection to the button as INPUT
  buttonState = digitalRead(pButton); // get the current state of the button
}



void Button_KeepAlive( void ) {
  // get the current state of the button and compare with the previous value
  bool buttonStateOld = buttonState;
  buttonState = digitalRead(pButton);
  if ( buttonState != buttonStateOld ) {
    // if the state has changed: start the LED Stripe
    statusLED(true);
  }
}
