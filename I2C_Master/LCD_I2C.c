/*
 * LCD_I2C.c
 *
 *  Created on: Jan 3, 2021
 *      Author: Rana Yehya Mohamed
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include "avr/delay.h"
#include "BIT_MATH.h"
#include "LCD_interface.h"
#include "LCD_I2C_Interface.h"



#define LCD_I2C_UnsignedInteger		0
#define LCD_I2C_SignedInteger   		1

#define LCD_I2C_UnsignedFloat   		2
#define LCD_I2C_SignedFloat		  		3

#define LCD_I2C_String  	 					4
#define LCD_I2C_Command 				5
#define LCD_I2C_Data 						6

#define LCD_I2C_CGRAMData			7

void LCD_I2C_init(u8 *Copy_u8CommandArray,u8 Copy_u8Size)
{
	u8 i = 0;
	_delay_ms(40);
	I2C_master_init();
	_delay_ms(120);
	I2C_send_start();
	I2C_select_slave(LCD_I2C_Slave_Address,0);
	/*
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
	*/
	for(i = 0; i<Copy_u8Size;i++){
		_delay_ms(100);
		I2C_Master_send_data(LCD_I2C_Command);
		_delay_ms(100);
		I2C_Master_send_data(Copy_u8CommandArray[i]);
		_delay_ms(10);
	//	I2C_send_start();
	}
	_delay_ms(10);
	I2C_stop();
}
void LCD_I2C_SendNum(s16 Copy_u16num){

	// For checking if the number is negative or not
	u8 signindicate = (Copy_u16num<0)? 1:0;

	if(signindicate){
		// The number is -ve
		Copy_u16num = Copy_u16num * -1;
	}
	u8 LSB=(u8)Copy_u16num;
	u8 MSB= (u8)(Copy_u16num>>8);
	// Start the transmission
	I2C_send_start();
	I2C_select_slave(LCD_I2C_Slave_Address,0);
	_delay_ms(200);

	if(signindicate){
		// The number is -ve
		I2C_Master_send_data(LCD_I2C_SignedInteger);
	}
	else{
		// The number is +ve
		I2C_Master_send_data(LCD_I2C_UnsignedInteger);
	}

	_delay_ms(200);
	I2C_Master_send_data(LSB);
	if (MSB==0)
	{

	}
	else
	{
		_delay_ms(200);
		I2C_Master_send_data(MSB);

	}
	_delay_ms(10);
	I2C_stop();
}
void LCD_I2C_SendString(u8* Copy_u8str)
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
	I2C_select_slave(LCD_I2C_Slave_Address,0);
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
	I2C_select_slave(LCD_I2C_Slave_Address,0);
	_delay_ms(100);

	I2C_Master_send_data(LCD_I2C_Data);
	_delay_ms(100);

	I2C_Master_send_data(Copy_u8Data);
	_delay_ms(10);
	I2C_stop();
}

void LCD_I2C_SendFloat(f32 Copy_u8Fnum){
	// For checking if the number is negative or not
	u8 signindicate = (Copy_u8Fnum<0)? 1:0;

	if(signindicate){

		Copy_u8Fnum = Copy_u8Fnum*-1;
	}
	u8 LSB_Int=(u8)Copy_u8Fnum;
	u8 MSB_Int= (u8)(((s16)Copy_u8Fnum)>>8);

	u8 _Float=(u8) ((Copy_u8Fnum - (s32)Copy_u8Fnum) *100);


	long mantissa = *( long * ) & Copy_u8Fnum;
	// NOT SURE OF THE MASKING
	//mantissa = mantissa & 0x000007FFFFF;
	// Start the transmission
	I2C_send_start();
	I2C_select_slave(LCD_I2C_Slave_Address,0);
	_delay_ms(200);

	if(signindicate){
		// The number is -ve
		I2C_Master_send_data(LCD_I2C_SignedFloat);
	}
	else{
		// The number is +ve
		I2C_Master_send_data(LCD_I2C_UnsignedFloat);
	}

	_delay_ms(200);
	I2C_Master_send_data(LSB_Int);

	if (MSB_Int==0)
	{

	}
	else
	{
		_delay_ms(200);
		I2C_Master_send_data(MSB_Int);
	}
	_delay_ms(200);
	// Send the floating point
	I2C_Master_send_data('.');

	// Send the floating number
	_delay_ms(200);


	I2C_Master_send_data(_Float);


	_delay_ms(10);
	I2C_stop();
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
	I2C_select_slave(LCD_I2C_Slave_Address,0);
	_delay_ms(100);
	I2C_Master_send_data(LCD_I2C_CGRAMData);

	for(i = 0; i<8;i++){
		_delay_ms(100);
		I2C_Master_send_data(Copy_U8ptr[i]);
	}
	_delay_ms(10);
	I2C_stop();
}
