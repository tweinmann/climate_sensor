// Libraries
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include <DNSServer.h>
#include <WiFiManager.h>
#include "DHT.h" 

// set D2 (= pin 4) on NodeMCU V1.0
#define DHTPIN 4    

// set DHT sensor Type (=11)
#define DHTTYPE DHT11  

// init DHT sensor
DHT dht(DHTPIN, DHTTYPE); 

// init web server
ESP8266WebServer server(80);
 
void setup() {

  // init serial port
  Serial.begin(9600);

  // init WIFI manager (will either load config from eprom or launch setup network SSID="climate_sensor" for initial configuration)
  WiFiManager wifiManager;
  wifiManager.autoConnect("climate_sensor");

  // register handler for "/humidity"
  server.on("/humidity", []() {   //Define the handling function for the path
    server.send(200, "text/plain", String(dht.readHumidity()));
  });
 
  // register handler for "/temperature"
  server.on("/temperature", []() {   //Define the handling function for the path
    server.send(200, "text/plain", String(dht.readTemperature()));
  });

  // register handler for "/" 
  server.on("/", []() {   //Define the handling function for the path
    server.send(200, "text/html", "<a href=\"/humidity\">humidity</a>|<a href=\"/temperature\">temperature</a>");
  });

  // start web server
  server.begin();                    
  Serial.println("Server listening");

  // start sensor
  dht.begin(); 

}
 
void loop() {
  
  //Handling of incoming requests
  server.handleClient();       
 
}
 
