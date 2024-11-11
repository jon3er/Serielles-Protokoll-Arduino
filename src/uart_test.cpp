#include <Arduino.h>
#include <uart.h>

void uart_test()
{

  for (int i = 0; i < 8; i++)
  {
    Serial.write(255);
    delayMicroseconds(4);
  }

  delay(100);

}