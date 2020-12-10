#include "Arduino.h"
#include "config.h"
#include "LED.h"



// global Variable for the state of the button
bool buttonState;

void initButton( void ) {
#ifdef serial
  Serial.println("Button: Service started");
#endif

  pinMode(pButton, INPUT); // drive pin with connection to the button as INPUT
  buttonState = digitalRead(pButton); // get the current state of the button

#ifdef serial
  Serial.println("Button: Listening on Pin " + String(pButton));
  Serial.println("Button: Pin State " + (buttonState == HIGH) ? "HIGH" : "LOW");
#endif
}



void Button_KeepAlive( void ) {
  // get the current state of the button and compare with the previous value
  bool buttonStateOld = buttonState;
  buttonState = digitalRead(pButton);
  if ( buttonState != buttonStateOld ) {
    // if the state has changed: start the LED Stripe

#ifdef serial
    Serial.println("Button: Pin Changed from " + String( (buttonStateOld == HIGH) ? "HIGH" : "LOW" ) + " to " + String( (buttonState == HIGH) ? "HIGH" : "LOW" ));
    Serial.println("Button: Starting LED Stripe");
#endif

    // start the LED Stripe
    statusLED(true);
  }
}
