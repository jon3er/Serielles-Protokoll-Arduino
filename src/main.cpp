#include <Arduino.h>
#include <B6C_sim.h>
#include <uart_com.h>
#include <uart_test.h>
#include <e_uart_msg.h>

void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate
  Serial1.begin(250000);
  // Display setup

}


void loop(){
  
  //Test fkt
  //uart_passthrough();
   //uart_test();

  int BitNumb;
  int MsgNumb;
  bool ComAktiv = false;
  int ComStep;
  int ComStatus;
  int TimeOutCnt;
  int MaxTimeOut= 5000;

    //set Var for startup
  int DataInStart[msgtype::numberStart][msgtype::MaxLgthStrt] ={
    [msgtype::StartMsg1]=85 ,32 ,240,
    [msgtype::StartMsg2]=85, 54, 15, 39, 0, 0,232, 3, 208, 7, 184, 11, 184, 11, 158, 0, 232, 3, 0, 0, 5, 208, 7, 0,
    [msgtype::StartMsg3]=85, 97, 76, 65, 66, 69, 76, 48, 208, 7,
    [msgtype::StartMsg4]=85, 129, 208, 7, 0, 0, 200, 0, 0, 0, 1, 54, 16, 1, 192, 100, 0, 0, 0, 30, 30, 16, 39, 0, 0, 0, 200, 0, 48, 117, 4, 0, 0, 0,
  };

  int DataOutStart[msgtype::numberStart][msgtype::MaxLgthStrt];

  //set Var for Communication
  int DataInCom[msgtype::numberCom][msgtype::MaxLgthCom]={
    [msgtype::ComMsg1]=85, 72, 25, 4, 23, 4, 239, 55, 239, 55,   4,  49,   0,  0,  0, 2, 0, 0, 0, 0,
    [msgtype::ComMsg2]=85, 89, 33, 2,  0, 0,  83, 49,   0, 68, 224, 167, 255, 68, 76, 0, 0, 0, 0,
  };

  int DataOutCom[msgtype::numberCom][msgtype::MaxLgthCom];


  switch (ComStep)
  {
  case 0:
    
    Startup_com(ComAktiv);

    if (ComAktiv)
    {
      ComStep++;
    };

    break;
  case 1:
    ComStatus = Uart_Start_Com(ComAktiv, BitNumb, MsgNumb, DataInStart[msgtype::numberStart][msgtype::MaxLgthStrt], DataOutStart[msgtype::numberStart][msgtype::MaxLgthStrt]);

    if (ComStatus)
    {
      ComStep++;
    };

  default:
    
    Uart_Data_Com(ComAktiv, BitNumb, MsgNumb, DataInCom[msgtype::numberCom][msgtype::MaxLgthCom], DataOutCom[msgtype::numberCom][msgtype::MaxLgthCom]);

    break;
  }
  
 
  //ComAktiv = uart_timeout(TimeOutCnt, MaxTimeOut);
 
  if (!ComAktiv)
  {
    ComStep = 0;
  }
  
}