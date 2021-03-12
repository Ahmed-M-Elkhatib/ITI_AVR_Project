/*
 * LCDI2C_prog.c
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */

#include "../LIB/STD_TYPES.h"
#include "../TWI/TWI_Interface.h"

#include <stdlib.h>
#include <util/delay.h>


#include "LCDI2C_Interface.h"
#include "LCDI2C_Config.h"

#define LCDI2C_String  	 		4
#define LCDI2C_Command 			5
#define LCDI2C_Data 			6
#define LCDI2C_CGRAMData		7

#define CGRAM_BASE 				0x40

static void TWI_start_and_wait(void)
{
	u8 status;
	while (1)
	{
		status = TWI_Start_TRX();								/* Read TWI status register with masking lower three bits */
		if (status != TWI_MTX_START)
		{
			/* Check weather start condition transmitted successfully or not? */
			continue; /* If no then continue with start loop again */
		}

		status =TWI_SendSlaveAddress(5,TWI_WRITE);

		if (status != TWI_MTX_SLAW_ACK )	/* Check weather SLA+W transmitted & ack received or not? */
		{
			TWI_Stop_TRX();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

u8 LCDI2C_SendCommand(u8 cmd)
{
	u8 status = 0;
	TWI_start_and_wait();
	_delay_ms(5);
	status = TWI_SendData(LCDI2C_Command);
	if(status != TWI_MTX_DATA_ACK){  return 5;  }
	status = TWI_SendData(cmd);
	if(status != TWI_MTX_DATA_ACK){  return 5;  }
	status = TWI_Stop_TRX();
	return 0;
}



void LCDI2C_Init(void)
{
//	u8 status = 0;
	u8 command1 = (0x04 | (LCD_ENTRYMODE_ID<<1) | (LCD_ENTRYMODE_S<<0));
	u8 command2 = (0x08 | (LCD_DISPLAY_C<<1) | (LCD_DISPLAY_D<<2)  | (LCD_DISPLAY_B<<0));
	_delay_ms(40);

	TWI_VidInit();
	_delay_ms(120);

	LCDI2C_SendCommand(command1);
	_delay_ms(100);
	LCDI2C_SendCommand(command2);
	_delay_ms(100);
	LCDI2C_SendCommand(CLEAR_DISPLAY);
	_delay_ms(100);

}

u8 LCDI2C_SendData(u8 data)
{
	u8 status = 0;
	TWI_start_and_wait();
	_delay_ms(5);
	status = TWI_SendData(LCDI2C_Data);
	if(status != TWI_MTX_DATA_ACK){  return 5;  }
	status = TWI_SendData(data);
	if(status != TWI_MTX_DATA_ACK){  return 5;  }
	status = TWI_Stop_TRX();
	return 0;
}

u8 LCDI2C_PrintString(char* string)
{
//	u8 status = 0;


//	/* the slave has a listen function which waits for
//	 * SLA+W to begin recieving a string
//	 * AND ALSO...
//	 * the slave while loop is designed to receive two bytes initially
//	 * and only the first byte tells the the loop its a string, so
//	 * the second byte is redundant */
//	TWI_start_and_wait();
//	_delay_ms(5);
//	status = TWI_SendData(LCDI2C_String);
//	if(status != TWI_MTX_DATA_ACK){  return 5;  }
//	status = TWI_SendData(LCDI2C_String);
//	if(status != TWI_MTX_DATA_ACK){  return 5;  }
//	status = TWI_Stop_TRX();

//	/* start communication again to signal the slave listen function */
//	TWI_start_and_wait();
//	_delay_ms(5);
//	u8 iDx=0;
//	do
//	{
//		status = TWI_SendData(string[iDx]);
//		_delay_ms(5);
//		if(status != TWI_MTX_DATA_ACK )
//		{
//			return 5;
//		}
//		iDx++;
//
//	}while(( string[iDx] != '\0')|| (iDx<39));

	for(int i=0; string[i]!='\0';i++)
	{

		LCDI2C_SendData(string[i]);
		_delay_ms(5);
		if(i>40)
		{
			break;
		}
	}


	return 0;
}

void LCDI2C_PrintInt(s32 num)
{
	char number[10]={0};
	itoa(num,number,10);
	LCDI2C_PrintString(number);
}

void LCDI2C_PrintFloat(f32 fnum, u8 precision)
{
	u32 e=1;
	s32 Int=(s32)fnum;
	s32 Float;
	for(u8 i=0;i<precision;i++)
	{
		e=e*10;
	}
	Float=(s32) ((fnum -(f32)Int) *e);
	if (fnum<0)
	{
		Float *= -1;
	}
	LCDI2C_PrintInt(Int);
	LCDI2C_SendData('.');
	LCDI2C_PrintInt(Float);
}

void LCDI2C_SaveCustomChar(u8* arr,u8 CGramAddress)
{
	LCDI2C_SendCommand(CGRAM_BASE+(CGramAddress*8)); //set CGRAM address command

	for(int i=0; i<8;i++)
	{
		LCDI2C_SendData(arr[i]);
		_delay_ms(5);
	}

	LCDI2C_SendCommand(0x80); //set reading to be from DDRAM again

}

void LCDI2C_SetCursorPosition(u8 x, u8 y)
{
	if((y%2) == 0)
	{
		LCDI2C_SendCommand(DISPLAY_ORG + (x%16) );
	}
	else
	{
		LCDI2C_SendCommand(DISPLAY_ORG + (x%16) + 64 );
	}
}

