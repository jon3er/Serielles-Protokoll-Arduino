#include <Arduino.h>
#include <uart.h>
#include <uart_msg.h>


void Startup_com(bool &Connected)
{
    
    if (combyte::Startbyte == Serial.read() & !Connected)
    {
				Connected = true;
    }

}

int Uart_Start_Com(bool &Connected, int &bytecnt, int &msgNumber, int (&Data_in)[msgtype::number][msgtype::Maxlength], int (&Data_out)[msgtype::number][msgtype::Maxlength])
{
	
	int SerialAvailable = Serial.available();
	
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
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next Msg
			msgNumber++;
			bytecnt = 0;
			break;
		
		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;
		}

		break;
	case (msgtype::StartMsg2):
		
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg2_RX:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}


		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;
		}

		break;
	case (msgtype::StartMsg3):
		
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg3_RX:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next Msg
			bytecnt++;
			if (msgbyte::Startup_msg3_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}


		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;
		}


		break;
	case (msgtype::StartMsg4):
		
switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Startup_msg4_RX:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next Msg
			bytecnt++;msgNumber++;
			if (msgbyte::Startup_msg4_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;

				return 1;
			}


		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;
		}

		break;
	
	default:
		break;
	}

	return 0;

}

int Uart_Data_Com(bool &Connected, int &bytecnt, int &msgNumber, int (&Data_in)[msgtype::number][msgtype::Maxlength], int (&Data_out)[msgtype::number][msgtype::Maxlength])
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
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;
			}


		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;

		break;
	case (msgtype::ComMsg2):
		
		switch (bytecnt)
		{
		
		case msgbyte::Commander_byte_pos ... msgbyte::Com_msg2_RX:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//write Data
			Serial.write(Data_out[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			if (msgbyte::Startup_msg2_RX == msgNumber)
			{
				msgNumber++;
				bytecnt = 0;

				return 1;
			}


		default:
			//read Data
			Data_in[msgNumber][bytecnt]= Serial.read();
			//Write Data
			Serial.write(Data_in[msgNumber][bytecnt]);
			//next byte
			bytecnt++;
			break;
		}
	}
	default:
		break;

	return 0;
	}
}

void uart_testcom(int &bit_numb, bool &com_aktiv, int *msg, int *data_in, int *data_out)
{

int msgSum;

//check end of msg
if (bit_numb >= 3)
{
	msgSum = msg[bit_numb] + msg[bit_numb-1] + msg[bit_numb-2] + msg[bit_numb-3];
}
else
{
  msgSum = msg[bit_numb];
}

// Kommunikation überprüfen start / stop
if ((0x55==Serial.read()) && bit_numb == 0)
{
  com_aktiv = true;
  // antwort delay für erste nachricht
  delay(10);
}
else if(msgSum == 0)
{
  bit_numb = 0;

  com_aktiv = false;
}

// bitnummer festlegen
if (Serial.available() )
{
bit_numb = bit_numb++; 
}

// Daten lesen und im array speichern
data_out[bit_numb] = Serial.read();



// Daten raus schreiben
switch (bit_numb)
{
case 1 || 2:

  Serial.write(Serial.read());  
case 3-38:

  Serial.write(data_in[bit_numb]);

case 39:

 com_aktiv = false;

default:
  
  bit_numb=0;

}


}