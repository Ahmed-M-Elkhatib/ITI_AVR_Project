/*
 * I2C_main.c
 *
 *  Created on: Dec 28, 2020
 *      Author: khalil
 */
#include "STD_TYPES.h"
#include "DIO_Interface.h"
#include "I2C_Interface.h"
#include "LCD_interface.h"
#include "avr/delay.h"
#include "LCD_cofig.h"
#define Num   	1
#define Str   	2
#define command 3
u8 flag=0;
void Receive_2Byte(u8* Copy_char,u8* Copy_command);
void LCD_PORT_init(void);
void main (void)
{u8 byte1=0,byte2=0;
 u8 arr[20]={0};
 u8 i=0;
 	 LCD_PORT_init();
	I2C_slave_init();

while(1)
{
		Receive_2Byte(&byte1,&byte2);
		if (byte1==command){LCD_VidSendCommand(byte2);flag=0;}
		else if (byte1==Num){LCD_VidSendNum(byte2);flag=0;}
		else if(byte1==Str)
		{
			while(byte2!='\0')
			{
				arr[i]=byte2;i++;
				Receive_2Byte(&byte1,&byte2);
			}

		arr[i]='\0';i=0;flag=0;
		LCD_VidSendStr(arr);
		}

}
}

void Receive_2Byte(u8* Copy_byte1,u8* Copy_byte2)
{
	if (flag==0){*Copy_byte1=I2C_Slave_recive_data(NULL);};
	flag=1;
	*Copy_byte2= I2C_Slave_recive_data(NULL);
}
void LCD_PORT_init(void)
{
	DIO_VidSetPort_Direction(Data_Port,1);
	DIO_VidSetPin_Direction(Control_Port,RS,1);
	DIO_VidSetPin_Direction(Control_Port,RW,1);
	DIO_VidSetPin_Direction(Control_Port,E,1);
}
