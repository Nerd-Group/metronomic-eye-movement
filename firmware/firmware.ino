#include "config.h" // configuration. Tweak parameters until it works


#include "WiFi.h" // wifi management


#include "WebInterface.h" // implementation of the web server and the web interface


#ifdef OTA
#include "OTA.h" // Over the air flashing
#endif


#include "Button.h" // Button to turn LEDs on


#include "LED.h" // Interface for the WS2812 LEDs



void setup( void ) {

  // if serial debugging should be enabled: start serial connection
#ifdef serial
  Serial.begin(SERIAL_BAUD);
#endif

  // set up WiFi connection
  initWiFi();

  // initialise Web Interface
  initWebInterface();

  // initialise OTA Interface
#ifdef OTA
  InitOTA();
#endif

  // initialise the Button
  initButton();

  // initialisiere den LED-Streifen
  initLED();
}



void loop( void ) {
  // make the webserver run
  WebInterface_KeepAlive();


  // OTA Service
#ifdef OTA
  OTA_KeepAlive();
#endif

  // proceed if the button has been pushed
  Button_KeepAlive();

  // let the LED light work
  proceedLED();
}
