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



void uart_testcom(int &bit_numb, bool &com_aktiv, int *msg, int *data_in, int *data_out)
{

int msgSum;

//check end of msg
if (bit_numb >= 3)
{
msgSum = msg[bit_numb] + msg[bit_numb-1] + msg[bit_numb-2] + msg[bit_numb-3];
}
else
{
  msgSum = msg[bit_numb];
}

// Kommunikation überprüfen start / stop
if ((0x55==Serial.read()) && bit_numb == 0)
{
  com_aktiv = true;
  // antwort delay für erste nachricht
  delay(10)
}
else if(msgSum == 0)
{
  bit_numb = 0;

  com_aktiv = false;
}

// bitnummer festlegen
if (Serial.available() )
{
bit_numb = bit_numb++; 
}

// Daten lesen und im array speichern
data_out[bit_numb] = Serial.read();



// Daten raus schreiben
switch (bit_numb)
{
case 1 || 2:

  Serial.write(Serial.read());  
case 3-38:

  Serial.write(data_in[bit_numb]);

case 39:

 com_aktiv = false;

default:
  
  bit_numb=0;

}


}