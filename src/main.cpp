#include <Arduino.h>
#include <B6C_sim.h>
#include <uart_com.h>
#include <uart_test.h>
#include <e_uart_msg.h>


int DataInCom[msgtype::numberCom][msgtype::MaxLgthCom];
double cnt=0;
bool LcdPrint=false;
double timer=0;
double timerOld=0;
bool msgEnd=false;
int CommanderOutData0[6]={0x20,0x36,0x61,0x81,0x48,0x59};
int CommanderOutData1[6]={0x20,0x21,0x5A,0x62,0x37,0x49};
bool firstmsg;
int msgNumber;
int msgByte;
int msgBuffer;


void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate
  Serial1.begin(250000);
  // Display setup
    // set up the LCD's number of columns and rows:

  lcd.begin(16, 2);


}

void loop(){
  
  //Test fkt
  //uart_passthrough();
  if (Serial.available() > 0)
  {
    msgBuffer = Serial.read();
    firstmsg = true;
    DataInCom[msgtype::numberCom][msgtype::MaxLgthCom]=Serial.read();
    if (msgByte==0)
    {
      Serial.write(CommanderOutData0[msgByte]);  //Kopiert empfangene daten auf daten ausgang
    }
    else if (msgByte==1)
    {
      Serial.write(CommanderOutData1[msgByte]);
    }
    else
    {
      Serial.write(msgBuffer);
    }
    msgByte++;
    msgEnd = false;
    timerOld = timer;
  }
  else if (Serial.available() == 0)
  {
    timer = millis()-timerOld;;
  }

  if (timer >= 5)
  {
    msgEnd=true;
    LcdPrint=true;
  }
  
  if (timer >= 15)
  {
    //Broadcast signal
    Serial.write(0x55);
  }

  if (timer > 1000)
  {
    //timeout
    msgNumber=0;
    firstmsg = false;
  }

  if (msgEnd)
  {
    msgByte=0;
    if (msgNumber < 5)
    {
      msgNumber++;
    }
    else
    {
      msgNumber=4;

    }
  }


   //uart_test();





  /*
  int BitNumb;
  int MsgNumb;
  bool ComAktiv;
  int ComStep;
  int ComStatus;
  int TimeOutCnt;
  int MaxTimeOut= 50000000;


  //set Var for startup
int DataInStart[msgtype::numberStart][msgtype::MaxLgthStrt] ={
    //msg 1
    //{85 ,32 ,240,},
    {0x55,0x20,0xf0},
    //msg 2
    //{85, 54, 15, 39, 0, 0,232, 3, 208, 7, 184, 11, 184, 11, 158, 0, 232, 3, 0, 0, 5, 208, 7, 0},
    {0x55, 0x36, 0x0F, 0x27, 0x00, 0x00, 0xE8, 0x03, 0xD0, 0x07, 0xB8, 0x0B, 0xB8, 0x0B, 0x9E, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x05, 0xD0, 0x07, 0x00},
    //msg 3
    //{85, 97, 76, 65, 66, 69, 76, 48, 208, 7,},
    {0x55, 0x61, 0x4C, 0x41, 0x42, 0x45, 0x4C, 0x30, 0xD0, 0x07},
    //msg 4
    //{85, 129, 208, 7, 0, 0, 200, 0, 0, 0, 1, 54, 16, 1, 192, 100, 0, 0, 0, 30, 30, 16, 39, 0, 0, 0, 200, 0, 48, 117, 4, 0, 0, 0}
    {0x55,0x81,0xD0,0x07,0x00,0x00,0xC8,0x00,0x00,0x00,0x01,0x36,0x10,0x01,0xC0,0x64,0x00,0x00,0x00,0x1E,0x1E,0x10,0x27,0x00,0x00,0x00,0xC8,0x00,0x30,0x75,0x04,0x00,0x00,0x00},
  };
int DataOutStart[msgtype::numberStart][msgtype::MaxLgthStrt];
//set Var for Communication
int DataInCom[][msgtype::MaxLgthCom]={
    //Com msg 1
    //{85, 72, 25, 4, 23, 4, 239, 55, 239, 55,   4,  42,   69,  0,  0, 2, 0, 0, 0, 0},
    //                                                    ____ <- winkel              
    {0x55,0x48,0x19,0x04,0x17,0x04,0xEF,0x37,0xEF,0x37,0x04,0x31,0x40,0x00,0x00,0x02,0x00,0x00,0x00,0x00},
    //Com msg 2
    //{85, 89, 33, 2,  0, 0,  83, 49,   0, 68, 224, 167, 255, 68, 76, 0, 0, 0, 0}
    {0x55,0x59,0x21,0x02,0x00,0x00,0x53,0x31,0x00,0x44,0xE0,0xA7,0xFF,0x44,0x4C,0x00,0x00,0x00,0x00}
  };
int DataOutCom[msgtype::numberCom][msgtype::MaxLgthCom];

/*
Startup_com(ComAktiv);
ComAktiv = uart_timeout(TimeOutCnt, MaxTimeOut);

if (ComAktiv && (Serial.available()>0))
{
  Serial.write(0x55);
}
else if (!ComAktiv)
{
  Serial.write(0xaa);
}
*/

/*

if (ComStep == 0)
{
// Wert des zündwinkels ausgeben bit 13
VarBuffer=DataInCom[0][12];
lcd.setCursor(0, 0);
lcd.print("ZW:");
lcd.print(VarBuffer);

// Wert der Frequenz ausgeben bit 13
VarBuffer=DataInCom[0][11];
lcd.setCursor(6, 0);
lcd.print("Freq:");
lcd.print(VarBuffer);

// Debug Print
// Wert der Frequenz ausgeben bit 13
VarBuffer=ComStep;
lcd.setCursor(0, 1);
lcd.print("setp:");
lcd.print(VarBuffer);

// Wert der Frequenz ausgeben bit 13
VarBuffer=ComStatus;
lcd.setCursor(9, 1);
lcd.print("Stat:");
lcd.print(VarBuffer);
}
//test serial write


// Com Start
  switch (ComStep)
  {
  case 0:

    //if ((combyte::Startbyte == Serial.read()) && !ComAktiv)
    if (true)
    {
				ComAktiv = true;
    }

    if (ComAktiv)
    {
      ComStep = 1;

    };
    Serial.print(0x01);
    break;
  case 1:
    ComStatus = Uart_Start_Com(ComAktiv, BitNumb, MsgNumb, DataInStart[msgtype::numberStart][msgtype::MaxLgthStrt], DataOutStart[msgtype::numberStart][msgtype::MaxLgthStrt]);

    if (ComStatus == 1)
    {
      ComStep= 99;
    };
    Serial.print(0x02);
    break;
  default:
    
    ComStatus = Uart_Data_Com(ComAktiv, BitNumb, MsgNumb, DataInCom[msgtype::numberCom][msgtype::MaxLgthCom], DataOutCom[msgtype::numberCom][msgtype::MaxLgthCom]);
    Serial.print(0x03);
    break;
  }
 */

 //
 // ComAktiv = uart_timeout(TimeOutCnt, MaxTimeOut);
 //
 // if (!ComAktiv)
 // {
 //   ComStep = 0;
 // }
 //
}