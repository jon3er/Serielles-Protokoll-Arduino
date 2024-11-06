#include <Arduino.h>


void setup(){

  Serial.begin(250000); //initialize serial communication at a 9600 baud rate

}


void loop(){

  Serial.write(255);
  Serial.write(0);
  Serial.write(1);
  Serial.println(1,BIN);

  delay(100);

}