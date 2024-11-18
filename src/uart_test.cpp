#include <Arduino.h>
#include <uart.h>

int SendDelay = 48; // Delay in MuS
int bit_numb;

void uart_test()
{

  for (int i = 0; i < 8; i++)
  {
    delayMicroseconds(35+SendDelay); //ab 35 reagiert er erst für 12 bits je 4 MuS auf addieren
    Serial.write(255);
    
  }

  delay(100);

}

void uart_passthrough()
{
  if (Serial.available() > 0)
  {
    Serial.write(Serial.read());  //Kopiert empfangene daten auf daten ausgang
  }

}

void uart_testcom()
{


bit_numb = Serial.available();

switch (bit_numb)
{
case 1 || 2:

  Serial.write(Serial.read());  
case 3:

  Serial.write(25);

default:
  break;
}

for (int i = 0; i < 1; i++)
{
  
  

}


}