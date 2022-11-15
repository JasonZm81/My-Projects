#include <LiquidCrystal.h>
#include <Servo.h>
Servo brake_servo;

const int LDR = A1;     
int LDRValue =0;      
int light_sensitivity = 750; 
int spotlight = A2;
int echo=9;
int trig=10;
int servo =20;
int sig=11;
int buzzer =13;
int LED1 =A5;
int LED2 =A4 ;
int LED3 =A3 ;
long drt,dis;
int pos = 0;

const int rs= 0, en=1, d4 = 8, d5 = 7, d6 = 6, d7 =5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  brake_servo.attach(sig);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(servo, INPUT);
  pinMode(sig, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(LED1, OUTPUT);  
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LDR, INPUT);
  pinMode(spotlight, OUTPUT); 
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {

  LDRValue = analogRead(LDR);       
       //Serial.println(LDRValue);
       //spotlight_brightness();      
       //delay(50);        
    
       if (LDRValue < light_sensitivity) 
         {
           digitalWrite(spotlight, HIGH);
           spotlight_on ();
           delay(100); 
         }
       else
         {
           digitalWrite(spotlight, LOW);
         }
  
  measure_distance();
  show_distance();
}

void measure_distance() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  drt = pulseIn(echo,HIGH);
  dis = drt*0.034*0.5;
  if(dis <=150){
    digitalWrite(buzzer, HIGH); 
    delay (50); 
    digitalWrite(buzzer, LOW);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
          for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
            brake_servo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(2.5);                       // waits 15 ms for the servo to reach the position
          }
          for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            brake_servo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(2.5);                       // waits 15 ms for the servo to reach the position
          }
    }

   else if((dis >150)&&(dis <=250)){
    digitalWrite(buzzer, LOW); 
    digitalWrite(LED2, HIGH); 
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);   
          for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees in steps of 1 degree
            brake_servo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15 ms for the servo to reach the position
          }
          for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            brake_servo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);                       // waits 15 ms for the servo to reach the position
          }                
  }

   else{
    digitalWrite(buzzer, LOW); 
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
}
};

void show_distance() {
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Distance: ");
//lcd.setCursor(0,1);
lcd.print(dis);
lcd.print("cm");
delay (500);
}

void spotlight_on() {
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Spotlight is on");
lcd.setCursor(0,1);
lcd.print("Brightness: ");
lcd.print(LDRValue);
delay (500);
}

void spotlight_brightness(){
lcd.setCursor(0,1);
lcd.print("Brightness: ");
lcd.print(LDRValue);
delay (500);
}
