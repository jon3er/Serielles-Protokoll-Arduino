#include <Arduino.h>
#include <uart.h>

void setup(){

  // Uart setup
  Serial.begin(250000); //initialize serial communication at a 250000 baud rate
  Serial1.begin(250000);
  // Display setup

}


void loop(){

  uart_passthrough();

  //uart_test();
  
}