#include <SoftwareSerial.h>
SoftwareSerial mcu(9,10);
int s1 = A0;
int s2 = A1;
int s3 = A2;
int s4 = A3;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;// variable to store the value coming from the sensor
int one,two,three,four;
int flex;

void setup() {
    Serial.begin(9600);
    mcu.begin(4800);
}

void loop() {
  // read the value from the sensor:
  sensorValue1 = analogRead(s1);
  sensorValue2 = analogRead(s2);
  sensorValue3 = analogRead(s3);
  sensorValue4 = analogRead(s4);
  one=map(sensorValue1,770,900,0,100);
 two=map(sensorValue2,810,935,0,100);
 three=map(sensorValue3,800,900,0,100);
 four=map(sensorValue4,810,900,0,100);
  Serial.print(" first: ");
  Serial.print(one);
  Serial.print(" second : ");
  Serial.print(sensorValue2);
  Serial.print("third : ");
  Serial.print(sensorValue3);
  Serial.print("fourth: ");
  Serial.println(four);
  
  if(one<50 && two>50 && three>50 && four >50)
  {
    flex=1;
  }
  else if(one>50 && two<50 && three>50 && four >50)
 {
  flex=2;
 }
 else if(one>50 && two>50 && three<50 && four >50)
 {
  flex=3;
 }
 else if(one>50 && two>50 && three>50 && four <50)
 {
  flex=4;
 }
 else if(one>50 && two<50 && three<50 && four <50)
 {
  flex=5;
 }
 else if(one>50 && two<50 && three<50 && four >50)
 {
  flex=6;
 }
 else
 {
  flex=0;
 }
 
  Serial.println(flex);
  mcu.println(flex);
  
  delay(1000);
}
