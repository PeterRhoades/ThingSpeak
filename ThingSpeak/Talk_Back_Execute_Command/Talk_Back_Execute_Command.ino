#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

String talkback_api = "5LTRP0UY3PL9GQ7V";
String talkback_id = "42223";
String payload=""; 
 
void setup() {
 
  Serial.begin(115200);                                  //Serial connection
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D1, HIGH);//HIGH -OFF and to TURN On - LOW
  digitalWrite(D3, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D7, HIGH);
  wificonnect();
 
}


void loop() {
  executeCommand();
  if(payload == "D1")
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH); 
    digitalWrite(D1, LOW); // D1 - ON
   }
   else if(payload == "D3")
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH); 
    digitalWrite(D3, LOW);// ON 
   }
   else if(payload == "D5")
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH); 
    digitalWrite(D5, LOW); 
    }   

   else if(payload == "D7")
    {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH); 
    digitalWrite(D7, LOW); 
    }
   else if(payload == "ALLON")
    {
    digitalWrite(D1, LOW);//on
    digitalWrite(D3, LOW);
    digitalWrite(D5, LOW);
    digitalWrite(D7, LOW); 
   }
   else if(payload == "ALLOFF")
  {
    digitalWrite(D1, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D7, HIGH); 
   }
  delay(5000);
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
void executeCommand()
{
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient

   //http://api.thingspeak.com/talkbacks/38001/commands/execute 
   String url  = "http://api.thingspeak.com/talkbacks/";
          url += talkback_id;
          url += "/commands/execute";
          
   http.begin(url);      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
   String postMessage =  String("api_key=") + String(talkback_api);  
   int httpCode = http.POST(postMessage);   //Send the request//"{\"api_key:\"\"0E1160BEX9CSNU6V\"}"
   payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   if(payload.length()>0)
   {
   Serial.println(payload);//Print request response payload
   }
   http.end();
  }
 
 else{
     Serial.println("Error in WiFi connection");   
 }
} 
