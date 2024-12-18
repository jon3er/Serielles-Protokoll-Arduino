#include <Arduino.h>
#include <B6C_sim.h>
#include <uart_com.h>
#include <uart_test.h>
#include <e_uart_msg.h>
#include <LCD_display.h>

#include <LiquidCrystal.h>
#include <string.h>
// initialize the library by associating any needed LCD interface pin


// Consitendte werte müssen auserhalb der loop gespeichert werden
int BitNumb=0;
int MsgNumb=0;
bool ComAktiv=false;
bool LcdPrint=false;
int ComStep=0;
int ComStatus=0;
int TimeOutCnt=0;
int MaxTimeOut=5000;
int VarBuffer=0;
int CoolDown=0;
int cnt=0;
bool StartupFin=false;



//set Var for startup
int DataInStart[msgtype::numberStart][msgtype::MaxLgthStrt] ={
    //msg 1; 
    //3 lang
    //{85 ,32 ,240,},
    {0x55,0x20,0xf0},
    //msg 2
    //24 lang
    //{85, 54, 15, 39, 0, 0,232, 3, 208, 7, 184, 11, 184, 11, 158, 0, 232, 3, 0, 0, 5, 208, 7, 0},
    {0x55, 0x36, 0x0F, 0x27, 0x00, 0x00, 0xE8, 0x03, 0xD0, 0x07, 0xB8, 0x0B, 0xB8, 0x0B, 0x9E, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x05, 0xD0, 0x07, 0x00},
    //msg 3
    //10 lang
    //{85, 97, 76, 65, 66, 69, 76, 48, 208, 7,},
    {0x55, 0x61, 0x4C, 0x41, 0x42, 0x45, 0x4C, 0x30, 0xD0, 0x07},
    //msg 4
    //34 lang
    //{85, 129, 208, 7, 0, 0, 200, 0, 0, 0, 1, 54, 16, 1, 192, 100, 0, 0, 0, 30, 30, 16, 39, 0, 0, 0, 200, 0, 48, 117, 4, 0, 0, 0}
    {0x55,0x81,0xD0,0x07,0x00,0x00,0xC8,0x00,0x00,0x00,0x01,0x36,0x10,0x01,0xC0,0x64,0x00,0x00,0x00,0x1E,0x1E,0x10,0x27,0x00,0x00,0x00,0xC8,0x00,0x30,0x75,0x04,0x00,0x00,0x00},
  };
int DataOutStart[msgtype::numberStart][msgtype::MaxLgthStrt];
//set Var for Communication
int DataInCom[msgtype::numberCom][msgtype::MaxLgthCom]={
    //Com msg 1
    //{85, 72, 25, 4, 23, 4, 239, 55, 239, 55,   4,  42,   69,  0,  0, 2, 0, 0, 0, 0},
    //                                                    ____ <- winkel              
    {0x55,0x48,0x19,0x04,0x17,0x04,0xEF,0x37,0xEF,0x37,0x04,0x31,0x40,0x00,0x00,0x02,0x00,0x00,0x00,0x00},
    //Com msg 2
    //{85, 89, 33, 2,  0, 0,  83, 49,   0, 68, 224, 167, 255, 68, 76, 0, 0, 0, 0}
    {0x55,0x59,0x21,0x02,0x00,0x00,0x53,0x31,0x00,0x44,0xE0,0xA7,0xFF,0x44,0x4C,0x00,0x00,0x00,0x00}
  };
int DataOutCom[msgtype::numberCom][msgtype::MaxLgthCom];


// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate
  Serial1.begin(250000);
  // Display setup
    // set up the LCD's number of columns and rows:

  lcd.begin(16,2);

}

void loop(){


Startup_com(ComAktiv);

//start up sollte funktionieren
if (!StartupFin 
    && ((cnt == 3) || (cnt == 28) || (cnt == 39)))  
{
  MsgNumb++;
  BitNumb=0;
  delay(5);
  if ((Serial.read() == 0x55))
  {
    ComStatus=Uart_Data_RW(BitNumb, DataInStart[MsgNumb][BitNumb], DataOutStart[MsgNumb][BitNumb]);
  }
  
  if (ComStatus == 1)
  {
    cnt++;
  }
}
else if (!StartupFin &&cnt == 74)
{
  cnt = 0;
  MsgNumb=0;
  BitNumb=0;
  StartupFin = true;
}
else if (!StartupFin && ComAktiv)
{
  //ComStatus=Uart_Data_RW(BitNumb, DataInStart[MsgNumb][BitNumb], DataOutStart[MsgNumb][BitNumb]);
  ComStatus=Uart_Data_RW(BitNumb, DataInStart[MsgNumb][BitNumb], DataOutStart[MsgNumb][BitNumb]);
  if (ComStatus == 1)
  {
    cnt++;
  }
}

if (StartupFin && (cnt == 20))
{
  MsgNumb++;
  BitNumb=0;
  if ((Serial.read() == 0x55))
  {
    ComStatus=Uart_Data_RW(BitNumb, DataInCom[MsgNumb][BitNumb], DataOutCom[MsgNumb][BitNumb]);
  }
  
  if (ComStatus == 1)
  {
    cnt++;
  }
}
else if (StartupFin && (cnt == 39))
{
  cnt = 0;
  MsgNumb = 0;
}
else if (StartupFin)
{

  if ((Serial.read() == 0x55) || cnt > 0 )
  {
  ComStatus=Uart_Data_RW(BitNumb, DataInCom[MsgNumb][BitNumb], DataOutCom[MsgNumb][BitNumb]);
  }
  if (ComStatus == 1)
  {
    cnt++;
  }
}


//Uart_Test(ComAktiv, BitNumb, MsgNumb, DataInStart, DataOutStart);

/*
  if (LcdRefresh(10))
  {
    VarBuffer = cnt;
    // Wert des zündwinkels ausgeben bit 13
    lcd.setCursor(0, 0);
    lcd.print("send:");
    lcd.print(VarBuffer);

    // Wert der Frequenz ausgeben bit 13
    lcd.setCursor(0, 1);
    lcd.print("receive:");
    lcd.print(millis());
  }
*/


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



//test serial write

/*
// Com Start
  switch (ComStep)
  {
  case 0:

    if ((combyte::Startbyte == Serial.read()) && !ComAktiv)
    //if (true)
    {
				ComAktiv = true;
    }

    if (ComAktiv)
    {
      ComStep = 1;

    };
    delay(10);
    
    break;
  case 1:
    ComStatus = Uart_Start_Com_1(ComAktiv, BitNumb, MsgNumb, DataInStart[BitNumb][MsgNumb], DataOutStart[BitNumb][MsgNumb]);

    if (ComStatus == 1)
    {
      ComStep= 99;
    };
    
    break;
  default:
    
    ComStatus = Uart_Data_Com(ComAktiv, BitNumb, MsgNumb, DataInCom, DataOutCom);
    
    break;
  }
  */
  

 // Time out
 // ComAktiv = uart_timeout(TimeOutCnt, MaxTimeOut);
 //
 // if (!ComAktiv)
 // {
 //   ComStep = 0;
 // }
 //
}