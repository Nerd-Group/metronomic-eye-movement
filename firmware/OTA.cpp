#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "config.h"

void InitOTA( void ) {
#ifdef OTA_Port
  ArduinoOTA.setPort(OTA_Port);
#endif

#ifdef OTA_Hostname
  ArduinoOTA.setHostname(OTA_Hostname);
#endif
  
#ifdef OTA_Password
  ArduinoOTA.setPassword(OTA_Password);
#endif

#ifdef OTA_Passwd_Hash
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
    Serial.println("OTA: Start updating " + type);
#endif
  });


  ArduinoOTA.onEnd([]() {
#ifdef serial
    Serial.println("\nOTA: Finished");
#endif
  });


  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
#ifdef serial
    Serial.printf("OTA: Progress: %u%%\r", (progress / (total / 100)));
#endif
  });


  ArduinoOTA.onError([](ota_error_t error) {
#ifdef serial
    Serial.printf("OTA: Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("OTA: Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("OTA: Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("OTA: Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("OTA: Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("OTA: End Failed");
    }
#endif
  });


  ArduinoOTA.begin();

#ifdef serial
  Serial.println("OTA: Service enabled");
#endif
}



// make the OTA service run when a request comes in
void OTA_KeepAlive( void ){
  ArduinoOTA.handle();
}
