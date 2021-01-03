
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include <avr/delay.h>
#include"DIO_Interface.h"
#include"LCD_interface.h"
#include "LCD_cofig.h"

void LCD_VidSendData(u8 Copy_u8Data)
{
	DIO_VidSetPin_Value(Control_Port,RS,1);   //rs=1   data
	DIO_VidSetPin_Value(Control_Port,RW,0);		//rw=0 write
	DIO_VidWriteOnPort(Data_Port,Copy_u8Data);
	DIO_VidSetPin_Value(Control_Port,E,1);
	_delay_ms(10);
	DIO_VidSetPin_Value(Control_Port,E,0);
	_delay_ms(10);
	
}
void LCD_VidSendCommand(u8 Copy_u8Data)
{
	DIO_VidSetPin_Value(Control_Port,RS,0);   //rs=0   data
	DIO_VidSetPin_Value(Control_Port,RW,0);		//rw=0 write
	DIO_VidWriteOnPort(Data_Port,Copy_u8Data);
	DIO_VidSetPin_Value(Control_Port,E,1);
	_delay_ms(10);
	DIO_VidSetPin_Value(Control_Port,E,0);
	_delay_ms(10);
	
}
void LCD_VidInt(void)
{	
	DIO_VidSetPort_Direction(Data_Port,1);
	DIO_VidSetPin_Direction(Control_Port,RS,1);
	DIO_VidSetPin_Direction(Control_Port,RW,1);
	DIO_VidSetPin_Direction(Control_Port,E,1);
		_delay_ms(40);
	LCD_VidSendCommand(0b00111000);
		_delay_ms(1);
	LCD_VidSendCommand(0b00001100);
		_delay_ms(1);
	LCD_VidSendCommand(0b00000001);
		_delay_ms(1);

}
void LCD_VidSendStr(u8* Copy_u8string)
{
	

	DIO_VidSetPin_Value(Control_Port,RS,1);   //rs=1   data
	DIO_VidSetPin_Value(Control_Port,RW,0);		//rw=0 write
	while(*Copy_u8string!='\0')
	{

	DIO_VidWriteOnPort(Data_Port,*Copy_u8string);
	DIO_VidSetPin_Value(Control_Port,E,1);
	_delay_ms(10);
	DIO_VidSetPin_Value(Control_Port,E,0);
	_delay_ms(10);
	Copy_u8string++;
	}
}
void LCD_VidSendNum(u16 Copy_u16Num)
{	u16 rev=0;
	u8 zeros=0;
	if (Copy_u16Num!=0)
	{
	while(Copy_u16Num>0)
		{
		 rev=(rev*10)+(Copy_u16Num % 10);
		Copy_u16Num/=10;
		zeros++;
		};
	while(rev!=0)
	{
	u8 rem=rev%10;
	rev/=10;
	LCD_VidSendData((48+rem));//+48 to have aski code
	zeros--;
	}
	while(zeros>0)
	{
	LCD_VidSendData((48+0));
	zeros--;
	}
	}
	else
	{

		LCD_VidSendData((48+0));
	}
}

void LCD_VidShiftDispaly(u8 Copy_u8Line,u8 Copy_u8Column)
{u8 shift=0,offset=0;
	switch(Copy_u8Line)
	{case 1:
		offset=128;
	break;
	case 2:
		offset=128+64;
	}
	shift=offset+Copy_u8Column;
	LCD_VidSendCommand(shift);
}


void LCD_VidCLR(void)
{

	LCD_VidSendCommand(0b00000001);

}

void LCD_SetCGRam(u8 Copy_u8location )  //start from 0:7
{	u8 offset=64+Copy_u8location;

	LCD_VidSendCommand(offset);

}

void LCD_SetDDRam(void)
{	u8 offset=128;

	LCD_VidSendCommand(offset);

}


void LCD_VidSendCharToCGRam(u8* Copy_u8Ptr)
{
	for(int i=0;i<8;i++)
	{
		LCD_VidSendData(*Copy_u8Ptr);
		Copy_u8Ptr++;
	}


}



