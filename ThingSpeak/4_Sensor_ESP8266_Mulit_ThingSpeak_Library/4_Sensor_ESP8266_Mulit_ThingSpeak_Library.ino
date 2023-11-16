

/*Peter Rhoades©:
Friday 29/04/22:
Folder 4_Sensor_ESP8266_Mulit_ThingSpeak_Library.
Scanner Inc Temperature & Humidity(MLX90614 & HDC1080)®:
I2C device found at address 0x5A-MLX90614 Object Ambient & Object Temperature:
I2C device found at address 0x40-HDC1080 Temperature & Humidity:
*/

#include <ESP8266WiFi.h>
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros
#include "ClosedCube_HDC1080.h" //HDC1080 Temperature & Humidity:
#include <Adafruit_MLX90614.h>  //MLX90614 Ambient Temperature & Object Temperature:
ClosedCube_HDC1080 hdc1080;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
WiFiClient  client;
unsigned long myChannelNumber = 1659042;
const char * myWriteAPIKey = "RQ3WMTMWU1K901NS";
int DL = 2000;
int count = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  hdc1080.begin(0x40);
  mlx.begin();
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  wificonnect();
 }
void wificonnect()
 {
  WiFi.begin("VM6535101", "pzpt3DvVssfj");
  Serial.println(".....Conneting to Home WiFi.....");
  Serial.println();
  while(WiFi.status() != WL_CONNECTED){
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
 int AmbientTempC = mlx.readAmbientTempC();
 int ObjectTempC  = mlx.readObjectTempC();
 int hdc1080Temp = hdc1080.readTemperature();
 int hdc1080Humi = hdc1080.readHumidity();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                delay(DL);
  Serial.print("Ambient Temperature "); Serial.print(mlx.readAmbientTempC());    Serial.println("°c\n");              
  Serial.println("..........................................................................\n");
  
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                delay(DL);
  Serial.print("Object Temperature ");  Serial.print(mlx.readObjectTempC());     Serial.println("°c\n");              
  Serial.println("..........................................................................\n");
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                delay(DL);
  Serial.print("HDC1080 Temperature "); Serial.print(hdc1080.readTemperature()); Serial.println("°c\n");
  Serial.println("..........................................................................\n");
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                delay(DL);
Serial.print("HDC1080 Humidity ");    Serial.print(hdc1080.readHumidity());    Serial.println("%\n"); 
Serial.println("..........................................................................\n");              
ThingSpeak.setField(1, AmbientTempC);
ThingSpeak.setField(2, ObjectTempC);
ThingSpeak.setField(3, hdc1080Temp);
ThingSpeak.setField(4, hdc1080Humi);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel Update Successful:\n");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
 }
