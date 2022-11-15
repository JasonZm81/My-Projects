#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);
#include <ArduinoJson.h>


void setup()
{
s.begin(9600);
}

void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
    
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.print("Data 1 ");
  Serial.println("");
  int datal=root["datal"];
  Serial.print (datal);
  Serial.print(" Data 2 ");
  int data2=root["data2"];
  Serial.print (data2);
  Serial.println("");
  Serial.println("---------------------XXXXX-----------");
  
}
