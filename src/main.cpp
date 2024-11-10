#include <Arduino.h>
#include <uart_com.h>

void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate

  // Display setup

}


void loop(){

  uart_com();

  /*
  Serial.write(255);
  Serial.write(0);
  Serial.write(1);
  Serial.println(1,BIN);

  delay(100);
  */
}