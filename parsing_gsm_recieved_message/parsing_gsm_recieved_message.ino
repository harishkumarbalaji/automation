#include <SoftwareSerial.h>
SoftwareSerial gsm(D7, D8);

char RcvdMsg[200] = " ";
int RcvdCheck = 0;
int RcvdConf = 0;
int indexx = 0;
int RcvdEnd = 0;
char MsgMob[15];
char MsgTxt[50]=" ";
int MsgLength = 0;


char ip[20]="";
char port[6]="";

boolean flag=false;

void setup() {
   gsm.begin(115200);   // the GPRS baud rate  
   Serial.begin(115200);    // the GPRS baud rate
   delay(500);


  gsm.println("AT+CSQ");  //Signal Quality Report
  delay(2000);
 ShowSerialData();


 gsm.println("AT+CREG?");  //Attach or Detach  from Gprs Service
 delay(2000);
 ShowSerialData();




 gsm.println("AT+CMGF=1");  
 delay(2000);
 ShowSerialData();
 
    
 gsm.println("AT+CNMI=1,2,0,0,0");  
 delay(2000);
 ShowSerialData();




}

void loop() {
  
    if(gsm.available())
     {
      //Clear();

     if(RecSMS())
     {  
       Serial.println("Succes!!");
     }else
     {
     // Serial.println("Nothing!!");

     }
   }
if(Serial.available()){
  switch(Serial.read()){
    case 's':
      Serial.println("\nPinakas MsgTXt");
        for (int i=0;i<50;i++){
          Serial.print(MsgTxt[i]);
        }
     break;
     case 't':
       GetIp(MsgTxt);
       Serial.println("\nPinakas Ip");
       for(int j=0;j<20;j++){
         Serial.print(ip[j]);
       }
       break;
      case 'r':
         Serial.println("\nPinakas port");
       for(int k=0;k<20;k++){
         Serial.print(port[k]);
       }
     break;
      }  
    }
  }










void ShowSerialData()
{
  while(gsm.available()!=0)
   Serial.write(gsm.read());
}





boolean RecSMS() // Receiving the SMS and extracting the Sender Mobile number & Message Text
{
  boolean flag=false;
  if(gsm.available())
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
  }
Serial.println();
Serial.print("Message Text: ");
for(int x = 44;x <51;x++)
  {
  MsgTxt[x-44] = RcvdMsg[x];
  Serial.print(MsgTxt[x-44]);
  }
  
  Serial.println();
      }
    }
  }
  return flag;
}


void GetIp(char msg[]){
  //boolean flag=false;
  int len=strlen(msg);
  Serial.print(len);
  int k=0,j=0,l=0,i=0;
 for (i=0;i<len;i++){
  ip[i]=msg[i];
    if (msg[i]==':')
    {
      Serial.print("Arithmos i= ");
      Serial.print(i);
      ip[i]='\0';
      j=i;
      break;
     }
   }
   Serial.println("Variable j= ");
   Serial.println(j);
 for(k=0;k<len-j;k++){
  
   port[k]=msg[j++];
  
 }
 }




void Clear(){
  gsm.flush();
  char data='\0';
  char RcvdMsg[200] = " ";
  int RcvdCheck = 0;
  int RcvdConf = 0;
  int indexx = 0;
  int RcvdEnd = 0;
  char MsgMob[15]=" ";
  char MsgTxt[50]=" ";
  int MsgLength = 0;


}
