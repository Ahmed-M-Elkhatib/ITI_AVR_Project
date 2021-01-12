/*
 * LCD_I2C.h
 *
 *  Created on: Jan 3, 2021
 *      Author: Rana Yehya Mohamed
 */

#ifndef LCD_I2C_INTERFACE_H_
#define LCD_I2C_INTERFACE_H_


#define LCD_I2C_Slave_Address 5


#define LCD_COMMAND_CLEARDISP 							0x01
#define LCD_COMMAND_RETURN_HOME 						0x02
#define DDRAM_address 									0x80




void LCD_I2C_init();

void LCD_I2C_SendCommand(u8 );
void LCD_I2C_SendData	(u8 );


void LCD_I2C_SendString	(char* );
void LCD_I2C_SendNum	(s32 );
void LCD_I2C_SendFloat(f32 Copy_f32Fnum,u8 Copy_u8res);

void LCD_I2C_SetPosition(u8 ,u8);

void LCD_I2C_WriteInCGRAM(u8 *Copy_U8ptr,u8 Copy_u8location);


#endif /* LCD_I2C_INTERFACE_H_ */
