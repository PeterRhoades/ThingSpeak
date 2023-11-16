/*Peter Rhoades©:
Sunday 14/11/21:
Receive data from thingSpeak Channel Inc SHT21 Temperature & Humidity®: 
Developed by: Rahul Shrivastava
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;
String readAPIkey = "PJPXZGAIKRFQUC8R";// Read API Key of ThingSpeak channel:
String channel_ID = "1341661";// Read Chanel ID of ThingSpeak channel:
String field_N1 = "1";//ThingSpeak Fields:
String field_N2 = "2";//ThingSpeak Fields:
String result_N = "1";// Unmber of Results:
int LD = 150000; //Delay Period 
int starT = 25;
int enD = 30;
void setup() {
    Serial.begin(9600);
    wificonnect(); 
 }

void loop() 
 {
 GETreceive();
 }

void wificonnect()
  {
    WiFiMulti.addAP("VM5774222", "b3rVddgtbvmp");
    delay(1000);
    Serial.println("Conneting to Home WiFi");
    Serial.println("");
    delay(1000);
    while(WiFiMulti.run()!=WL_CONNECTED)
    {
      Serial.print(".");
      digitalWrite(D0, LOW);
      delay(100);
      digitalWrite(D0, HIGH);
      delay(100);
    }
     delay(1000);
    Serial.println("Connected to Home WiFi...");// This line will execute if your device is connected to Access Pass
    Serial.println("Sunday 14/11/21, Receive data from thingSpeak Channel Inc SHT21 Temperature & Humidity:");
    Serial.println("");
    delay(1000);
  }

void GETreceive()
{
        HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N1;
               url += ".json?api_key=";
               url += readAPIkey;
               url += "&results=";
               url += result_N;
       http.begin(wifiClient,url); //HTTP
       int httpCode = http.GET();
       if(httpCode > 0) {
  String payload = http.getString();
  int begin_b = payload.indexOf("\"entry_id");
  String field_data_string = payload.substring(begin_b+starT,begin_b+enD);
  float field_data = field_data_string.toFloat();
  if (field_data > 0.00)
  {
  Serial.println ("   Summer House ");
  Serial.print ("(SHT31)   Temperature "); Serial.print(field_data); Serial.println("°C");
  delay (LD);
 }
  http.end();
 }
 {
   HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N2;
               url += ".json?api_key=";
               url += readAPIkey;
               url += "&results=";
               url += result_N;
       http.begin(wifiClient,url); //HTTP
       int httpCode = http.GET();
       if(httpCode > 0) {
  String payload = http.getString();
  int begin_b = payload.indexOf("\"entry_id");
  String field_data_string = payload.substring(begin_b+starT,begin_b+enD);
  float field_data = field_data_string.toFloat();
  if (field_data > 0.00)
  {
  Serial.print ("(SHT31)   Humidity "); Serial.print(field_data); Serial.println("%");
  Serial.println();
  delay (LD);
 }
  http.end();
 }
}
}
