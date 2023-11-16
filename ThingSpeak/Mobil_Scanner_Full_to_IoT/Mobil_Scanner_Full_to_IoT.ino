/*Peter Rhoades©:
Monday 03/05/21:
Mobil Scanner Inc Light(BH1750), Laser distance(VL53L0X), Temperature-Humidity-Pressure(BME280 & HTU21) 
and Object Temperature(MLX90614) Readings®
I2C device found at address 0x23-BH1750 Light Sensor: 
I2C device found at address 0x29-Laser Ranger:
I2C device found at address 0x40-HTU Temperature & Humidity:
I2C device found at address 0x76-BME280 Temperature, Humidity & Pressure:
I2C device found at address 0x5A-Object Temperature:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_MLX90614.h> //0x5A Object Temperature:
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h> //0x23-BH1750 Light Sensor:
#include <VL53L0X.h> //0x29-Laser Ranger:
#include "Adafruit_HTU21DF.h" //0x44 SHT31 Temperature & Humidity:
#include <BME280I2C.h> //0x76-BME280 Temperature, Humidity & Pressure:
String api_key = "3C2ZJY4VNZ9E6D7R"; //API Key:
int field_no1 = 1; //Laser 0x23:
int field_no2 = 2; //Object Temperature 0x5A:
int field_no3 = 3; //BME280 Temperature 0x76:
int field_no4 = 4; //BME280 Himidity 0x76:
int field_no5 = 5; //HTU Temperature 0x40:
int field_no6 = 6; //HTU Himidity 0x40:
int field_no7 = 7; //BH1750 Light Sensor 0x23 :
int field_no8 = 8; //BME280 Pressure 00x76:
int DL = 1200;
ESP8266WiFiMulti WiFiMulti;
BH1750 lightMeter(0x23); //0x23 BH1750 Light Sensor: 
VL53L0X Lsensor; //0x29 Laser Ranger:
Adafruit_HTU21DF htu = Adafruit_HTU21DF(); //0x40 HTU Temperature & Humidity:
Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //0x5A Object Temperature:
BME280I2C bme; //0x76 BME280 Temperature & Himidity:

void setup() 
 {
  mlx.begin(); //Object Temperature 0x5A:
  Serial.begin(115200);
  Serial.flush();
  delay(50);
  Wire.begin();
  bme.begin(); //BME280 Temperature & Himidity 0x76:
  Lsensor.init(); //VL53L0X Laser 0x29:
  Lsensor.setTimeout(1500); //VL53L0X Laser 0x29:
  Lsensor.startContinuous(1000); //VL53L0X Laser 0x29:
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
    
    float temp(NAN), hum(NAN), pres(NAN);
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius);
    BME280::PresUnit presUnit(BME280::PresUnit_Pa);
    bme.read(pres, temp, hum, tempUnit, presUnit);
    float bmeC = temp;
    float bmeH = hum;
    float bmeP = pres; 
  float D = Lsensor.readRangeContinuousMillimeters()-45; //Laser 0x23 [F1}:
  GETsendD(D); //Laser 0x23:
  delay (DL);
  float L = lightMeter.readLightLevel(); //BH1750 Light Sensor 0x23 [F7]:
  GETsendL(L); //BH1750 Light Sensor 0x23 [F7]:
  delay (DL);
  float F = mlx.readObjectTempC(); //Object Temperature 0x5A [F2]:
  GETsendF(F); //Object Temperature 0x5A:
  delay (DL);
  float K = bmeC; //BME280 Temperature 0x76 [F3]:
  GETsendK(K); //BME280 Temperature 0x76:
  delay (DL);
  float M = bmeH; //BME280 Humidity 0x76 [F4]:
  GETsendM(M); //BME280 Humidity 0x76:
  delay (DL);
  float P = bmeP / 100; //BME280 Pressure 0x76 [F8]:
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
 
void GETsendD(float data) //Laser 0x23 [F1}:
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
  Serial.println("");
  Serial.println("");
  Serial.print("(VL53L0X)  Distance: "); Serial.print(data); Serial.println("mm:");
 }
void GETsendF(float data) //Object Temperature 0x5A [F2]:
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
  Serial.print("(MLX90614) Object Temperature: "); Serial.print(data); Serial.println("°C"); 
  Serial.print("(MLX90614) Ambient Temperature: "); Serial.print(mlx.readAmbientTempC()); Serial.println("°C");
 }
void GETsendK(float data) //BME280 Temperature 0x76 [F3]:
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
 Serial.print("(BME280)   Temperature: "); Serial.print(data); Serial.println("°C");
 }
void GETsendM(float data) //BME280 Humidity 0x76 [F3]:
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
 Serial.print("(BME280)   Humidity: "); Serial.print(data); Serial.println("%");
 }
void GETsendT(float data) //HTU Temperature 0x40 [F5]:
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
 Serial.print("(HTU21)    Temperature: "); Serial.print(data);  Serial.println("°C");
 }
void GETsendR(float data) //HTU Humidity 0x40 [F6]:
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
 Serial.print("(HTU21)    Humidity: "); Serial.print(data); Serial.println("%");
 }
void GETsendL(float data) //BH1750 Light Sensor 0x23 [F7]:
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
  Serial.print("(BH1750)   Light: "); Serial.print(data); Serial.println("Lx"); 
 }
void GETsendG(float data) //BH1750 Light Sensor 0x23 [F7]:
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
 Serial.print("(BH1750)   Light: "); Serial.print(data); Serial.println("Lx"); 
 }
 void GETsendP(float data) //BME280 Temperature 0x76 [F8]:
 {
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no8;
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
 Serial.print("(BME280)   Pressure: "); Serial.print(data); Serial.println("mbar"); 
 }
  
