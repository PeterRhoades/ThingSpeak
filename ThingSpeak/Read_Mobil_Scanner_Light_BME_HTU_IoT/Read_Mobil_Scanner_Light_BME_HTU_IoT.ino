/*Peter Rhoades©:
Saturday 28/11/21:
Mobil Scanner Inc Light(BH1750), Temperature-Humidity-Pressure(BME280 & HTU21)®
I2C device found at address 0x23-BH1750 Light Sensor: 
I2C device found at address 0x40-HTU Temperature & Humidity:
I2C device found at address 0x76-BME280 Temperature, Humidity & Pressure:
25/08/21 Pressure calculation adjusted to match BBC Weather: 
01/09/21 Update Time to ThingSpeak Increassed to 3 Seconds:
11/11/21 Lines added or changed:  #include <WiFiClient.h>:
                                  WiFiClient wifiClient;:
                                  http.begin(wifiClient,url);// initiate HTTP Request to establish connection:
Saturday 28/11/21  int starT = 27; & int enD = 33; Added to alter payload.substring from 1 location not 6:
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;
String readAPIkey = "S3XJS9HNWE8F23DS";// Read API Key of ThingSpeak channel:
String channel_ID = "1396346";// Read Chanel ID of ThingSpeak channel:
String field_N1 = "1";
String field_N2 = "2";
String field_N3 = "3"; //ThingSpeak Fields:
String field_N4 = "4";
String field_N5 = "5";
String field_N6 = "6";
String result_N = "1";// Unmber of Results:
int LD = 3000; //Delay Period 
int starT = 25; int enD = 33; //payload.substring:
void setup() {
    Serial.begin(115200);
    wificonnect(); 
 }
void loop() 
 {
 GETreceive();
 }

void wificonnect()
  {
    WiFiMulti.addAP("VM6535101", "pzpt3DvVssfj");
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
    Serial.println("Sunday 14/11/21, Receive data BH1750 Light, SHT21 & (BME280) Temperature & Humidity (Pressure):");
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
  Serial.println ("   Mobile Sensor ");
  Serial.println();
  Serial.print ("(BME280)   Temperature "); Serial.print(field_data); Serial.println("°C");
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
  Serial.print ("(BME280)   Humidity "); Serial.print(field_data); Serial.println("%");
  delay (LD);
 }
  http.end();
 }
{
   HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N3;
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
  Serial.print ("(BME280)   Pressure "); Serial.print(field_data); Serial.println("mbar");
  Serial.println();
  delay (LD);
 }
  http.end();
 }
{
   HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N4;
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
  Serial.print ("(HTU21)    Temperature "); Serial.print(field_data); Serial.println("°C");
  delay (LD);
 }
  http.end();
 }
{
   HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N5;
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
  Serial.print ("(HTU21)    Humidity "); Serial.print(field_data); Serial.println("%");
  Serial.println();
  delay (LD);
 }
  http.end();
 }
{
   HTTPClient http;    
       String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID; // 
               url += "/fields/";
               url += field_N6;
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
  Serial.print ("(BH1750)   Light: "); Serial.print(field_data); Serial.println("Lux");
  Serial.println();
  delay (LD);
 }
  http.end();
 }
}
 }
}
 }
}
 }
