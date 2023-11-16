#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

 String talk_back_api = "5LTRP0UY3PL9GQ7V";
 String talk_back_id = "42223";//42223
 String command_id = "22597691";//22569895
 
 void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, INPUT_PULLUP);// press = 0, open -1 
  pinMode(D3, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
  Serial.begin(115200);                                  //Serial connection
  wificonnect();
  }
 
void loop() {
       if(digitalRead(D1)==0)
    {
      Serial.println("D1");
      PUTupdateCommand("D1");// adding commanding to TalkBack   
    }
    else if(digitalRead(D3)==0)
    {
      Serial.println("D3");
      PUTupdateCommand("D3");  
    }
    else if(digitalRead(D5)==0)
    {
      Serial.println("D5");
      PUTupdateCommand("D5");  
    }
    else if(digitalRead(D7)==0)
    {
      Serial.println("D7");
      PUTupdateCommand("D7");  
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

void PUTupdateCommand (String command)
{
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
     HTTPClient http;    //Declare object of class HTTPClient
     https://api.thingspeak.com/talkbacks/12345/commands/23456.json
     String url =  "http://api.thingspeak.com/talkbacks/";
            url += talk_back_id;
            url += "/commands/";
            url += command_id;
            url += ".json"; 
     Serial.println(url);
     http.begin(url);      //Specify request destination
     
     http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
     //String postMessage = "api_key=LK7OXGEIVFTPDIJT&command_string=rahul\r\n\r\n";
     String putMessage  = "api_key=";
            putMessage += talk_back_api;
            putMessage += "&command_string=";
            putMessage += command;
            putMessage += "\r\n\r\n";
     
     int httpCode = http.PUT(putMessage);   //Send the request//"{\"api_key:\"\"0E1160BEX9CSNU6V\"}"
     String payload = http.getString();                  //Get the response payload
   
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
