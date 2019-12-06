#include <SoftwareSerial.h>
#include <Servo.h>
Servo servoPan;
Servo servoTilt;
char tiltChannel=0, panChannel=1;
//Servo servoTilt, servoPan;
char serialChar=0;
int x=0,y=0;
SoftwareSerial bt(9,10);
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
int firstVal=0, secondVal=0,thirdVal=0;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(57600);
  bt.begin(9600);
  servoPan.attach(6);
servoTilt.attach(5);
servoPan.write(90);
servoTilt.write(90);
}

// the loop routine runs over and over again forever:
void loop() {
 /* String num;
  // read the input on analog pin 0:
  //int sensorValue = analogRead(A0);
  if(bt.available()>0)
  {
     
  Serial.write(bt.read());
  //Serial.println("");
  }
  // print out the value you read:
  //Serial.println(sensorValue);
  */
  if (bt.available() > 0 )
  {
    rdata = bt.read();
    myString = myString+ rdata;
   
   // Serial.print(rdata);
    if( rdata == ':')
    {
   //  Serial.println(myString);
  // Serial.println("fahad");
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2);


firstVal = l.toInt();
secondVal = m.toInt();
thirdVal = n.toInt();
myString = "";
// end new code
    }
  }
 Serial.print(firstVal);
  Serial.print("\t");
Serial.print(secondVal);
 Serial.print("\t");
 Serial.println(thirdVal);
// if(bt.available()>0 )
 //{
   x=map(firstVal,105,-80,0,180);
  servoPan.write(x);
  y=map(secondVal,-62,90,0,180);
  servoTilt.write(y);
// }
/* else
 {
  while(Serial.available() <=0);  //Wait for a character on the serial port.
  serialChar = Serial.read();     //Copy the character from the serial port to the variable
  if(serialChar == tiltChannel){  //Check to see if the character is the servo ID for the tilt servo
    while(Serial.available() <=0);  //Wait for the second command byte from the serial port.
    servoTilt.write(Serial.read());  //Set the tilt servo position to the value of the second command byte received on the serial port
  }
  else if(serialChar == panChannel){ //Check to see if the initial serial character was the servo ID for the pan servo.
    while(Serial.available() <= 0);  //Wait for the second command byte from the serial port.
    servoPan.write(Serial.read());   //Set the pan servo position to the value of the second command byte received from the serial port.
  }

  
 }*/
 delay(10);        // delay in between reads for stability
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

