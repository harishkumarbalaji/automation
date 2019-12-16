#include <SoftwareSerial.h>
#include<string.h>
SoftwareSerial gsm(D7,D8);
boolean SERIAL_DEBUG_GSM = true;
char text[300];                   //TEXT CHAR HOLDS THE TEXT TO SENT TO GSM MODULE      
String textsms;
int flag1=0,flag2=0,gsm_flag=0;
int bill=125;
int gsmflag=0;

void gsm_send_sms_contact1(); 
void ShowSerialData();
void gsm_send_sms(char *st);
void gsm_setup();
void check_sms();
void recsms();
volatile char RcvdMsg[200] = " ";
int RcvdCheck = 0;
int RcvdConf = 0;
int indexx = 0;
int RcvdEnd = 0;
volatile char MsgMob[15] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','"'};
volatile char MsgTxt[50]=" ";
int MsgLength = 48;
boolean flag=false;
char numt[64];
String num,num_t,st1,numta;
void setup() {
  // put your setup code here, to run once:
gsm.begin(115200);
Serial.begin(115200);
gsm_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
  check_sms();
//Serial.println("waiting");
//delay(5000);
//Serial.println("sending SMS");
//gsm_send_sms_contact1();
//delay(50);

}
void ShowSerialData()// this function is used to view in serial monitor
{
  if(SERIAL_DEBUG_GSM)
  {
  while(gsm.available()!=0)
   Serial.write(gsm.read());
  }
}
void gsm_send_sms_contact1()  //a variable named a will hold the text message to be sent
{ 
  if(gsmflag==0)
{
  gsmflag=1;
  //gps();
  textsms = ((String)"!!ALERT!!The bill amount has reached more than 80%. Current Bill amount is "+bill+" Rupees");
  strcpy(text,textsms.c_str());//the text sms is the copied to the text variable which is a char variable
  gsm.write(0x1a);
  gsm.println("AT");
  ShowSerialData();
  gsm.println("ATZ");                       //software reset for sim900a module which resets to user defined profiles
  ShowSerialData();
  delay(500);                              //optimum delay for the sim900a to respond
  gsm.println("AT+CMGF=1");                 //sets the sim900a module to message sending mode
  delay(500);
  ShowSerialData();
  gsm.println("AT+CMGS=\"+919677219665\"");     //"AT+CMGS=\"+91<india country code><10 digit cellphone number>\""
  
  delay(500);
  gsm.println(text);                           //the text should sent from gsm module to cellphone   
  //gsm.print("speed: ");
  //gsm.println(speedOTG);
  gsm.write(0x1a);                            //0x1a is the ascii code for ctrl+z which indicates the gsm module the message has been completed
  ShowSerialData();
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CNMI=1,2,0,0,0");  
  delay(2000);
  ShowSerialData();
}
}
void gsm_setup()
{
    
    gsm.println("AT+CSQ");  //Signal Quality Report
    delay(2000);
    ShowSerialData();
    gsm.println("AT+CMGF=1");  
    delay(2000);
    ShowSerialData();
    gsm.println("AT+CNMI=1,2,0,0,0");  
    delay(2000);
    ShowSerialData();
   // gsm.println("AT+CGNSPWR=1");
    //delay(2000);
    ShowSerialData();
    gsm_flag = 1;

}

void check_sms()
{
  if(gsm.available())  //checks for message from gsm module
  {
    recsms();
  }
  if((flag1 == 1)&&(flag2 ==1))
  { 
    flag1 =0;flag2=0;
    String stb = ((String)MsgTxt[0]+MsgTxt[1]+MsgTxt[2]+MsgTxt[3]+MsgTxt[4]+MsgTxt[5]+MsgTxt[6]+MsgTxt[7]);
    //Serial.println(stb);
    if(stb == "bill123")         //checks for the loc keyword in msg to respond
    {
      gsm_send_sms(numt);
    }
      for(int y=0;y<=12;y++)MsgMob[y]= '\o';     //following lines are used to rest the variables for next use
      for(int f=0;f<=50;f++)MsgTxt[f]= '\o ';
      for(int f=0;f<=200;f++)RcvdMsg[f]= '\o ';
       RcvdCheck = 0;
       RcvdConf = 0;
       indexx = 0;
       RcvdEnd = 0;
       
  }
}
void recsms() // Receiving the SMS and extracting the Sender Mobile number & Message Text
{

  if(gsm.available() && gsm_flag == 1)
   {
    char data = gsm.read();
    if(data == '+'){RcvdCheck = 1;}
    if((data == 'C') && (RcvdCheck == 1)){RcvdCheck = 2;}
    if((data == 'M') && (RcvdCheck == 2)){RcvdCheck = 3;}
    if((data == 'T') && (RcvdCheck == 3)){RcvdCheck = 4;}
    if(RcvdCheck == 4){indexx = 0; RcvdConf = 1; RcvdCheck = 0;flag=true;}
  if(RcvdConf == 1)
     {
  if(data == '\n'){RcvdEnd++;}
  if(RcvdEnd == 3){RcvdEnd = 0;}
  RcvdMsg[indexx] = data;

  indexx++;
  if(RcvdEnd == 2){RcvdConf = 0;MsgLength = indexx-2;}
    if(RcvdConf == 0)
    {
  Serial.print("Mobile Number is: ");
    for(int x = 4;x <17;x++)
  {
    MsgMob[x-4] = RcvdMsg[x];
    Serial.print(MsgMob[x-4]);
  }flag1=1;
  if(flag1 == 1){
  num = ((String)"AT+CMGS=\""+MsgMob[0]+MsgMob[1]+MsgMob[2]+MsgMob[3]+MsgMob[4]+MsgMob[5]+MsgMob[6]+MsgMob[7]+MsgMob[8]+MsgMob[9]+MsgMob[10]+MsgMob[11]+MsgMob[12]+MsgMob[13]+ MsgMob[14]+"\"");     
  strcpy(numt,num.c_str());
  //Serial.println(numt);
  flag2 = 1;
  }

  Serial.print("Message Text: ");
  if(flag2 == 1){
  for(int x = 44;x<51;x++)//the message is present in the character between 46 to 48
    {
    MsgTxt[x-44] = RcvdMsg[x];
    Serial.print(MsgTxt[x-44]);
    }
    }
  }
  }
  }
}
void gsm_send_sms(char *st)  //a variable named a will hold the text message to be sent
{
  textsms = ((String)"Your current bill amount is "+bill+" Rupees");
  strcpy(text,textsms.c_str());//the text sms is the copied to the text variable which is a char variable
  //gps();
  gsm.write(0x1a);          
  gsm.println("AT");
  delay(500);
  ShowSerialData();
  gsm.println("ATZ");
  delay(500);
  ShowSerialData();
  gsm.println("AT+CMGF=1");                 //sets the sim900a module to message sending mode
  delay(500);
  ShowSerialData();
  Serial.println(st);
  gsm.println(st);       
  
  delay(250);
  Serial.println(text);
  gsm.println(text); 
  //gsm.print("speed: ");
  //gsm.println(speedOTG);
                            //the text should sent from gsm module to cellphone   
  gsm.write(0x1a);//0x1a is the ascii code for ctrl+z which indicates the gsm module the message has been completed
  ShowSerialData();
  gsm.println("AT+CMGF=1");  
  delay(2000);
  ShowSerialData();
  gsm.println("AT+CNMI=1,2,0,0,0");  
  delay(2000);
  ShowSerialData();
  
}
