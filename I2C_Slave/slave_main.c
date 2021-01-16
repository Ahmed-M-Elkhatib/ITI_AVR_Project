/*
 * slave_main.c
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MAN.h"
#include "DIO/DIO_Interface.h"
#include "TWI/TWI_Interface.h"
#include "LCD/LCD_Interface.h"
#include <util/delay.h>

#include "LCDI2C/LCDI2C_Interface.h"
#include "LCDI2C/LCDI2C_Config.h"



u8 buffer[SLAVE_BUFFER_SIZE]={0};
u8 CGram_buffer[CGRAM_BUFFER_SIZE]={0};

u8 byte1=0,byte2=0;
u8 flag=0;       // this flag to

int main (void)
{

	LCD_VidInt(); 		// intialize LCD with a default configuration
				 	   // because the user can send a configuration or not
				      // so some default configuration must be guranteed
	                 // if the user wants to change it , he simply can by sending
				    // any configuration commands
	LCD_VidSendStr((u8*)"Slave Waiting...");
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
