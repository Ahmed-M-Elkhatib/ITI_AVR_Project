/*
 * LCDI2C_slave.c
 *
 *  Created on: Jan 10, 2021
 *      Author: mazen
 */
#include "STD_TYPES.h"
#include "I2C_Interface.h"
#include "LCDI2C_slave.h"

extern u8 flag;   // what does this do ?


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



