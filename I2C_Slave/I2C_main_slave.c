/*
 * I2C_main.c
 *
 *  Created on: Dec 28, 2020
 *      Author: khalil
 */

#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include "LCD_interface.h"
#include "LCD_cofig.h"
#include <util/delay.h>

#include "LCDI2C_slave.h"

#define NUM   		0
#define STR   		4
#define CMD			5
#define DATA    	6
#define CGRAMData	7


u8 buffer[SLAVE_BUFFER_SIZE]={0};
u8 CGram_buffer[SLAVE_BUFFER_SIZE]={0};
//u8 buffer_index=0;
//u8 CGram_buffer_index=0;
u8 byte1=0,byte2=0;
u8 flag=0;       // this flag to

int main (void)
{

	LCD_VidInt(); 		// intialize LCD with a default configuration
				 	   // because the user can send a configuration or not
				      // so some default configuration must be guranteed
	                 // if the user wants to change it , he simply can by sending
				    // any configuration commands

	I2C_slave_init();

	while(1)
	{
		Receive_2Byte(&byte1,&byte2);
		if (byte1==CMD)
		{
			LCD_VidSendCommand(byte2);
			flag=0;
		}
		else if (byte1==NUM)
		{
			LCD_VidSendNum(byte2);
			flag=0;
		}
		else if(byte1==STR)
		{
			Receive_String(buffer);
			LCD_VidSendStr(buffer);
		}
		else if (byte1==DATA)
		{
			LCD_VidSendData(byte2);
			flag=0;
		}
		else if (byte1==CGRAMData)
		{
			Receive_CGram(CGram_buffer);
		}
	}
}

