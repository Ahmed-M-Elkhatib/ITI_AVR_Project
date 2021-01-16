/*
 * master_main.c
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */

#include "LIB/STD_TYPES.h"

#include "UART/UART_Interface.h"
#include "LCDI2C_Master/LCDI2C_Interface.h"
#include <util/delay.h>

int main(void)
{
	char uart_buffer[50]={0};
	UART_VidInit();
	LCDI2C_Init();
	u8 arr[8]={0x00,0x1B,0x1F,0x1F,0x0E,0x04,0x04,0x00};

	LCDI2C_SaveCustomChar(arr,0);

	while(1)
	{

		LCDI2C_PrintString("AVR FinalProject");
		_delay_ms(2000);
		LCDI2C_SendCommand(CLEAR_DISPLAY);
		_delay_ms(2000);
		LCDI2C_PrintString("Integers :");
		LCDI2C_SetCursorPosition(0,1);
		LCDI2C_PrintInt(-256);
		_delay_ms(2000);
		LCDI2C_SendCommand(CLEAR_DISPLAY);
		_delay_ms(2000);

		LCDI2C_SetCursorPosition(0,0);
		LCDI2C_PrintString("Floats: ");
		LCDI2C_SetCursorPosition(0,1);
		LCDI2C_PrintFloat(-256.999f,3);
		_delay_ms(2000);
		LCDI2C_SendCommand(CLEAR_DISPLAY);
		_delay_ms(2000);
		LCDI2C_SetCursorPosition(0,0);



		/* sine wave */
		u8 n = 15;
		u8 line_no= 0;

		for(int i=0; i<24;i++)
		{


			LCDI2C_SendCommand(CLEAR_DISPLAY);
			LCDI2C_SetCursorPosition(n,line_no);
			LCDI2C_PrintString("Khatib");
			_delay_ms(500);


			if(n<0)
			{
				n = 15;
			}
			else
			{
				n-= 2 ;
			}
	line_no = (line_no+1)%2 ;
		}
		LCDI2C_SendCommand(CLEAR_DISPLAY);
		_delay_ms(2000);

		n = 0;
		line_no= 0;

		for(int i=0; i<24;i++)
		{


			LCDI2C_SendCommand(CLEAR_DISPLAY);
			LCDI2C_SetCursorPosition(n,line_no);
			LCDI2C_SendData(0);
			LCDI2C_PrintString("Rana");
			LCDI2C_SendData(0);
			_delay_ms(500);


			if(n>15)
			{
				n = 0;
			}
			else
			{
				n+= 2 ;
			}
			line_no = (line_no+1)%2 ;
		}
		LCDI2C_SendCommand(CLEAR_DISPLAY);
		_delay_ms(2000);
		LCDI2C_SetCursorPosition(0,0);
		LCDI2C_PrintString("Uart RX:");
		LCDI2C_SetCursorPosition(0,1);
		UART_scanf(uart_buffer,50);
		LCDI2C_PrintString(uart_buffer);
		_delay_ms(2000);
		LCDI2C_SetCursorPosition(0,0);
		LCDI2C_SendCommand(CLEAR_DISPLAY);


	}

return 0;
}

