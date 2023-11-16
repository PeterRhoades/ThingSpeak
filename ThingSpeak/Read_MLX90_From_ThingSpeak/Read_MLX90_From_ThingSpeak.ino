/*Peter Rhoades©:
Saturday 19/12/22:
Read data from thingSpeak Channel inc TDS,Dallas,DHT22,BH1750,OLED Print®: 
Folder TDS_Dallas_DHT22_BH1750_Read_ThingSpeak_OLED_Print:
Developed by: Rahul Shrivastava using ThingSpeak Library:
*/
#include "SH1106Wire.h" //OLED Display Driver:
#include <WiFi.h>
#include "ThingSpeak.h" //Always Include ThingSpeak Header File: 
char ssid[] = "VM6535101"; //Network SSID: 
char password[] = "pzpt3DvVssfj"; //Network Password:
WiFiClient  client;
unsigned long ReadChannelNumber = 1396346; //Read Channel Number:
const char * ReadAPIKey = "IOKJYS8558STU0YW"; //and API Key:
int DL = 1000;
SH1106Wire display(0x3c, SDA, SCL); //OLED Display Driver:

void setup()
{
  Serial.begin(9600);
  Serial.println("In Setup");
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Serial.println("MLX90_ThingSpeak");
      display.init(); //Initialize OLED Display Driver:
      display.flipScreenVertically(); //OLED Display Command:
      display.setFont(ArialMT_Plain_10); //OLED Display Command:
      display.setTextAlignment(TEXT_ALIGN_LEFT); //OLED Display Command:
      display.drawString(15, 10, "ThingSpeak Reciver"); 
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 30, "ESP32 With OLED Display");
      display.display();
  wificonnect();
 }
 
void wificonnect()
 {
 WiFi.begin(ssid, password);
  Serial.println(".....Conneting to Home WiFi.....");
   while(WiFi.status() != WL_CONNECTED){
  Serial.print("...");
 delay(500);  
 }
 Serial.println();
  Serial.print(WiFi.SSID());
   Serial.print(".......");
    Serial.println(WiFi.localIP());
     Serial.println("");
    Serial.println("Read_ThingSpeak_OLED_Print:");
  Serial.println('\n'); 
 delay(500);
 }

void loop()
{
   float tempC = ThingSpeak.readFloatField(ReadChannelNumber, 4, ReadAPIKey);
   int statusCode = ThingSpeak.getLastReadStatus();
 if(statusCode == 200)
{
 Serial.print("Status Code "); Serial.print(statusCode); Serial.println(" ThingSpeak Read Completed\n");
 }
   Serial.print("Object Temperature: "); Serial.print(tempC); Serial.println ("°C "); 
   Serial.println(""); 
display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(5, 0, "Object");
  display.drawString(5, 20, "Temperature");
  display.drawString(5, 40, String(tempC) + " °C");
  display.display();
  delay(DL);
}
