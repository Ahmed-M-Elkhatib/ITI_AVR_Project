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
	/*
		//LCD_I2C_init();
	LCD_I2C_SendNum(125);
	LCD_I2C_SendString("/");
	LCD_I2C_SendString("Ahmed");
	*/


	LCD_I2C_init();
	LCD_I2C_SendFloat(-12.5);
		LCD_I2C_SendString("/");
		LCD_I2C_SendString("Ahmed");
		while(1);

}

