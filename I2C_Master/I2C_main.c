/*
 * I2C_main.c
 *
 *  Created on: Dec 28, 2020
 *      Author: khalil
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include "avr/delay.h"
#include "BIT_MATH.h"
#include "I2C_PRIVATE.h"
#include "LCD_interface.h"
#include "LCD_I2C_Interface.h"

void main (void)
{
	/*
		//LCD_I2C_init();
	LCD_I2C_SendNum(125);
	LCD_I2C_SendString("/");
	LCD_I2C_SendString("Ahmed");
	*/


	u8 init_array[]= {
			0b00111000,
			0b00001100,
			0b00000001

	};
	LCD_I2C_init(init_array,3);
		LCD_I2C_SendNum(125);
		LCD_I2C_SendString("/");
		LCD_I2C_SendString("Ahmed");
		while(1);

}

