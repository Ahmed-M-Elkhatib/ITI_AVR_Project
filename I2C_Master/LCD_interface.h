/*************Auther:Ahmed Elkhatib              */
/*************Date:30/11/2020                    */
/*************Version:1                          */
/*************Desc:                              */
#ifndef _LCD_interface_
#define _LCD_interface_

void LCD_VidInt(void);
void LCD_VidSendData(u8 Copy_u8Data);
void LCD_VidSendCommand(u8 Copy_u8Data);
void LCD_VidSendStr(u8* Copy_u8string);
void LCD_VidSendNum(u16 Copy_u16Num);
void LCD_VidShiftDispaly(u8 Copy_u8Line,u8 Copy_u8Column);
void LCD_VidCLR(void);
void LCD_SetCGRam(u8 Copy_u8location );  //start from 0:7
void LCD_SetDDRam(void);
void LCD_VidSendCharToCGRam(u8* Copy_u8Ptr);














#endif
