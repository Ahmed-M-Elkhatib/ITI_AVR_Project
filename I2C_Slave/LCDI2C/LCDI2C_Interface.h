/*
 * LCDI2C_Interface.h
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */

#ifndef LCDI2C_LCDI2C_INTERFACE_H_
#define LCDI2C_LCDI2C_INTERFACE_H_



//#define NUM   		0
#define STR   		4
#define CMD			5
#define DATA    	6
#define CGRAMData	7


void LCDI2C_Init(void);
void LCDI2C_Receive_2Byte( u8*byte1,u8*byte2);
void LCDI2C_Receive_String(u8*buffer);
void LCDI2C_Receive_CGram(u8*CGram_buffer, u8 CGram_address);

#endif /* LCDI2C_LCDI2C_INTERFACE_H_ */
