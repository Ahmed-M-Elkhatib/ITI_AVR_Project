/*
 * LCD_I2C.c
 *
 *  Created on: Jan 3, 2021
 *      Author: Rana Yehya Mohamed
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include <util/delay.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "LCD_interface.h"
#include "LCD_I2C_Interface.h"

#include "LCD_I2C_Config.h"

//#define WITH_DELAY

#define DELAY_GCD   1
#define DELAY_FACTOR 5

#define LCD_I2C_Integer				0

#define LCD_I2C_String  	 		4
#define LCD_I2C_Command 			5
#define LCD_I2C_Data 				6
#define LCD_I2C_CGRAMData			7

void LCD_I2C_init()
{

	u8 command1 = (0x04 | (LCD_ENTRYMODE_ID<<1) | (LCD_ENTRYMODE_S<<0));
	u8 command2 = (0x08 | (LCD_DISPLAY_C<<1) | (LCD_DISPLAY_D<<2)  | (LCD_DISPLAY_B<<0));
	_delay_ms(40);
	I2C_master_init();
	_delay_ms(120);



	I2C_send_start();
	I2C_select_slave(5,0);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(LCD_I2C_Command);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(command1);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_I2C_Command);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(command2);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_I2C_Command);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_COMMAND_CLEARDISP);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD);
#endif

	I2C_stop();
}

void LCD_I2C_SendNum(s32 Copy_u32num)
{
	char number[10]={0};
	itoa(Copy_u32num,number,10);
	LCD_I2C_SendString(number);
}

void LCD_I2C_SendString(char* Copy_u8str)
{

	u8 i=0;
	I2C_send_start();
	I2C_select_slave(5,0);

#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_I2C_String);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	while(Copy_u8str[i]!='\0')
	{
		I2C_Master_send_data(Copy_u8str[i++]);
#ifdef WITH_DELAY
		_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	}

	I2C_Master_send_data('\0');
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD);
#endif
	I2C_stop();
}


void LCD_I2C_SendCommand(u8 Copy_u8Command)
{
	I2C_send_start();
	I2C_select_slave(5,0);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_I2C_Command);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(Copy_u8Command);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD);
#endif

	I2C_stop();
}

void LCD_I2C_SendData(u8 Copy_u8Data)
{
	I2C_send_start();
	I2C_select_slave(5,0);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif

	I2C_Master_send_data(LCD_I2C_Data);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(Copy_u8Data);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD);
#endif
	I2C_stop();
}

void LCD_I2C_SendFloat(f32 Copy_f32Fnum,u8 Copy_u8res){
	u32 e=1;
	s32 Int=(s32)Copy_f32Fnum;
	for(u8 i=0;i<Copy_u8res;i++)
	{
		e=e*10;
	}
	s32 Float=(s32) ((Copy_f32Fnum -(f32)Int) *e);
	if (Copy_f32Fnum<0)
	{
		Float *= -1;
	}
	LCD_I2C_SendNum(Int);
	LCD_I2C_SendData('.');
	LCD_I2C_SendNum(Float);
}


void LCD_I2C_SetPosition(u8 Copy_U8PosX,u8 Copy_U8PosY)
{

	LCD_I2C_SendCommand(0x80 | (Copy_U8PosX & 0x3F) | (GET_BIT(Copy_U8PosY,0) << 6));
}


void LCD_I2C_SetCGRAMAdress(u8 Copy_U8Address)
{

	LCD_I2C_SendCommand	(0b01000000 | Copy_U8Address);

}


void LCD_I2C_WriteInCGRAM(u8 *Copy_U8ptr,u8 Copy_u8location)
{
//CGRAMData

	u8 i = 0;
	_delay_ms(40);
	I2C_master_init();
	_delay_ms(120);

	I2C_send_start();
	I2C_select_slave(5,0);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(LCD_I2C_CGRAMData);
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(Copy_u8location);
	for(i = 0; i<8;i++)
	{
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD*DELAY_FACTOR);
#endif
	I2C_Master_send_data(Copy_U8ptr[i]);
	}
#ifdef WITH_DELAY
	_delay_ms(DELAY_GCD);
#endif
	I2C_stop();

	_delay_ms(DELAY_GCD*DELAY_FACTOR);
	LCD_I2C_SendCommand(0x80); /// set DDRam pointer
}
