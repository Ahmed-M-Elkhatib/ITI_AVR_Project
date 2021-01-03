/*
 * LCD_I2C.h
 *
 *  Created on: Jan 3, 2021
 *      Author: USER
 */

#ifndef LCD_I2C_INTERFACE_H_
#define LCD_I2C_INTERFACE_H_
void LCD_I2C_init						(u8 *,u8 );

void LCD_I2C_SendCommand		(u8 );
void LCD_I2C_SendData				(u8 );


void LCD_I2C_SendString			(u8* );
void LCD_I2C_SendNum				(s16 );
void LCD_I2C_SendFloat				(f32 );

void LCD_I2C_SetPosition			(u8 ,u8);


void LCD_I2C_SetCGRAMAdress	(u8 );
void LCD_I2C_WriteInCGRAM		(u8 *);

#endif /* LCD_I2C_INTERFACE_H_ */
