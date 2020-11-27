#ifndef CONFIG
#define CONFIG

// login to wifi network
#define WiFi_SSID "Michi\ 🐿️"
#define WiFi_PSK "callMeTheRoller"



// Pin Layout:

//which pin is connected to the WS2812 LED Stripe
#define pData 2

// where is the button connected?
#define pButton 3



// Stripe Length: the amount of WS2812 LEDs in a row
#define sLen 144



// Enabling or disabling OTA (over the air) flashing. Comment it out to disable OTA.
#define OTA

// default port is 8266
#define OTA_Port 8266

// Hostname defaults to esp8266-[ChipID]
#define OTA_Hostname "LED-Stripe Controller"

// No authentication by default
#define OTA_Password "Pass1word"

// Password can be set with it's md5 value as well
// MD5(Pass1word) = 21232f297a57a5a743894a0e4a801fc3
//#define OTA_Passwd_Hash "6479799dfe1bd86e2777e1da2eec6bcc"



// optional serial debugging. Comment it out to disable serial debugging
#define serial

#ifdef serial
#define SERIAL_BAUD 115200
#endif

#endif
