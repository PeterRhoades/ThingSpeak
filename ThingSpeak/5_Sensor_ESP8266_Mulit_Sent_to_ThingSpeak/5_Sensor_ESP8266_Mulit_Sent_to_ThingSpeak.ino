
/*Peter Rhoades©:
Friday 04/03/22:
Folder 5_Sensor_ESP8266_Mulit_Sent_to_ThingSpeak.
Mobil Scanner Inc Light(BH1750), Temperature & Humidity(MLX90614 & HDC1080)®
I2C device found at address 0x23-BH1750 Light Sensor: 
I2C device found at address 0x5A-MLX90614 Object Ambient & Object Temperature
I2C device found at address 0x40-HDC1080 Temperature & Humidity:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  
#include <Wire.h>
//#include <BH1750.h> //BH1750 lightMeter:
#include "ClosedCube_HDC1080.h" //HDC1080 Temperature & Humidity:
#include <Adafruit_MLX90614.h>  //MLX90614 Ambient Temperature & Object Temperature:
ClosedCube_HDC1080 hdc1080;
//BH1750 lightMeter; //BH1750 lightMeter:
String api_key = "RQ3WMTMWU1K901NS"; //API Key:
int field_no1 = 1; //MLX90614 Ambient Temperature:
int field_no2 = 2; //MLX90614 Object Temperature:
int field_no3 = 3; //HDC1080 Temperature:
int field_no4 = 4; //HDC1080 Humidity:
int field_no5 = 5; //BH1750 lightMeter:
String sent = " Channel Data Successful Sent";
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
int DL = 10000;
int SDL = 50;
int count = 1;
  
void setup() 
 {
  Serial.begin(9600);
  Wire.begin();
  //lightMeter.begin();
  hdc1080.begin(0x40);
  mlx.begin();
  wificonnect();
 }
void wificonnect()
 {
  WiFiMulti.addAP("VM6535101", "pzpt3DvVssfj");
  Serial.println(".....Conneting to Home WiFi.....");
  Serial.println();
  while(WiFiMulti.run()!=WL_CONNECTED){
  Serial.print("...");
  delay(500);  
 }
    Serial.println(".....Connected to Home WiFi.....");  //Serial.println ("[VM6535101]--[pzpt3DvVssfj]");// This line will execute if your device is connected to Access Pass
    Serial.println();
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
 }
void loop() 
 {
     Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
     Serial.println();
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no1;
         url += "=";
         int k = mlx.readAmbientTempC();
         url += mlx.readAmbientTempC();// passing the parameter to string, this value will reach cloud at field1
           Serial.print("Ambient: "); Serial.print(mlx.readAmbientTempC());  Serial.println("°C");
         url += "&field";
         url += field_no2;
         url += "=";
         url += mlx.readObjectTempC();
           Serial.print("Object: "); Serial.print(mlx.readObjectTempC()); Serial.println("°C");
         url += "&field";
         url += field_no3;
         url += "=";
         url += hdc1080.readTemperature();
           Serial.print("Temperature: "); Serial.print(hdc1080.readTemperature()); Serial.println("°C");
         url += "&field";
         url += field_no4;
         url += "=";
         url += hdc1080.readHumidity();
           Serial.print("Humidity: ");    Serial.print(hdc1080.readHumidity());  Serial.println("%"); 
        //url += "&field";
        //url += field_no5;
       //url += "=";
       //url += WiFi.localIP;
        //Serial.print(WiFi.localIP()); Serial.println(":"); 
        http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
           
  int x   = http.GET();// get method, returns a http code, -ve if access denied
if (x == 200)
  {
  Serial.print("Return Code = ");
  Serial.print(x);
  Serial.println(sent);
}else{
  Serial.println("Problem updating channel. HTTP error code " + String(x));
 }
  http.end();
  delay(DL);
 } 
