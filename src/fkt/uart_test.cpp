#include <Arduino.h>

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


void uart_passthrough_2chan()
{
  if (Serial.available() > 0)
  {
    int msg;

    msg = Serial.read();
    
      Serial.write(msg);  //Kopiert empfangene daten auf daten ausgang
      Serial1.write(msg);
    
  }

}



