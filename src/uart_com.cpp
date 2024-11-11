#include <Arduino.h>
#include <uart.h>

void uart_com()
{
    
    int msg_read;
    int UartDataOut1[20]={85,72,25,4,23,4,224,55,224,55,4,50,77,102,0,2,0,0,0,0}; //Data1 Msg
    int UartDataIn1[19];
    int UartDataOut2[19]={85,89,33,2,196,0,4,11,0,4,193,170,255,4,77,0,0,0,0}; //Data2 Msg
    int UartDataIn2[18];
    int UartDataWrite;
    //read broadcast msg
    msg_read = Serial.read();
    

    //if (msg_read == 55)
    {
        for (int i=0 ; i < int(sizeof(UartDataOut1)); i++)
        {
            UartDataWrite = UartDataOut1[i];

            Serial.write(UartDataWrite);

            delayMicroseconds(4);
            
            UartDataIn1[i] = Serial.read();
            
            delayMicroseconds(4);
        }
            
    }
    
    //reset broadcast msg
   
    msg_read = 0;

    msg_read = Serial.read();

    if (msg_read == 55)
    {
        for (int i=0 ; i < int(sizeof(UartDataOut2)); i++)
        {
            UartDataWrite = UartDataOut2[i];

            Serial.write(UartDataWrite);

            delayMicroseconds(4);
            
            UartDataIn2[i] = Serial.read();
            
            delayMicroseconds(4);
        }
            
    }
 
}