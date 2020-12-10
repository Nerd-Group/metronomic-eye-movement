#include <ESP8266WebServer.h>
#include "eeprom.h"
#include "LED.h"


void handleRoot( void );
void handleConfig( void );



// declare the web server
ESP8266WebServer server(80);



void initWebInterface( void ) {
  // initialise web server handles
  server.on("/", handleRoot);
  server.on("/config", handleConfig);

  server.onNotFound([]() { // Error 404
    server.send(404, "text/html", "");
  });

  // open the server
  server.begin();
}



// make the web server ru when a request comes in
void WebInterface_KeepAlive( void ) {
  server.handleClient();
}



// provide Website
void handleRoot( void ) {

#ifdef serial
  Serial.println("HTTP-Server: Website requested");
#endif

  server.send(200, "text/html", "<!DOCTYPE html><html lang=de><head><title>Control Panel</title><meta charset=utf-8><meta name=viewport content='initial-scale=2, maximum-scale=1'><style>html,body{border:0;padding:0;margin:0;font-family:'Segoe UI',Tahoma,Geneva,Verdana,sans-serif;font-size:1rem;color:darkslategrey}body{display:flex;height:100vh;width:100vw;flex-direction:column;align-items:center;justify-content:space-around}form{display:flex;flex-direction:column;justify-content:space-evenly;height:50vh;padding:0;margin:0;border:0}fieldset{border:0;flex:0 0 auto}h1{font-size:1.6rem;font-weight:normal;color:darkcyan}input[type='radio']{margin-left:0;margin-right:1rem;vertical-align:center}input[type='number']{width:4rem;margin-right:.5rem;appearance:textfield;text-align:center}input[type='color']{background-color:#fff;border:0;padding:0}input[type='button']{background-color:#fff;border:solid 1px darkslategrey;font-size:1.2rem;color:darkcyan;font-weight:normal;padding:.5rem}input[type='button']:hover,input[type='color']:hover,input[type='radio']:hover{cursor:pointer}</style><script>window.addEventListener('load',function(){document.getElementById('submit-button').addEventListener('click',function(){for(var d=document.getElementById('duration').value,e=document.getElementById('dauer-inf').checked?0:document.getElementById('dauer-min').value,a=Array(3),f=document.getElementById('color').value,b=0,c=1;3>b;b++,c+=2)a[b]=parseInt(f.substr(c,2),16);fetch('/config?time='+d+'&duration='+e+'&r='+a[0]+'&g='+a[1]+'&b='+a[2])})});</script></head><body><form><fieldset id=formular><label for=umlaufzeit><h1>Umlaufzeit</h1><p><input id=duration name=umlaufzeit type=number step=0.2 min=0.2 max=10 value=4> Sekunden</p></label></fieldset><fieldset><label for=dauer><h1>Dauer</h1><p><input id=dauer-inf name=dauer type=radio value=Unendlich checked><label for=dauer-infinity>&infin;</label></p><p><input id=dauer-val name=dauer type=radio value=Zeitdauer><input id=dauer-min type=number value=10 min=1 max=100 step=1> Minuten</p></label></fieldset><fieldset><label for=farbe><h1>Farbe</h1><p><input id=color name=farbe type=color value=#E57373></p></label></fieldset><fieldset><label for=speichern><p><input id=submit-button name=speichern type=button value=Speichern></p></label></fieldset></form></body></html>");

#ifdef serial
  Serial.println("HTTP-Server: Website delivered");
#endif
}



// when new configuration received: store and activate it
void handleConfig( void ) {

#ifdef serial
  Serial.println("HTTP-Server: Configuration Received");
#endif

  uint16_t runtime = server.arg("time").toFloat();
  uint16_t duration = server.arg("duration").toInt();
  uint8_t r = server.arg("r").toInt();
  uint8_t g = server.arg("g").toInt();
  uint8_t b = server.arg("b").toInt();

#ifdef serial
  Serial.println("\t Runtime = "  + String(runtime));
  Serial.println("\t Duration = " + String(duration));
  Serial.println("\t Color-R = "  + String(r));
  Serial.println("\t Color-G = "  + String(g));
  Serial.println("\t Color-B = "  + String(b));
#endif

#ifdef serial
  Serial.println("HTTP-Server: Storing Value in EEPROM");
#endif

  // store values in EEPROM
  eeprom_config * Config = new eeprom_config();
  Config->setTime( runtime );
  Config->setDuration( duration );
  Config->setColorRed( r );
  Config->setColorGreen( g );
  Config->setColorBlue( b );
  delete Config;

#ifdef serial
  Serial.println("HTTP-Server: reinitialising LED Stripe");
#endif

  // Update config of the LED Stripe
  updateLEDConfig();

  // ACK
  server.send ( 201, "text/plain", "");
}
