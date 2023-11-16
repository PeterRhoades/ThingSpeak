/*Peter Rhoades©:
Wednesday 02/02/22:
Mobil Scanner Inc Light(BH1750), Temperature-Humidity-Pressure(BME280 & HTU21)®
I2C device found at address 0x23-BH1750 Light Sensor: 
I2C device found at address 0x40-HTU Temperature & Humidity:
I2C device found at address 0x76-BME280 Temperature, Humidity & Pressure:
25/08/21 Pressure calculation adjusted to match BBC Weather: 
11/11/21 Lines added or changed:  #include <WiFiClient.h>
                                  WiFiClient wifiClient;
                                  http.begin(wifiClient,url);// initiate HTTP Request to establish connection*/
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  //Line added 11/11/21:
#include <BH1750.h> //0x23-BH1750 Light Sensor:
#include "Adafruit_HTU21DF.h" //0x44 SHT31 Temperature & Humidity:
#include <BME280I2C.h> //0x76-BME280 Temperature, Humidity & Pressure:
String api_key = "IOKJYS8558STU0YW"; //API Key:
int field_no1 = 1; //BME280 Temperature 0x76:
int field_no2 = 2; //BME280 Himidity 0x76:
int field_no3 = 3; //BME280 Pressure 00x76:
int field_no4 = 4; //HTU Temperature 0x40:
int field_no5 = 5; //HTU Himidity 0x40:
int field_no6 = 6; //BH1750 Light Sensor 0x23 :
int DL = 1000;
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient; //Line added 11/11/21:
BH1750 lightMeter(0x23); //0x23 BH1750 Light Sensor: 
Adafruit_HTU21DF htu = Adafruit_HTU21DF(); //0x40 HTU Temperature & Humidity:
BME280I2C bme; //0x76 BME280 Temperature & Himidity:

void setup() 
 {
  Serial.begin(115200);
  Wire.begin();
  bme.begin(); //BME280 Temperature & Himidity 0x76:
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750 Advanced begin"));
 }else {
    Serial.println(F("Error initialising BH1750"));
 }
 if (!htu.begin()) {
    Serial.println("Couldn't find sensor!");
    while (1);
 }
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
    Serial.println("Peter Rhoades Monday 25/08/21 Mobil Scanner Inc Light(BH1750), Temperature-Humidity-Pressure(BME280 & HTU21)");
    Serial.println("I2C device at address 0x23-BH1750 Light Sensor: ");
    Serial.println("I2C device at address 0x40-HTU Temperature & Humidity:");
    Serial.println("I2C device at address 0x76-BME280 Temperature, Humidity & Pressure:");
    Serial.println("25/08/21 Pressure calculation adjusted to match BBC Weather:"); 
    Serial.println("11/11/21 Lines added or changed:  #include <WiFiClient.h>");
    Serial.println("                                  WiFiClient wifiClient;");
    Serial.println("                                  http.begin(wifiClient,url);");
    delay (DL);
 }
void loop() 
 {
    
    float temp(NAN), hum(NAN), pres(NAN);
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);
    bme.read(pres, temp, hum, tempUnit, presUnit);
    float bmeC = temp;
    float bmeH = hum;
    float bmeP = pres; 
  float K = bmeC; //BME280 Temperature 0x76 [F3]:
  GETsendK(K); //BME280 Temperature 0x76:
  delay (DL);
  float M = bmeH; //BME280 Humidity 0x76 [F4]:
  GETsendM(M); //BME280 Humidity 0x76:
  delay (DL);
  float P = bmeP / 100 + 13; //BME280 Pressure 0x76 [F8]:
  GETsendP(P); //BME280 Pressure 0x76 [F8]:
  delay (DL);
  float T = htu.readTemperature(); //HTU Temperature 0x40 [F5]:
  GETsendT(T); //HTU Temperature 0x40:
  delay (DL);
  float R = htu.readHumidity(); //HTU Humidity 0x40 [F6]:
  GETsendR(R); //HTU Humidity 0x40:
  delay (DL);
  float G = lightMeter.readLightLevel(); //BH1750 Light Sensor 0x23 [F7]:
  GETsendG(G); //BH1750 Light Sensor 0x23 [F7]:
  delay (DL);
 
 }
 void GETsendK(float data) //BME280 Temperature 0x76 [F1]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no1;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
         }         
 http.end();
 Serial.println("");
 Serial.println("      Mobil Scanner");
 Serial.println();
 Serial.print("(BME280)   Temperature: "); Serial.print(data); Serial.println("°C");
 }
void GETsendM(float data) //BME280 Humidity 0x76 [F2]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no2;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
 Serial.print("(BME280)   Humidity: "); Serial.print(data); Serial.println("%");
 }
void GETsendT(float data) //HTU Temperature 0x40 [F4]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no4;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection [Line Changed 11/11/21]: 
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end(); 
 Serial.println("");
 Serial.print("(HTU21)    Temperature: "); Serial.print(data);  Serial.println("°C");
 }
void GETsendR(float data) //HTU Humidity 0x40 [F5]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no5;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 } 
 http.end();         
 Serial.print("(HTU21)    Humidity: "); Serial.print(data); Serial.println("%");
 }
void GETsendG(int data) //BH1750 Light Sensor 0x23 [F6]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no6;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end();
 Serial.println("");
 Serial.print("(BH1750)   Light: "); Serial.print(data); Serial.println("-Lux"); 
 }
 void GETsendP(int data) //BME280 Temperature 0x76 [F3]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no3;
         url += "=";// Creating HTTP Query/GET Method
         url += data;// passing the parameter to string, this value will reach cloud at field1
  http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  if(httpCode > 0) 
 {
 }else{
 Serial.printf("Failed to connect to server");
 }         
 http.end();
 Serial.print("(BME280)   Pressure: "); Serial.print(data); Serial.println("mbar"); 
 }
  
