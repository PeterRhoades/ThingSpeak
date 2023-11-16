#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

 String talk_back_api = "5LTRP0UY3PL9GQ7V";
 String talk_back_id = "42223";
 
 void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, INPUT_PULLUP);// open - HIGH, Close - LOW
  pinMode(D3, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  Serial.begin(115200);                                  //Serial connection
  wificonnect();
  }
 
void loop() {
      if(digitalRead(D1)==0)
    {
      Serial.println("FWD");
      POSTaddCommand("FWD");// adding commanding to TalkBack   
    }
    else if(digitalRead(D3)==0)
    {
      Serial.println("Back");
      POSTaddCommand("Back");  
    }
    else if(digitalRead(D5)==0)
    {
      Serial.println("Right");
      POSTaddCommand("Right");  
    }
    else if(digitalRead(D7)==0)
    {
      Serial.println("Left");
      POSTaddCommand("Left");  
    }

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

void POSTaddCommand (String command)
{
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
     HTTPClient http;    //Declare object of class HTTPClient
  //https://api.thingspeak.com/talkbacks/38050/commands
     String url =  "http://api.thingspeak.com/talkbacks/";
            url += talk_back_id;
            url += "/commands"; 
     http.begin(url);      //Specify request destination
     
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
     //String postMessage = "api_key=LK7OXGEIVFTPDIJT&command_string=rahul\r\n\r\n";
     String postMessage  = "api_key=";
            postMessage += talk_back_api;
            postMessage += "&command_string=";
            postMessage += command;
            postMessage += "\r\n\r\n";
     
     int httpCode = http.POST(postMessage);   //Send the request//"{\"api_key:\"\"0E1160BEX9CSNU6V\"}"
     String payload = http.getString();                  //Get the response payload
     //Serial.println(postMessage);
     Serial.println(httpCode);   //Print HTTP return code
     if(payload.length()>0)
     {
     Serial.println(payload);//Print request response payload
     }
     else
     {
     Serial.println("HTTP ERROR");
     }
     http.end();
     delay(1500);
     }
 
 else{
     Serial.println("Error in WiFi connection");   
 }  
}
