#include <Arduino.h>

void uart_com()
{
    //msg
    int msg_read;
    bool msg_start;
    int BCByte = 85;
    //timing
    int OneBitDelay = 44;
    int DelayOffset = 35;


    int UartDataOut1[20]={85,32,25,4,23,4,224,55,224,55,4,50,77,102,0,2,0,0,0,0}; //Data1 Msg
    int UartDataIn1[19];
    int UartDataOut2[19]={85,89,33,2,196,0,4,11,0,4,193,170,255,4,77,0,0,0,0}; //Data2 Msg
    int UartDataIn2[18];
    int UartDataWrite;
    //read broadcast msg
    msg_read = Serial.read();
    
    

    if (msg_read == BCByte)
    {   
        msg_start = true;

        for (int i=0 ; i < int(sizeof(UartDataOut1)); i++)
        {
            UartDataWrite = UartDataOut1[i];

            delayMicroseconds(OneBitDelay+DelayOffset);

            Serial.write(UartDataWrite);

            
            
            //UartDataIn1[i] = Serial.read();
            
        }
            
    }
    
    //reset broadcast msg
   
    msg_read = 0;

    msg_read = Serial.read();

    if ((msg_read == BCByte) && (msg_start == true))
    {
        for (int i=0 ; i < int(sizeof(UartDataOut2)); i++)
        {
            UartDataWrite = UartDataOut2[i];

            delayMicroseconds(OneBitDelay+DelayOffset);

            //UartDataIn2[i] = Serial.read();
            
        }
        
        msg_start = false;
    }
 
}

bool uart_timeout(int TimeOutCnt, int MaxTimeOut)
{
  int cnt;
  // Time Out Counter
  if (Serial.available() == 0)
  {
    ;
      TimeOutCnt++;
    
  }
  else
  {
    TimeOutCnt = 0;
  }
  
  //Connection lost
  if (TimeOutCnt < MaxTimeOut)
  {
    return true;
  }
  else
  {
    return false;
  }

};
