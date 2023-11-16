/*Peter Rhoades
Saturday 10/04/21
Talk Back ThingHTTP Command 5 LED®
https://pastebin.com/t7wY1kYw  Developed by: Rahul Shrivastava
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
ESP8266WiFiMulti WiFiMulti;
int talkbacks_id = 42294;
int command_id = 22605644;
String talkbacks_api = "0BPAICBLD993VBVP";
String command_string="";
int LED = D0;
int DL = 500;

void setup() {
    Serial.begin(115200);
    Serial.flush();
    pinMode(D0, OUTPUT); 
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D7, OUTPUT);
    digitalWrite(D1, HIGH);//turn OFF
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH);
    wificonnect();         
}

void loop() {

        GETcommand();
        if(command_string == "D1")
            {
              digitalWrite(D1, LOW);//turn on the LED
              digitalWrite(D2, HIGH);// turn on the LED
              digitalWrite(D3, HIGH);// turn on the LED
              digitalWrite(D5, HIGH);// turn on the LED
              digitalWrite(D7, HIGH);// turn on the LED
              delay (DL);
              
            }
        else if(command_string == "D3")
            {
              digitalWrite(D3, LOW);// turn on the LED
              digitalWrite(D1, HIGH);//turn on the LED
              digitalWrite(D2, HIGH);// turn on the LED
              digitalWrite(D5, HIGH);// turn on the LED
              digitalWrite(D7, HIGH);// turn on the LED
              delay (DL);
            }
        else if(command_string == "D2")
            {
              digitalWrite(D2, LOW);// turn on the LED
              digitalWrite(D1, HIGH);//turn on the LED
              digitalWrite(D3, HIGH);// turn on the LED
              digitalWrite(D5, HIGH);// turn on the LED
              digitalWrite(D7, HIGH);// turn on the LED
              delay (DL);
            }
        else if(command_string == "D5")
            {
              digitalWrite(D5, LOW);// turn on the LED
              digitalWrite(D1, HIGH);//turn on the LED
              digitalWrite(D2, HIGH);// turn on the LED
              digitalWrite(D3, HIGH);// turn on the LED
              digitalWrite(D7, HIGH);// turn on the LED
              delay (DL);
            }
        else if(command_string == "D7")
            {
              digitalWrite(D7, LOW);// turn on the LED
              digitalWrite(D1, HIGH);//turn on the LED
              digitalWrite(D2, HIGH);// turn on the LED
              digitalWrite(D3, HIGH);// turn on the LED
              digitalWrite(D5, HIGH);// turn on the LED
              delay (DL);
            }
        else if(command_string == "LEDOFF")
            {
              digitalWrite(D1, HIGH);//turn on the LED
              digitalWrite(D2, HIGH);// turn on the LED
              digitalWrite(D3, HIGH);// turn on the LED
              digitalWrite(D5, HIGH);// turn on the LED
              digitalWrite(D7, HIGH);// turn on the LED
              delay (DL);
            }
        else if(command_string == "LEDON")
            {
              digitalWrite(D1, LOW);//turn on the LED
              digitalWrite(D2, LOW);// turn on the LED
              digitalWrite(D3, LOW);// turn on the LED
              digitalWrite(D5, LOW);// turn on the LED
              digitalWrite(D7, LOW);// turn on the LED
              delay (DL);
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

void GETcommand()
{
        HTTPClient http;    

        Serial.print("[HTTP] begin...\n");
        //"http://api.thingspeak.com/talkbacks/35233/commands/16599915.json?api_key=0E1160BEX9CSNU6V"
        String url = "http://api.thingspeak.com/talkbacks/";
               url += talkbacks_id;  
               url += "/commands/";
               url += command_id;
               url += ".json?api_key=";
               url += talkbacks_api;
        http.begin(url); //HTTP

        Serial.print("[HTTP] GET...\n");
        
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
                     if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
                int index_start = payload.indexOf("command_string\":\"") + 17;
                int index_stop = payload.indexOf("\",\"position");
                command_string = payload.substring(index_start, index_stop);
                Serial.println(command_string);  
                
                          
            }
   
        } 
        else 
        {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
       
    delay(1000);
 
}
