//Code for Receiver


#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal_I2C.h>
//String msg;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RH_ASK driver;
#define buzzer 2

#include <SoftwareSerial.h>
#include <ArduinoJson.h> 
SoftwareSerial s(5,6);

void setup()

{

    Serial.begin(9600);  // Debugging only
s.begin(9600);
delay(1000);
    pinMode(buzzer, OUTPUT);

    //lcd.begin(16, 2);
      lcd.init(); // initialize the lcd
      lcd.backlight();

      //lcd.setCursor(0, 0);         // move cursor to   (0, 0)
      //lcd.print("Arduino");        // print message at (0, 0)

    //lcd.clear(); 

    if (!driver.init())

         Serial.println("init failed");

}

void loop(){


    uint8_t buf[12];

    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking

    {

      int i;

      digitalWrite(buzzer, HIGH);

      delay(1000);

      digitalWrite(buzzer, LOW);

      // Message with a good checksum received, dump it.

      //lcd.setCursor(0,0);
      
      //lcd.print("LCD keluar la");

      //lcd.print((char*)buf); 
     

      Serial.print("Message: ");

      Serial.println((char*)buf);

      lcd.clear(); 

      lcd.setCursor(0,0);

      lcd.print("T1:");

      lcd.print((char*)buf);

      //lcd.print((char*)buf); 
       delay(1000);
      
    //}
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["datal"] = (char*)buf;
  //root["data2"] = "apple";
  
  if (s.available() >0){
  root.printTo(s);
} 
}
}
