#include <EEPROM.h>
#include "eeprom.h"

/*
   The EEPROM is used i the following way:
   0. Byte: H-Byte of Variable 'Time'
   1. Byte: L-Byte of Variable 'Time'
   2. Byte: H-Byte of Variable 'Duration'
   3. Byte: L-Byte of Variable 'Duration'
   4. Byte: Variable 'Color_R'
   5. Byte: Variable 'Color_G'
   6. Byte: Variable 'Color_B'
*/


// Time
uint16_t eeprom_config::getTime( void ) {
  uint16_t Time = uint16_t(EEPROM[0] << 8) + uint16_t(EEPROM[1]);

#ifdef serial
  Serial.println("EEPROM: Getting value of Time: " + String(Time));
#endif

  return Time;
}
void eeprom_config::setTime( uint16_t Time ) {
#ifdef serial
  Serial.println("EEPROM: Setting value of Time: " + String(Time));
#endif
  // write H and L Byte of Variable 'Time'
  EEPROM[0] = uint8_t(Time >> 8);
  EEPROM[1] = uint8_t(Time);
}


// Duration
uint16_t eeprom_config::getDuration( void ) {
  uint16_t Duration = uint16_t(EEPROM[2] << 8) + uint16_t(EEPROM[3]);

#ifdef serial
  Serial.println("EEPROM: Getting value of Duration: " + String(Duration));
#endif

  return Duration;
}
void eeprom_config::setDuration( uint16_t Duration ) {
#ifdef serial
  Serial.println("EEPROM: Setting value of Duration: " + String(Duration));
#endif

  // write H and L Byte of Variable 'Duration'
  EEPROM[2] = uint8_t(Duration >> 8);
  EEPROM[3] = uint8_t(Duration);
}



// color red
uint8_t eeprom_config::getColorRed( void ) {
  uint8_t Red = uint8_t(EEPROM[4]);

#ifdef serial
  Serial.println("EEPROM: Getting value of Color Red: " + String(Red));
#endif

  return Red;
}
void eeprom_config::setColorRed( uint8_t Red ) {
#ifdef serial
  Serial.println("EEPROM: Setting value of Color Red: " + String(Red));
#endif

  EEPROM[4] = uint8_t(Red);
}


// color green
uint8_t eeprom_config::getColorGreen( void ) {
  uint8_t Green = uint8_t(EEPROM[5]);

#ifdef serial
  Serial.println("EEPROM: Getting value of Color Green: " + String(Green));
#endif

  return Green;
}
void eeprom_config::setColorGreen( uint8_t Green ) {
#ifdef serial
  Serial.println("EEPROM: Setting value of Color Green: " + String(Green));
#endif

  EEPROM[5] = uint8_t(Green);
}


// color blue
uint8_t eeprom_config::getColorBlue( void ) {
  uint8_t Blue = uint8_t(EEPROM[6]);

#ifdef serial
  Serial.println("EEPROM: Getting value of Color Green: " + String(Green));
#endif

  return Blue;
}
void eeprom_config::setColorBlue( uint8_t Blue ) {
#ifdef serial
  Serial.println("EEPROM: Setting value of Color Blue: " + String(Blue));
#endif

  EEPROM[6] = uint8_t(Blue);
}
