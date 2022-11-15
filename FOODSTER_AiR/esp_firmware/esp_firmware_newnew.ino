#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D6, D5);
#include <ArduinoJson.h>

char *ssid = "j";
char *password = "j12345678";

char server[] = "https://apiv2.favoriot.com";
const String APIKEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Ikdyb3VwMTUiLCJyZWFkX3dyaXRlIjp0cnVlLCJpYXQiOjE2MzY3Nzk5NTB9.GL_hMQfBldMoeIh6XYPJBXsVhko4yjlvjKl63v0I6Ok";
const String DEVICE = "nodemcu@Group15";

String message ;
bool messageReady;

WiFiClient client;

void setup()
{
  WiFi.begin(ssid, password);
  Serial.begin(9600);
s.begin(9600);
while (!Serial) continue;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  //Serial.print("IP Address: ");
  //Serial.println(WiFi.localIP());

  //Serial.println(WiFi.status());
  Serial.println("Wifi Connected!");
  //Serial.println("");
}

void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
    
  //Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  //Serial.print("Data 1 ");
  //Serial.println("");
  String datal=root["datal"];
  Serial.println("");
  //Serial.print (datal);
  /*Serial.print(" Data 2 ");
  int data2=root["data2"];
  Serial.print (data2);
  Serial.println("");
  Serial.println("---------------------XXXXX-----------");*/
  
  //sendStream();

  messageReady = true;

  if (messageReady)
  {
    // Serial.println(message);
    messageReady = false;

    String txt = "ON HIGH"; // Text to send

    // If there's a successful connection
    if (client.connect(server, 80))
    {
      //Serial.println(F("connected"));
      //Serial.println("");
      Serial.print (datal);
      Serial.println("");
      // Build the data field
      String json = "{\"device_developer_id\":\"nodemcu@Group15\",\"data\":{\"Task\":\"" + datal + "\"}}";
      int thisLength = json.length();

      //Serial.println("STATUS : Sending data..."); // Display sending status
      client.println("POST /v2/streams HTTP/1.1");
      client.println("Host: apiv2.favoriot.com");
      client.print(String("apikey: "));
      client.println(APIKEY);
      client.println("Content-Type: application/json");
      client.println("cache-control: no-cache");
      client.print("Content-Length: ");
      client.println(thisLength);
      client.println("Connection: close");

      client.println();
      client.println(json);

      Serial.println(json);                  // display sent data
      //Serial.println("STATUS : Data sent!"); // display sent status
      Serial.print (datal);
    }
    else
    {
      // If you didn't get a connection to the server:
      Serial.println(F("connection failed"));
    }
  }
  delay(1000);
}




/*/ Send stream to FAVORIOT
void sendStream()
{

    messageReady = true;

  if (messageReady)
  {
    // Serial.println(message);
    messageReady = false;

    String txt = "ON HIGH"; // Text to send

    // If there's a successful connection
    if (client.connect(server, 80))
    {
      Serial.println(F("connected"));
      Serial.println("");
      // Build the data field
      String json = "{\"device_developer_id\":\"nodemcu@Group15\",\"data\":{\"Task\":\"" + message + "\"}}";
      int thisLength = json.length();

      Serial.println("STATUS : Sending data..."); // Display sending status
      client.println("POST /v2/streams HTTP/1.1");
      client.println("Host: apiv2.favoriot.com");
      client.print(String("apikey: "));
      client.println(APIKEY);
      client.println("Content-Type: application/json");
      client.println("cache-control: no-cache");
      client.print("Content-Length: ");
      client.println(thisLength);
      client.println("Connection: close");

      client.println();
      client.println(json);

      Serial.println(json);                  // display sent data
      Serial.println("STATUS : Data sent!"); // display sent status
    }
    else
    {
      // If you didn't get a connection to the server:
      Serial.println(F("connection failed"));
    }
  }
}*/
