#include <ESP8266WiFi.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>

char* wifiName = "WIFI_BASCULAS";

#define pinLedWifi D4

WiFiManager wifiM;
Ticker ticWifiLed;

void ParpadeoLedWifi();
void startWifi();


void startWifi(){
  pinMode(pinLedWifi,OUTPUT);
  Serial.println("Conectando a la wifi...");
  
  ticWifiLed.attach(0.2,ParpadeoLedWifi);
  
  
  //wifiM.resetSettings();
  if(! wifiM.autoConnect(wifiName)){
      Serial.println("Fallo en la conexión...");
      ESP.reset();
      delay(1000);
  }
  Serial.println("Ya estas conectado");
  ticWifiLed.detach();
  digitalWrite(pinLedWifi,HIGH);
}

void ParpadeoLedWifi() {
  byte estado = digitalRead(pinLedWifi);
  digitalWrite(pinLedWifi, !estado);
}
