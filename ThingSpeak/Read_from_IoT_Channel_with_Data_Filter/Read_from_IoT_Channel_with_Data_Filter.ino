/*
Problem Statement: Receive data from thingSpeak Channel  
                   WiFi Credentials are not hardcoded, They can be updated in real time using Tzapu WiFiManager Library
Developed by: Rahul Shrivastava
*********************************
*/

#include <Arduino.h>//
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
#include <DNSServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
String readAPIkey = "SJED4JK0UWO1PTEC";// Read API Key of ThingSpeak channel
String channel_ID = "1331323";
String field_N = "1";
String result_N = "1";
        //"http://api.thingspeak.com/channels/1024134/fields/2.json?api_key=702L9HBEV9F88HHV&results=1"

void setup() {
    Serial.begin(115200);
    Serial.flush();
    pinMode(D0, OUTPUT);
    pinMode (D6, OUTPUT);
    wificonnect(); 
            
}

void loop() {

        float temperature = GETreceive();
        if (temperature>23)
        {
          digitalWrite(D0, LOW);
          digitalWrite(D6, HIGH);  
        }
        else
        {
           digitalWrite(D0, HIGH);
           digitalWrite(D6, LOW);
             
        }
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


float GETreceive()
{
        HTTPClient http;    
 
        Serial.print("[HTTP] begin...\n");
       
        //"http://api.thingspeak.com/channels/963373/fields/1.json?api_key=28WYJLR74BJ9ZKAT&results=1"
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N;
               url += ".json?api_key=";
               url += readAPIkey;
               url += "&results=";
               url += result_N;
               Serial.println(url);
        http.begin(url); //HTTP
 
        Serial.print("[HTTP] GET...\n");
       
        // start connection and send HTTP header
        int httpCode = http.GET();
 
        // httpCode will be negative on error
       
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
 
                if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println("..........................................................................");
                Serial.println(payload);
                Serial.println("..........................................................................");
                delay(2000); 
             
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+26,begin_b+30);
                float field_data = field_data_string.toFloat();
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                Serial.println ();
                
                return(field_data);
                
                delay(2000);
             }
         }
        else
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
 
        http.end();
     
    delay(2000); 
     
}
