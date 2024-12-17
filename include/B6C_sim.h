#pragma once
#include <e_uart_msg.h>

void Startup_com(bool &Connected);
// connected true -> finished

int Uart_Data_RW(int &bytecnt, int &Data_in, int &Data_out);
/// @brief  
/// @param bytecnt 
/// @param Data_in 
/// @param Data_out 
/// @return 0 if data RW else 1

int Uart_Start_Com(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthStrt], int Data_out[][msgtype::MaxLgthStrt]);
// return   -1 not connected
//          0 running
//          1 startup finished

int Uart_Data_Com(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthCom], int Data_out[][msgtype::MaxLgthCom]);
/// @brief   -1 not connected \n 0 running; 1 msg finished
//          
//          


void Uart_Test(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthStrt], int Data_out[][msgtype::MaxLgthStrt]);

int Uart_Start_Com_1(bool &Connected, int &bytecnt, int &msgNumber, int &Data_in, int &Data_out);