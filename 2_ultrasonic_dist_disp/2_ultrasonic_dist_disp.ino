#include <NewPing.h>

#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define TRIGGER_PINF  A2  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PINF     A3  // Arduino pin tied to echo pin on ping sensor.

#define TRIGGER_PINR  A4  // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PINR     A5  // Arduino pin tied to echo pin on ping sensor.
float rSensor, fSensor;

NewPing sonarRight(TRIGGER_PINR, ECHO_PINR, MAX_DISTANCE);
NewPing sonarFront(TRIGGER_PINF, ECHO_PINF, MAX_DISTANCE);

unsigned int pingSpeed = 30; // How frequently are we going to send out a ping (in milliseconds). 50ms would be 20 times a second.
unsigned long pingTimer;     // Holds the next ping time.
void setup() {

  Serial.begin(4800); // Open serial monitor at 115200 baud to see ping results.
}
void loop{
   ReadSensors();
 Serial.print(" Right : ");
  Serial.print(rSensor);
  Serial.print(" cm ");
  Serial.print(" Front : ");
  Serial.print(fSensor);
  Serial.println(" cm ");
}
void ReadSensors() {

  //leftSensor = sonarLeft.ping_median(TestNUM);     //accurate but slow
  //rightSensor = sonarRight.ping_median(TestNUM);     //accurate but slow
  //frontSensor = sonarFront.ping_median(TestNUM);     //accurate but slow

  //leftSensor = sonarLeft.convert_cm(leftSensor);
  //rightSensor = sonarRight.convert_cm(rightSensor);
  //frontSensor = sonarFront.convert_cm(frontSensor);

  lSensor = sonarLeft.ping_cm(); //ping in cm
  rSensor = sonarRight.ping_cm();
  fSensor = sonarFront.ping_cm();


  leftSensor = (lSensor + oldLeftSensor) / 2; //average distance between old & new readings to make the change smoother
  rightSensor = (rSensor + oldRightSensor) / 2;
  frontSensor = (fSensor + oldFrontSensor) / 2;


  oldLeftSensor = leftSensor; // save old readings for movment
  oldRightSensor = rightSensor;
  oldFrontSensor = frontSensor;

}

