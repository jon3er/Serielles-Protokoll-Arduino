#pragma once

//kommunikations fkt
void uart_com();

void Startup_com();

int Uart_Start_Com();

int Uart_Data_Com();

//test fkt
void uart_test();

void uart_passthrough();

void uart_testcom();

void uart_testcom(int&, bool&, int*, int*, int*);