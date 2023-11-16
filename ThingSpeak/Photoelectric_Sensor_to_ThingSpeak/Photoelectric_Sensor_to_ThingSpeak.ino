/*Peter Rhoades©:
Saturday 12/03/22:
Folder Photoelectric_Sensor_to_ThingSpeak:
Sharp GP2Y1010AU0F Onboard for Measuring PM2.5 Air Purifier®:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> 
#include <PMsensor.h> 
PMsensor PM;
String api_key = "0VDAOTY3VRGDS08V"; //API Key:
int field_no1 = 1; //filter_Data:
int field_no2 = 2; //noFilter_Data:
int DL = 10000;
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;

void setup() {
  Serial.begin(9600);
  PM.init(D3, A0);
  wificonnect();
 }
 void wificonnect()
 {
  WiFiMulti.addAP("VM6535101", "pzpt3DvVssfj");
  Serial.println(".....Conneting to Home WiFi.....");
  Serial.println();
  while(WiFiMulti.run()!=WL_CONNECTED)
 {
      digitalWrite(D0, LOW);
      delay(100);
      digitalWrite(D0, HIGH);
      delay(100);
 }
    Serial.println(".....Connected to Home WiFi.....");  //Serial.println ("[VM6535101]--[pzpt3DvVssfj]");// This line will execute if your device is connected to Access Pass
    Serial.println();
 }
void loop() {
  Serial.println("=================================");
  Serial.println("Read PM2.5");
  float filter_Data = PM.read(0.1);
  float noFilter_Data = PM.read();
  Serial.print("Filter : ");
  Serial.println(filter_Data);
  Serial.print("noFilter : ");
  Serial.println(noFilter_Data);
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no1;
         url += "=";
         url += filter_Data; //passing the parameter to string, this value will reach cloud at field3
         url += "&field";
         url += field_no2;
         url += "=";
         url += noFilter_Data; //passing the parameter to string, this value will reach cloud at field4
  Serial.println();
         http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  http.end();
  delay(DL);
 } 
