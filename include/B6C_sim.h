#pragma once

void Startup_com(bool);
// connected true -> finished

int Uart_Start_Com();
// return   -1 not connected
//          0 running
//          1 startup finished

int Uart_Data_Com();
// return   -1 not connected
//          0 running
//          1 msg finished


void uart_testcom();