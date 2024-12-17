#include <Arduino.h>
#include <B6C_sim.h>
#include <e_uart_msg.h>


void Startup_com(bool &Connected)
{
    
    if (combyte::Startbyte == Serial.read() & !Connected)
    {
		Connected = true;
    }

}

int Uart_Data_RW(int &bytecnt, int &Data_in, int &Data_out)
{
	
	if (Serial.available() > 0)
	{
		//read Data
		Data_out= Serial.read();
		//write Data
		Serial.write(Data_in);
		//next byte
		bytecnt++;

		return 1;
	}
	else
	{
		return 0;
	}
}


//to do verkleinern der funktions größe
int Uart_Start_Com(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthStrt], int Data_out[][msgtype::MaxLgthStrt])
{
	
	int SerialAvailable = Serial.available();
	
	if (!Connected)
	{
		return -1;
	}

	if (SerialAvailable)
	{
		switch (msgNumber)
		{
		case (msgtype::StartMsg1):

			switch (bytecnt)
			{
			case (msgbyte::Startup_msg1_RX):
				
				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);
				
				msgNumber++;
				bytecnt = 0;
				break;

			default:

				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

				break;
			}

			break;
		case (msgtype::StartMsg2):

			switch (bytecnt)
			{
			
			case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg2_RX:

				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

				if (msgbyte::Startup_msg2_RX == msgNumber)
				{
					msgNumber++;
					bytecnt = 0;
				}


			default:

				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

				break;
			}

			break;
		case (msgtype::StartMsg3):

			switch (bytecnt)
			{
			
			case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg3_RX:

				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

				if (msgbyte::Startup_msg3_RX == msgNumber)
				{
					msgNumber++;
					bytecnt = 0;
				}


			default:

				Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

				break;
			}


			break;
		case (msgtype::StartMsg4):

			switch (bytecnt)
				{
				
				case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg4_RX:

					Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);
					
					if (msgbyte::Startup_msg4_RX == msgNumber)
					{
						msgNumber++;
						bytecnt = 0;

						return 1;
					}


				default:

					Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

					break;
				}

				break;

		default:
			break;
		}

		return 0;

	}
	
}
/// @brief  -1 not connected; 0 running; 1 msg finished
/// @param Connected 
/// @param bytecnt 
/// @param msgNumber 
/// @param Data_in 
/// @param Data_out 
/// @return 
int Uart_Data_Com(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthCom], int Data_out[][msgtype::MaxLgthCom])
{

	if (!Connected)
	{
		return -1;
	}

	switch (msgNumber)
	{
	case (msgtype::ComMsg1):
		
		switch (bytecnt)
		{
		case msgbyte::Commander_byte_pos ... msgbyte::Com_msg1_RX:
			
			Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}


		default:

			Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

			break;

		break;
	case (msgtype::ComMsg2):
		
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Com_msg2_RX:

			Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;

				return 1;
			}


		default:

			Uart_Data_RW(bytecnt, Data_in[msgNumber][bytecnt], Data_out[msgNumber][bytecnt]);

			break;
		}
	}
	default:
		break;

	return 0;
	}
}


// -------ALT--------
void Uart_Test(bool &Connected, int &bytecnt, int &msgNumber, int Data_in[][msgtype::MaxLgthStrt], int Data_out[][msgtype::MaxLgthStrt])
{
	
	if (msgNumber == msgtype::StartFin)
	{
		msgNumber = 0;
		
	}

	if (bytecnt == msgbyte::Startup_msg3_TX)
	{
		msgNumber++;
		bytecnt = 0;
		delay(1000);
		
	}
	else
	{
	Serial.write(Data_in[msgNumber][bytecnt]);
	bytecnt++;
	}

}


int Uart_Start_Com_1(bool &Connected, int &bytecnt, int &msgNumber, int &Data_in, int &Data_out)
{
	
	if (!Connected)
	{
		return -1;
	}

		switch (msgNumber)
	{
	case (msgtype::StartMsg1):
		switch (bytecnt)
		{
		case (msgbyte::Startup_msg1_RX):
			
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			
			msgNumber++;
			bytecnt = 0;
			break;
		default:
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			break;
		}
		break;
	case (msgtype::StartMsg2):
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg2_RX:
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}
		default:
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			break;
		}
		break;
	case (msgtype::StartMsg3):
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg3_RX:
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			if (msgbyte::Startup_msg3_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}
		default:
			Uart_Data_RW(bytecnt, Data_in, Data_out);
			break;
		}
		break;
	case (msgtype::StartMsg4):
		switch (bytecnt)
			{
			
			case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg4_RX:
				Uart_Data_RW(bytecnt, Data_in, Data_out);
				
				if (msgbyte::Startup_msg4_RX == msgNumber)
				{
					msgNumber++;
					bytecnt = 0;
					return 1;
				}
			default:
				Uart_Data_RW(bytecnt, Data_in, Data_out);
				break;
			}
			break;
	default:
		break;
	}
	return 0;
	
	
}