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
	_delay_ms(100);

	I2C_Master_send_data(LCD_I2C_Command);
	_delay_ms(100);
	I2C_Master_send_data(command1);
	_delay_ms(100);
	I2C_Master_send_data(LCD_I2C_Command);
	_delay_ms(100);
	I2C_Master_send_data(command2);
	_delay_ms(100);
	I2C_Master_send_data(LCD_I2C_Command);
	_delay_ms(100);
	I2C_Master_send_data(LCD_COMMAND_CLEARDISP);

	_delay_ms(10);
	I2C_stop();
}
void LCD_I2C_SendNum(s32 Copy_u32num)
{
	char number[10]={0};
	itoa(Copy_u32num,number,10);
	LCD_I2C_SendString(number);
	/*// For checking if the number is negative or not
	u8 signindicate = (Copy_u32num<0)? 1:0;

	if(signindicate){
		// The number is -ve
		Copy_u32num = Copy_u32num * -1;
	}
	u8 LSB1=(u8)Copy_u32num;
	u8 LSB2=(u8)(Copy_u32num>>8);
	u8 MSB1=(u8)(Copy_u32num>>16);
	u8 MSB2=(u8)(Copy_u32num>>24);
	if(signindicate){
		LCD_I2C_SendData('-');

	}

	// Start the transmission
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(200);

	I2C_Master_send_data(LCD_I2C_Integer);


	_delay_ms(200);
	I2C_Master_send_data(LSB1);
	_delay_ms(200);
	I2C_Master_send_data(LSB2);
	_delay_ms(200);
	I2C_Master_send_data(MSB1);
	_delay_ms(200);
	I2C_Master_send_data(MSB2);

	_delay_ms(10);
	I2C_stop();*/
}
void LCD_I2C_SendString(char* Copy_u8str)
{

	u8 i=0;
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);

	I2C_Master_send_data(LCD_I2C_String);
	_delay_ms(100);

	while(Copy_u8str[i]!='\0')
	{
		I2C_Master_send_data(Copy_u8str[i++]);
		_delay_ms(100);
	}

	I2C_Master_send_data('\0');
	_delay_ms(10);
	I2C_stop();
}
void LCD_I2C_SendCommand(u8 Copy_u8Command)
{
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);

	I2C_Master_send_data(LCD_I2C_Command);
	_delay_ms(100);

	I2C_Master_send_data(Copy_u8Command);
	_delay_ms(10);
	I2C_stop();
}

void LCD_I2C_SendData(u8 Copy_u8Data)
{
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);

	I2C_Master_send_data(LCD_I2C_Data);
	_delay_ms(100);

	I2C_Master_send_data(Copy_u8Data);
	_delay_ms(10);
	I2C_stop();
}

void LCD_I2C_SendFloat(f32 Copy_u8Fnum){

	s16 Int=(s16)Copy_u8Fnum;
	s16 Float=(s16) ((Copy_u8Fnum -Int) *100);
	Float *= -1;
	LCD_I2C_SendNum(Int);
	LCD_I2C_SendData('.');
	LCD_I2C_SendNum(Float);
}


void LCD_I2C_SetPosition(u8 Copy_U8PosX,u8 Copy_U8PosY){
/*
	if(0== Copy_U8PosX)
		LCD_send_command(128+Copy_U8PosY);
	else if(1==Copy_U8PosX)
		LCD_send_command(128+64+Copy_U8PosY);
*/
	LCD_I2C_SendCommand(0x80 | (Copy_U8PosX & 0x3F) | (GET_BIT(Copy_U8PosY,0) << 6));
}


void LCD_I2C_SetCGRAMAdress(u8 Copy_U8Address){

	LCD_I2C_SendCommand	(0b01000000 | Copy_U8Address);

}


void LCD_I2C_WriteInCGRAM(u8 *Copy_U8ptr)
{
//CGRAMData

	u8 i = 0;
	_delay_ms(40);
	I2C_master_init();
	_delay_ms(120);
	I2C_send_start();
	I2C_select_slave(5,0);
	_delay_ms(100);
	I2C_Master_send_data(LCD_I2C_CGRAMData);

	for(i = 0; i<8;i++){
		_delay_ms(100);
		I2C_Master_send_data(Copy_U8ptr[i]);
	}
	_delay_ms(10);
	I2C_stop();
}
