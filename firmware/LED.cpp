#include <FastLED.h>
#include "config.h"
#include "Arduino.h"
#include "eeprom.h"


// global variables


// Define the array of leds
CRGB leds[sLen];

// configuration
uint16_t Time; // Time
uint16_t Duration; // Duration
uint8_t Color[3]; // Color

// parameters calculated from configuration
unsigned long animDuration, stepTime;

// current state
bool Direction, State;
// State: True -> Stripe is turned on, false -> Stripe is turned off
// Direction: True -> positive index shifting, false -> negative index shifting
unsigned int ind;

// timer
unsigned long last_update, anim_start;


void statusLED( bool Status ) { // true: stripe is running, false: stripe is turned off
  bool state_old = State; // store old status value

#ifdef serial
  Serial.println("LED: Setting Status to " + String(Status));
#endif

  State = Status; // set satus-Variable

  if (state_old == false && State == true) { // if state switched from off to on
#ifdef serial
    Serial.println("LED: Status switched from " + String( (state_old == true) ? "TRUE" : "FALSE" ) + " to " + String( (State == true) ? "TRUE" : "FALSE" ));
    Serial.println("LED: Resetting both timers, Direction and index value");
#endif
    last_update = anim_start = millis();
    Direction = true;
    ind = 0;
  }
}


void updateLEDConfig( void ) {
  // get values from EEPROM
  eeprom_config * Config = new eeprom_config();
  Time = Config->getTime();
  Duration = Config->getDuration();
  Color[0] = Config->getColorRed();
  Color[1] = Config->getColorGreen();
  Color[2] = Config->getColorBlue();
  delete Config;

  animDuration = Duration * 60 * 1000; // transform minutes to milliseconds
  stepTime = (Time * 1000) / (2 * sLen); // calculate time an LED is turned on


#ifdef serial
  Serial.println("LED: Update Conig ");
  Serial.println("\t Runtime = "  + String(Time));
  Serial.println("\t Duration = " + String(Duration));
  Serial.println("\t Color-R = "  + String(Color[0]));
  Serial.println("\t Color-G = "  + String(Color[1]));
  Serial.println("\t Color-B = "  + String(Color[2]));
  Serial.println("Calculated Parameters:");
  Serial.println("\t Animation-Duration = "  + String(animDuration) + " ms");
  Serial.println("\t Step-Time = "  + String(stepTime) + " ms");
#endif

}


void initLED( void ) {
#ifdef serial
  Serial.println("LED: Initialising Service");
#endif
  updateLEDConfig(); // get the values stored in EEPROM
  statusLED(false); // turn stripe off

#ifdef serial
  Serial.println("LED: Resetting both timers");
#endif
  last_update = anim_start = millis();

  Direction = true;
  ind = 0;


#ifdef serial
  Serial.println("LED: Initialising FastLED, turning all LEDs black and showing");
#endif
  // init led stripe in fastled library
  FastLED.addLeds<NEOPIXEL, pData>(leds, sLen).setCorrection( TypicalLEDStrip );

  // turn all LEDs in LED-Array off
  for (unsigned int i = 0; i < sLen; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();

}


void proceedLED( void ) {
  if (State) {
#ifdef serial
    Serial.println("LED: Satus-Value tells the LEDs to run");
#endif
    unsigned long Now = millis();
    if (Now - anim_start < animDuration) {
#ifdef serial
      Serial.println("LED: Animation-Timer tells the LEDs to run");
#endif
      if (Now - last_update > last_update) {
#ifdef serial
        Serial.println("LED: Updating Step-Timer");
#endif
        last_update -= Now; // update Timer

        // check index position. Maybe direction neets to be flipped
        if ( (ind == 0 && !Direction) || ((ind == (sLen - 1) && Direction)) ) {
#ifdef serial
          Serial.println("LED: Flipping Direction");
#endif
          Direction = !Direction;
        }

        // perform index shift
        ind += (Direction) ? 1 : -1;

        // turn whole stripe black and colorize only the one at the index-position
        for (unsigned int i = 0; i < sLen; i++) {
          leds[i] = CRGB::Black;
        }
        leds[ind].r = Color[0];
        leds[ind].g = Color[1];
        leds[ind].b = Color[2];

#ifdef serial
        Serial.println("LED: Showing Update on Stripe");
#endif

        FastLED.show(); // perform output

      }
    } else {
#ifdef serial
      Serial.println("LED: Animation done. Setting Status to 'false'");
#endif
      statusLED(false);
    }
  }

  //FastLED.show();
}
