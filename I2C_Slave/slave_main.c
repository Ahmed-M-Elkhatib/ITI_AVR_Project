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



u8 buffer[SLAVE_BUFFER_SIZE]={'A','B','C','D'};
u8 CGram_buffer[CGRAM_BUFFER_SIZE]={0};

u8 byte1=0,byte2=0;
u8 flag=0;

int main (void)
{

	LCDI2C_Init();
	LCD_VidPrintString("Slave Waiting...",0);
	_delay_ms(1000);
	while(1)
	{
		LCDI2C_Receive_2Byte(&byte1,&byte2);
		_delay_ms(10);
		if (byte1==CMD)
		{
			/*LCD_VidPrintString("RX: CMD",0);
			_delay_ms(1000);
			LCD_VidSendCommand(CLEAR_DISPLAY);
			_delay_ms(1000);*/


			LCD_VidSendCommand(byte2);
			flag=0;
		}
//		else if (byte1==NUM)
//		{
//			LCD_VidPrintString("RX: NUM",0);
//			_delay_ms(1000);
//			LCD_VidSendCommand(CLEAR_DISPLAY);
//			_delay_ms(1000);
//
//			LCD_VidPrintNum((s32)byte2);
//			flag=0;
//		}
		else if(byte1==STR)
		{
			/*LCD_VidPrintString("RX: STR",0);
			_delay_ms(1000);
			LCD_VidSendCommand(CLEAR_DISPLAY);
			_delay_ms(1000);*/


			LCDI2C_Receive_String(buffer);
			LCD_VidPrintString((char*)buffer,0);
		}
		else if (byte1==DATA)
		{
			/*LCD_VidPrintString("RX: DATA",0);
			_delay_ms(1000);
			LCD_VidSendCommand(CLEAR_DISPLAY);
			_delay_ms(1000);*/

			LCD_VidSendChar(byte2);
			flag=0;
		}
		else if (byte1==CGRAMData)
		{
			LCDI2C_Receive_CGram(CGram_buffer,byte2);
		}
	}
}
