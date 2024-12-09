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

  int BitNumb;
  bool ComAktiv;
  int Msg[38]


  void uart_testcom(int &BitNumb, bool &ComAktiv, int *Msg, int *DataIn, int *DataOut)

  //uart_test();
  
}