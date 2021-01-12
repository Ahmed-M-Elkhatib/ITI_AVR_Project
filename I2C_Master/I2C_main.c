/*
 * I2C_main.c
 *
 *  Created on: Dec 28, 2020
 *      Author: khalil
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "I2C_PRIVATE.h"
#include "LCD_interface.h"
#include "LCD_I2C_Interface.h"

int main (void)
{

	u8 arr[8]={0x00,0x1B,0x1F,0x1F,0x0E,0x04,0x04,0x00};

	LCD_I2C_init();
	LCD_I2C_SendFloat(1254.1245,5);
	_delay_ms(1000);
	LCD_I2C_SendCommand(LCD_COMMAND_CLEARDISP);
	LCD_I2C_SendFloat(-10.5,1);
	_delay_ms(1000);
	LCD_I2C_SendCommand(LCD_COMMAND_CLEARDISP);
	LCD_I2C_SendFloat(32.54,2);
	_delay_ms(1000);
	LCD_I2C_SendCommand(LCD_COMMAND_CLEARDISP);
	LCD_I2C_WriteInCGRAM(arr,0);
	LCD_I2C_SendData(0);

	while(1);

}

