/*
 * LCDI2C_slave.c
 *
 *  Created on: Jan 10, 2021
 *      Author: mazen
 */
#include "STD_TYPES.h"
#include "I2C_Interface.h"
#include "LCDI2C_slave.h"

extern u8 flag;   // what does this do ? //this flag to determine the first byte ( command) at only the first receive operation then all received
										//data will received in byte2 (as temp variable)
									   // so when flag ==0 this means that i have new connection and i need to read byte1 to know the required action
									  // then when flag==1 this means all data we receiving now are data and i don,t need to byte 1 just all data
									 //will received by byte2 as a temp variable


void Receive_2Byte(u8* Copy_byte1,u8* Copy_byte2)
{
	if (flag==0)
	{
		*Copy_byte1=I2C_Slave_recive_data(NULL);
	}
	flag=1;
	*Copy_byte2= I2C_Slave_recive_data(NULL);
}

void Receive_String(u8* buffer)
{
	u8 i = 0;
	u8 byte1=0,byte2=0;

	while(byte2!='\0')
	{
		buffer[i]=byte2;
		if(i<SLAVE_BUFFER_SIZE)
		{
			i++;
			Receive_2Byte(&byte1,&byte2);
		}
		else
		{
			break;
		}

	}

	buffer[i]='\0';
	i=0;
	flag=0;
}



