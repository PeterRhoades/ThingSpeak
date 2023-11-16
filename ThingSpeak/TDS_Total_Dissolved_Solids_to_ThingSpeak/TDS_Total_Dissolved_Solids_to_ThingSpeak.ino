/*Peter Rhoades©:
Friday 04/03/22:
Folder TDS_Total_Dissolved_Solids_to_ThingSpeak:
CQRobot Ocean: TDS (Total Dissolved Solids) Meter®
*/

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>  
#define TdsSensorPin A0
#define VREF 5.0   // analog reference voltage(Volt) of the ADC
#define SCOUNT  30 // sum of sample point
String api_key = "UO14CLDEEMJ50ISB"; //API Key:
int field_no1 = 1; //PPM:
int field_no2 = 2; //Vol:
ESP8266WiFiMulti WiFiMulti;
WiFiClient wifiClient;
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0, copyIndex = 0;
float averageVoltage = 0, tdsValue = 0, temperature = 25;

void setup()
{
  Serial.begin(9600);
  pinMode(TdsSensorPin, INPUT);
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
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    delay(2000);
 }

void loop()
 {
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U)  //every 40 milliseconds,read the analog value from the ADC
 {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT)
    analogBufferIndex = 0;
 }
  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 20000U)//Change to alter print timeing:800
 {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0); //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge = averageVoltage / compensationCoefficient; //temperature compensation
    tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; //convert voltage value to tds value
    Serial.println("20 Second TDS Scan interval");
    Serial.print("TDS----Value:");
    Serial.print(tdsValue, 0);
    Serial.print("ppm  ");
    Serial.print("voltage:");
    Serial.print(averageVoltage,2);
    Serial.println("V");
  HTTPClient http; //http is the object of class HTTPClient this class defines the method to create and send HTTP requests            
  String url =  "http://api.thingspeak.com/update?api_key=";
         url += api_key;
         url += "&field";
         url += field_no1;
         url += "=";
         url += tdsValue;// passing the parameter to string, this value will reach cloud at field1
         url += "&field";
         url += field_no2;
         url += "=";
         url += averageVoltage;
         Serial.println();
         http.begin(wifiClient,url);// initiate HTTP Request to establish connection  
  int httpCode = http.GET();// get method, returns a http code, -ve if access denied
  http.end();
 } 
}
int getMedianNum(int bArray[], int iFilterLen)
 {
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
