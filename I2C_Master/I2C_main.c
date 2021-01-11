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
#define Num   	1
#define Str   	2
#define command 3
void LCD_I2C_init(void);
void LCD_I2C_send_NUM(u16 Copy_num);
void LCD_I2C_send_str(u8* Copy_str);
void LCD_I2C_send_Command(u8 Copy_com);

void main (void)
{
		LCD_I2C_init();
		LCD_I2C_send_NUM(125);
		LCD_I2C_send_str("/");
		LCD_I2C_send_str("Ahmed");


		while(1);

}









void LCD_I2C_init(void)
{
	_delay_ms(40);
	I2C_master_init();
	_delay_ms(120);
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);
	I2C_Master_send_data(command);
	_delay_ms(100);
	I2C_Master_send_data(0b00111000);
	_delay_ms(100);
	I2C_Master_send_data(command);
	_delay_ms(100);
	I2C_Master_send_data(0b00001100);
	_delay_ms(100);
	I2C_Master_send_data(command);
	_delay_ms(100);
	I2C_Master_send_data(0b00000001);
	_delay_ms(10);
	I2C_stop();
}
void LCD_I2C_send_NUM(u16 Copy_num)
{
	u8 LSB=(u8)Copy_num;
	u8 MSB= (u8)(Copy_num>>8);

		I2C_send_start();
		I2C_select_slave(5,0);
		_delay_ms(200);
		I2C_Master_send_data(Num);
		_delay_ms(200);
		I2C_Master_send_data(LSB);
		if (MSB==0)
		{
			I2C_stop();
		}
		else
		{
			_delay_ms(200);
			I2C_Master_send_data(MSB);
			I2C_stop();
		}
}


void LCD_I2C_send_str(u8* Copy_str)
{
	u8 i=0;
		I2C_send_start();
		I2C_select_slave(5,0);
		_delay_ms(100);
		I2C_Master_send_data(Str);
		_delay_ms(100);
		while(Copy_str[i]!='\0')
		{
			I2C_Master_send_data(Copy_str[i]);
			i++;
			_delay_ms(100);
		}
		I2C_Master_send_data('\0');
		I2C_stop();
}

void LCD_I2C_send_Command(u8 Copy_com)
{
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);
	I2C_Master_send_data(command);
	_delay_ms(100);
	I2C_Master_send_data(Copy_com);
	I2C_stop();

}

