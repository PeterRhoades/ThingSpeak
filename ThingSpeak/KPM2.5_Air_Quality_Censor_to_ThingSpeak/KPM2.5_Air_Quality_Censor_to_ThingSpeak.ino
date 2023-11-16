/*Peter Rhoades©:
Friday 12/03/22:
Folder KPM2.5_Air_Quality_Censor_to_ThingSpeak:
Sharp GP2Y1010AU0F Onboard for Measuring PM2.5 Air Purifier®:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> 
String api_key = "0VDAOTY3VRGDS08V"; //API Key:
int field_no3 = 3; //filter_Data:
int field_no4 = 4; //noFilter_Data:
int DL = 10000;
int dustPin=A0;
float dustVal=0; 
int ledPower=D3;
int delayTime=280;
int delayTime2=40;
float offTime=9680;
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;

void setup()
 {
Serial.begin(9600);
wificonnect();
 }
void wificonnect()
 {
  WiFiMulti.addAP("VM5774222", "b3rVddgtbvmp");
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

void loop(){
digitalWrite(ledPower,LOW); 
delayMicroseconds(delayTime);
dustVal=analogRead(dustPin); 
delayMicroseconds(delayTime2);
digitalWrite(ledPower,HIGH); 
delayMicroseconds(offTime);
  if (dustVal>36.455)
Serial.print("KPM2.5 Air Quality Censor ");
Serial.println((float(dustVal/1024)-0.0356)*120000*0.035);
Serial.print("Read A0 ");
Serial.println(analogRead (A0));
HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no3;
         url += "=";
         url += (float(dustVal/1024)-0.0356)*120000*0.035; //passing the parameter to string, this value will reach cloud at field3
         url += "&field";
         url += field_no4;
         url += "=";
         url += analogRead (A0); //passing the parameter to string, this value will reach cloud at field4
  Serial.println();
         http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  http.end();
  delay(DL);
 } 
