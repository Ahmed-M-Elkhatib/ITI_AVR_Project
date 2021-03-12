/*
 * LCDI2C_Interface.h
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */

#ifndef LCDI2C_MASTER_LCDI2C_INTERFACE_H_
#define LCDI2C_MASTER_LCDI2C_INTERFACE_H_

#define CLEAR_DISPLAY 0x01
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define DIPLAY_ON 0b00001110
#define DISPLAY_ORG 0x80



void LCDI2C_Init(void);
u8 LCDI2C_SendData(u8 data);
u8 LCDI2C_SendCommand(u8 cmd);
u8 LCDI2C_PrintString(char* string);
void LCDI2C_PrintInt(s32 num);
void LCDI2C_PrintFloat(f32 fnum, u8 precision);
void LCDI2C_SaveCustomChar(u8* arr,u8 CGramAddress);
void LCDI2C_SetCursorPosition(u8 x, u8 y);




#endif /* LCDI2C_MASTER_LCDI2C_INTERFACE_H_ */
