/*Peter Rhoades:
Monday 01/05/21:
Mobil Scanner Inc Sound, Light(BH1750), Laser distance(VL53L0X), Temperature Ambient(SHT31&DallasTemperature) and Object(MLX90614) Readings®
I2C device found at address 0x23:
I2C device found at address 0x29:
I2C device found at address 0x5A:
I2C device found at address 0x44:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MLX90614.h>
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"
#include <BH1750.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <VL53L0X.h>
#define ONE_WIRE_BUS D4
String api_key = "VEBS82JPJD8VMVBO";
int field_no1 = 1; //Light: 0x23:
int field_no2 = 2; //Object Temperature 0x5A:
int field_no3 = 3; //Dallas Temperature D4:
int field_no4 = 4; //Dust Sensor A0:
int field_no5 = 5; //Laser 0x29:
int field_no6 = 6; //SHT31 Temperature 0x44:
int field_no7 = 7; //SHT31 Himidity 0x44:
int dustPin=A0;
int sensorValue = 0; 
int val;
int DL = 1000;
float dustVal=0; 
int ledPower=D5;
int delayTime=280;
int delayTime2=40;
float offTime=9680;
BH1750 lightMeter(0x23);
ESP8266WiFiMulti WiFiMulti;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
VL53L0X Lsensor;
Adafruit_SHT31 sht31 = Adafruit_SHT31();


void setup() 
 {
  Serial.begin(115200);
  pinMode(ledPower,OUTPUT);
  pinMode(dustPin, INPUT);
  sensors.begin();
  mlx.begin(); //IR Temperature 0x5A:
  Wire.begin();
  sht31.begin();
  Lsensor.init(); //VL53L0X Laser:
  Lsensor.setTimeout(1500); //VL53L0X Laser:
  Lsensor.startContinuous(1000); //VL53L0X Laser:
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
 }else {
    Serial.println(F("Error initialising BH1750"));
 }
wificonnect();
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
void loop() 
 {
   digitalWrite(ledPower,LOW); 
   delayMicroseconds(delayTime);
   dustVal=analogRead(dustPin); 
   delayMicroseconds(delayTime2);
   digitalWrite(ledPower,HIGH); 
   delayMicroseconds(offTime);
   delay(1200);
if (dustVal>36.455)
  Serial.println("");
  float D = Lsensor.readRangeContinuousMillimeters()-45;
  GETsendD(D);
  float F = mlx.readObjectTempC();
  GETsendF(F);
  sensors.requestTemperatures();
  float T = sensors.getTempCByIndex(0);
  GETsendT(T);
  float K = sht31.readTemperature();
  GETsendK(K);
  float M = sht31.readHumidity();
  GETsendM(M);
  float L = lightMeter.readLightLevel();
  GETsendL(L);
  float G = lightMeter.readLightLevel();
  GETsendG(G);
  float R = dustVal=analogRead(dustPin);
  GETsendR(R);
 
 }
 void GETsendD(float data) //Laser:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no1;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
  Serial.println("");
  Serial.print("(VL53L0X)  Distance: "); Serial.print(data); Serial.println("mm:");
  delay (1200);
 }
 void GETsendF(float data) //Object Temperature:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no2;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
  Serial.printf("Failed to connect to server");
 }         
  http.end();
  Serial.println("");
  Serial.print("(MLX90614) Object Temperature: "); Serial.print(data); Serial.println("*C"); 
  delay (1200);   
 }
 void GETsendT(float data) //Ambient Temperature:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no3;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
         }         
 http.end();
 Serial.println("");
 Serial.print("(Dallas)   Temperature: "); Serial.print(data); Serial.println("*C");
 delay (1200);
 }
 void GETsendL(float data) //Light:
 {
 HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
 String url =  "http://api.thingspeak.com/update?api_key=";
        url += api_key;
        url += "&field";
        url += field_no4;
        url += "=";// Creating HTTP Query/GET Method
        url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
  Serial.printf("Failed to connect to server");
 }         
  http.end();
  Serial.println("");
  Serial.print("(BH1750)   Light: "); Serial.print(data); Serial.println("-LUX"); 
  delay (1200);
 }


void GETsendG(float data) //Dust:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no4;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end();
   Serial.println("");
  Serial.print("(BH1750)   Light: "); Serial.print(data); Serial.println("-LUX"); 
  delay (1200);
  //Serial.println("");
  //Serial.print ("(PM2.5)    Dust Level "); Serial.println(data);
  //delay (1200);
 }
 
 
 
 void GETsendK(float data) //SHT31 Temperature:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no6;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
 Serial.println("");
 Serial.print("(SHT31)    Temperature: "); Serial.print(data);  Serial.println("*C");
 delay (1200);
 }
 
 void GETsendM(float data) //SHT31 Humidity:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no7;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
 Serial.println("");
 Serial.print("(SHT31)    Humidity: "); Serial.print(data); Serial.println("%");
  }
  
  void GETsendR(float data) //SHT31 Humidity:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no5;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
 Serial.println("");
 Serial.print("(A0)       Dust: "); Serial.print(data); Serial.println("ppm");
  }
