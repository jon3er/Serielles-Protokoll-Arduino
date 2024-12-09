#pragma once

// enum Datenstrukturen

// Länge der Datenpackete
typedef enum e_msgbytesLength
{
    //start msg length
    Startup_msg1_RX = 3-1,
    Startup_msg1_TX = 4-1,

    Startup_msg2_RX = 24-1,
    Startup_msg2_TX = 25-1,

    Startup_msg3_RX = 10-1,
    Startup_msg3_TX = 11-1,

    Startup_msg4_RX = 34-1,
    Startup_msg4_TX = 35-1,
    
    // Com msg length
    Com_msg1_RX = 20-1,
    Com_msg1_TX = 21-1,

    Com_msg2_RX = 19-1,
    Com_msg2_TX = 20-1,



    // comander byte pos
    Commander_byte_pos = 3-1,
}msgbyte;

typedef enum e_combytes
{
    Startbyte = 0x55


}combyte;

typedef enum e_messages
{
    StartMsg1 = 0,
    StartMsg2 = 1,
    StartMsg3 = 2,
    StartMsg4 = 3,
    StartFin = 4,

    ComMsg1 = 0,
    ComMsg2 = 1,

    //array info
    Maxlength = 34,
    number  = 5,
}msgtype;
