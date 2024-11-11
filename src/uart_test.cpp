#include <Arduino.h>
#include <uart.h>

int SendDelay = 48; // Delay in MuS


void uart_test()
{

  for (int i = 0; i < 8; i++)
  {
    delayMicroseconds(35+SendDelay); //ab 35 reagiert er erst für 12 bits je 4 MuS auf addieren
    Serial.write(255);
    
  }

  delay(100);

}