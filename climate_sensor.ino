#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include <DNSServer.h>
#include <WiFiManager.h>
#include "DHT.h" //DHT Bibliothek laden

#define DHTPIN 4 //Der Sensor wird an PIN 2 angeschlossen    
#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

ESP8266WebServer server(80);
 
void setup() {
 
  Serial.begin(9600);

  WiFiManager wifiManager;
  wifiManager.autoConnect("climate_sensor");
 
  server.on("/humidity", []() {   //Define the handling function for the path
  
    server.send(200, "text/plain", String(dht.readHumidity()));
 
  });
 
  server.on("/temperature", []() {   //Define the handling function for the path
  
    server.send(200, "text/plain", String(dht.readTemperature()));
 
  });

  server.on("/", []() {   //Define the handling function for the path
  
    server.send(200, "text/html", "<a href=\"/humidity\">humidity</a>|<a href=\"/temperature\">temperature</a>");
 
  });

  server.begin();                    //Start the server
  Serial.println("Server listening");
 
  dht.begin(); //DHT11 Sensor starten

}
 
void loop() {

  server.handleClient();         //Handling of incoming requests
 
}
 
