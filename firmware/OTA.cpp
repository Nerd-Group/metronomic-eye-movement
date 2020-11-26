#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "config.h"

void InitOTA( void ) {
  ArduinoOTA.setPort(OTA_Port);
  ArduinoOTA.setHostname(OTA_Hostname);
  ArduinoOTA.setPassword(OTA_Password);

#ifdef OTA_Passwd_Hash
#define OTA_Passwd_Hash
  ArduinoOTA.setPasswordHash(OTA_Passwd_Hash);
#endif

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
#ifdef serial
#define serial
    Serial.println("Start updating " + type);
#endif
  });


  ArduinoOTA.onEnd([]() {
#ifdef serial
#define serial
    Serial.println("\nEnd");
#endif
  });


  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
#ifdef serial
#define serial
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
#endif
  });


  ArduinoOTA.onError([](ota_error_t error) {
#ifdef serial
#define serial
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
#endif
  });


  ArduinoOTA.begin();

#ifdef serial
#define serial
  Serial.println("OTA Service enabled");
#endif
}
