#include <EEPROM.h>

class eeprom_config {
  public:
    // Time
    uint16_t getTime( void );
    void setTime( uint16_t Time );


    // Duration
    uint16_t getDuration( void );
    void setDuration( uint16_t Duration );


    // color red
    uint8_t getColorRed( void );
    void setColorRed( uint8_t Red );


    // color green
    uint8_t getColorGreen( void );
    void setColorGreen( uint8_t Green );


    // color blue
    uint8_t getColorBlue( void );
    void setColorBlue( uint8_t Blue );
};
