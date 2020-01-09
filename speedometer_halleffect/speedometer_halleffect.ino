#include <SoftwareSerial.h>
SoftwareSerial bt(9,10);
//calculations
//tire radius ~ 13.5 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25

#define reed A0//pin connected to read switch

//storage variables
int reedVal;
long timer;// time between one full rotation (in ms)
int mph;
float radius = 13.5 * 0.393701;// tire radius (in inches) "0.393701 is conversion of cms into inches"
float circumference;
int kph;
int r1=2;
int r2=3;
int r3=4;
int r4=5;
int recieved=0;
int rpm;

int maxReedCounter = 10;//min time (in ms) of one rotation (for debouncing)
int reedCounter;


void setup(void) {
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  pinMode(reed, INPUT);
  Serial.begin(9600);
  bt.begin(9600);
  // TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//allow interrupts
  //END TIMER SETUP
  
}


ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = (analogRead(reed)>200?0:1);//get val of A0
  if (reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      mph = (56.8*float(circumference))/float(timer);//calculate miles per hour
      rpm = (float(60000))/(float(timer));
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
      kph = mph * 1.609344;
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        //reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 1000){
    mph = 0;
  kph = 0;//if no new pulses from reed switch- tire is still, set mph, rpm and kph to 0
  rpm=0;
  }
  else{
    timer += 1;//increment timer
  } 
}
unsigned long previousMillis = 0; 
void loop(void) {
  if(bt.available())
  {
    recieved=bt.read();
    //delay(50);
    //Serial.println("");
  }
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 200) {
    
    previousMillis = currentMillis;
bt.println(kph);
   
    }
    Serial.println(recieved);
 switch(recieved)
 {
  case 11:
  digitalWrite(r1,HIGH);
  break;
  case 10:
  digitalWrite(r1,LOW);
  break;
  case 21:
  digitalWrite(r2,HIGH);
  break;
  case 20:
  digitalWrite(r2,LOW);
  break;
  case 31:
  digitalWrite(r3,HIGH);
  break;
  case 30:
  digitalWrite(r3,LOW);
  break;
  case 40:
  digitalWrite(r4,LOW);
  break;
  case 41:
  digitalWrite(r4,HIGH);
  break;
 }
 delay(50);
}
