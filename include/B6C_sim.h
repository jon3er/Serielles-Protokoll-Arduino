#pragma once

void Startup_com(bool &Connected);
// connected true -> finished

int Uart_Start_Com(bool &Connected, int &bytecnt, int &msgNumber, int (&Data_in), int (&Data_out));
// return   -1 not connected
//          0 running
//          1 startup finished

int Uart_Data_Com(bool &Connected, int &bytecnt, int &msgNumber, int (&Data_in), int (&Data_out));
// return   -1 not connected
//          0 running
//          1 msg finished


void uart_testcom(int &bit_numb, bool &com_aktiv, int *msg, int *data_in, int *data_out);