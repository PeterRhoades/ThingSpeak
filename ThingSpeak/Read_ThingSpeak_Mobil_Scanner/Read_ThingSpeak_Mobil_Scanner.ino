/*
Peter Rhoades:
Wednesday 02/03/22
Folder Read_ThingSpeak_Mobil_Scanner:
Read Data from ThingSpeak Mobil Scanner Channel®:
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  
String readAPIkey = "S3XJS9HNWE8F23DS";// Read API Key & Channel ID ThingSpeak channel Mobile Scanner: 
String channel_ID = "1396346";
String readAPIkey1 = "PJPXZGAIKRFQUC8R";// Read API Key & Channel ID ThingSpeak channel Summer House BME280:
String channel_ID1 = "1341661";
String readAPIkey2 = "LWSBBSH5PREAX7YJ";// Read API Key & Channel ID ThingSpeak channel Summer House DHT22: 
String channel_ID2 = "1654219";
String readAPIkey3 = "DWYC3QRVYKT9WF4L";// Read API Key & Channel ID ThingSpeak channel 5 Sensor: 
String channel_ID3 = "1659042";
String readAPIkey4 = "NO4MA0BRD4X3H29U";// Read API Key & Channel ID ThingSpeak channel TDS (Total Dissolved Solids) Meter: 
String channel_ID4 = "1663832";
String field_N1 = "1";
String result_N = "1";
String field_N2 = "2";
String field_N3 = "3"; //ThingSpeak Fields:
String field_N4 = "4";
String field_N5 = "5";
String field_N6 = "6";
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;
int DL = 2000;
int count = 1;

void setup() {
    Serial.begin(9600);
    Serial.flush();
    wificonnect();         
}

void loop() 
{
 GETreceive();
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
  Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    delay(2000);
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
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("1 Mobile Scanner BME280 Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);  
 }
 {
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
 
      if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("2 Mobile Scanner BME280 Humidity:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);
}
{
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
 
      if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("3 Mobile Scanner BME280 Pressure:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL); 
 }
 {
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
 
      if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("4 Mobile Scanner HTU21 Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL); 
}
{
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
 
      if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();//.toFloat
                Serial.println ("5 Mobile Scanner HTU21 Humidity:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL); 
 }
 {
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
 
      if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+33);
                float field_data = field_data_string.toFloat();
                Serial.println ("6 Mobile Scanner BH1750 light:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL); 
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID1; // 
               url += "/fields/";
               url += field_N1;
               url += ".json?api_key=";
               url += readAPIkey1;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("7 Summer House BME280 Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID1; // 
               url += "/fields/";
               url += field_N2;
               url += ".json?api_key=";
               url += readAPIkey1;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("8 Summer House BME280 Humidity:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID1; // 
               url += "/fields/";
               url += field_N3;
               url += ".json?api_key=";
               url += readAPIkey1;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+29,begin_b+34);
                float field_data = field_data_string.toFloat();
                Serial.println ("9 Summer House Pressure BME280 Pressure:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID2; // 
               url += "/fields/";
               url += field_N1;
               url += ".json?api_key=";
               url += readAPIkey2;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+28,begin_b+33);
                float field_data = field_data_string.toFloat();
                Serial.println ("10 Summer House DHT22 Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID2; // 
               url += "/fields/";
               url += field_N2;
               url += ".json?api_key=";
               url += readAPIkey2;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+28,begin_b+33);
                float field_data = field_data_string.toFloat();
                Serial.println ("11 Summer House DHT22 Humidity:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
  HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID3; // 
               url += "/fields/";
               url += field_N1;
               url += ".json?api_key=";
               url += readAPIkey3;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+27,begin_b+32);
                float field_data = field_data_string.toFloat();
                Serial.println ("12 Five Sensor MLX90614 Ambient Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID3; // 
               url += "/fields/";
               url += field_N2;
               url += ".json?api_key=";
               url += readAPIkey3;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+27,begin_b+32);
                float field_data = field_data_string.toFloat();
                Serial.println ("13 Five Sensor MLX90614 Object Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID3; // 
               url += "/fields/";
               url += field_N3;
               url += ".json?api_key=";
               url += readAPIkey3;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+27,begin_b+32);
                float field_data = field_data_string.toFloat();
                Serial.println ("14 Five Sensor HDC1080 Temperature:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID3; // 
               url += "/fields/";
               url += field_N4;
               url += ".json?api_key=";
               url += readAPIkey3;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+27,begin_b+32);
                float field_data = field_data_string.toFloat();
                Serial.println ("15 Five Sensor HDC1080 Humidity:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 {
 HTTPClient http;    
        String url =  "http://api.thingspeak.com/channels/";
               url += channel_ID4; // 
               url += "/fields/";
               url += field_N1;
               url += ".json?api_key=";
               url += readAPIkey4;
               url += "&results=";
               url += result_N;
               http.begin(wifiClient,url); //HTTP
        int httpCode = http.GET();
        
        if(httpCode == 200) 
        {
                
                Serial.println("..........................................................................");
                Serial.println();
                Serial.print("Count = ");
                Serial.println(count);
                count++;
                Serial.println();
                Serial.print("Return Code = ");
                Serial.print(httpCode);
                Serial.print(" Channel Data Successfully Read\n");    
                  String payload = http.getString();
                  Serial.println();
                int begin_b = payload.indexOf("\"entry_id");
                String field_data_string = payload.substring(begin_b+28,begin_b+33);
                float field_data = field_data_string.toFloat();
                Serial.println ("16 Dissolved Solids PPM:");
                Serial.println(field_data_string);
                Serial.println(field_data);
                Serial.println ();
                http.end();
          delay(DL);        
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
