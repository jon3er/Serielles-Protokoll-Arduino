#include <Arduino.h>
#include <uart.h>

void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate

  // Display setup

}


void loop(){

  uart_com();

  //uart_test();
  
}