#include <ESP8266WiFi.h>
#include <strings_en.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h >
#include <Ticker.h>

#define pinLedWifi  D4
char* wifiName = "WIFI_CONECT_EJC"; // Nombre de la red Wifi

void parpadeoLedWifi();
void MyWiFiConnect();
void printMessageWiFi();

// Instancia a la clase Ticker para parpadear led indicador de conexión wifi
Ticker ticker_wifi;

void parpadeoLedWifi(){
  // Cambiar de estado el LED
  byte estado = digitalRead(pinLedWifi);
  digitalWrite(pinLedWifi, !estado);
}


void printMessageWiFi(){  
  Serial.println("\n********************************************");
  Serial.print("Conectado a la red WiFi: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("macAdress: ");
  Serial.println(WiFi.macAddress());
  Serial.println("*********************************************");
}

void MyWiFiConnect(){  
  pinMode(pinLedWifi, OUTPUT); // Modo del pin
  Serial.println("Conectando a la wifi...");
  ticker_wifi.attach(0.2, parpadeoLedWifi);// Empezamos el temporizador que hará parpadear el LED
 
  // Creamos una instancia de la clase WiFiManager
  WiFiManager wifiManager;
 
  // Descomentar para resetear configuración
  //wifiManager.resetSettings();
 
  // Cremos AP y portal cautivo y comprobamos si
  // se establece la conexión
   if(! wifiM.autoConnect(wifiName)){
      Serial.println("Fallo en la conexión...");
      ESP.reset();
      delay(1000);
  }
  printMessageWiFi();  
  ticker_wifi.detach(); // Eliminamos el temporizador
  digitalWrite(pinLedWifi, HIGH); // Apagamos el LED
}
