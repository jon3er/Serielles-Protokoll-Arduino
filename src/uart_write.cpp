#include <Arduino.h>

void uart_write();

void uart_write()
{
    
    int msg;
    int UartData[19]={85,89,33,02,00,00,83,49,00,68,224,167,255,68,240,59,3,0,0};

    msg = Serial.read();
    

    if (msg == 55)
    {
        for (int i=0 ; i<sizeof(UartData); i++)
        {
            Serial.write(UartData[i]);

        }
            
    }
}