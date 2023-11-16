/*
Problem Statement: Upload LM35 Sensor Data to your channel on ThingSpeak.com using POST HTTP Method
Developed by: Rahul Shrivastava
*********************************
Pin Connections
LM35    NODEMCU
Vcc(1)   3.3V
GND(3)   GND
OUT(2)   A0
*********************************
*/
#include <Arduino.h>//
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
#include <DNSServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <Wire.h>
 WiFiClient client;
String apiKey = "28PIARBD3PQXUYEZ";     //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";

void setup() 
 {
       Serial.begin(115200);
       delay(10);
       Serial.flush();
       wificonnect();
       mlx.begin();
 }
 void loop() 
 {  
   float tempData = mlx.readObjectTempC();
   POSTSend(tempData); 
   Serial.println (".............................................:");
   Serial.println (mlx.readObjectTempC()); 
   Serial.println (".............................................:");            
 }
void wificonnect()
 {
    WiFiMulti.addAP("VM6535101", "pzpt3DvVssfj");
    Serial.println("Conneting");
    while(WiFiMulti.run()!=WL_CONNECTED)
    {
      Serial.print(".");
      digitalWrite(D0, LOW);
      delay(100);
      digitalWrite(D0, HIGH);
      delay(100);
    }
     Serial.print("Connected to HOTSPOT..\n");// This line will execute if your device is connected to Access Pass
  }

void POSTSend(float data)
 {
 if (client.connect(server,80))
 {  
 String postStr = apiKey;
 postStr +="&field1=";
 postStr += data;
 postStr += "\r\n\r\n";
 
 client.print("POST /update HTTP/1.1\n");
 client.print("Host: api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(postStr.length());
 client.print("\n\n");
 client.print(postStr);
 delay(500);
 String line="";
 while (client.available())
 { 
  line = client.readStringUntil('\r'); 
  Serial.print(line);                            }                          
 }
  client.stop();
  Serial.println("Waiting...");
  delay(2000);  
 }
 
