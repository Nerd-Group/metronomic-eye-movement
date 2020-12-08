#include <ESP8266WiFi.h>
#include "config.h"



void initWiFi( void ) {
#ifdef serial
  Serial.print("\nInitialising WiFi connection to SSID " + String(WiFi_SSID));
#endif
 
  // set up WiFi Network connection
  WiFi.mode(WIFI_STA);
  WiFi.begin((const char*)WiFi_SSID, (const char*)WiFi_PSK);


  // if serial debugging is enabled: wait until the wifi connection is done and print the IP Adress
#ifdef serial
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(".");
    //Serial.println(WiFi.status());
  }
  Serial.println("\nConnected");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
#endif
}
