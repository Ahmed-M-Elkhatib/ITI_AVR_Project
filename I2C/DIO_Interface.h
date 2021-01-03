/*************Auther:Ahmed Elkhatib              */
/*************Date:29/11/2020                    */
/*************Version:1                          */
/*************Desc:                              */

#ifndef _DIO_interface_
#define _DIO_interface_

#define DIO_PORTA   0
#define DIO_PORTB   1
#define DIO_PORTC   2
#define DIO_PORTD   3

#define DIO_High    1
#define DIO_Low     0



#define DIO_OUTPUT 1
#define DIO_INPUT   0



#define DIO_PIN0   0
#define DIO_PIN1   1
#define DIO_PIN2   2
#define DIO_PIN3   3
#define DIO_PIN4   4
#define DIO_PIN5   5
#define DIO_PIN6   6
#define DIO_PIN7   7

void DIO_VidSetPin_Direction(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8State);
void DIO_VidSetPin_Value(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Value);
u8 DIO_VidGetPin(u8 Copy_u8Port,u8 Copy_u8Pin);
void DIO_VidToggelPin(u8 Copy_u8Port,u8 Copy_u8Pin);
void DIO_VidSetPort_Direction(u8 Copy_u8Port,u8 Copy_u8State);
void DIO_VidWriteOnPort(u8 Copy_u8Port,u8 Copy_u8Value);
void DIO_VidPullUp_Pin(u8 Copy_u8Port,u8 Copy_u8Pin);
void DIO_VidPullDown_Pin(u8 Copy_u8Port,u8 Copy_u8Pin);
void DIO_VidSetPort_Value(u8 Copy_u8Port,u8 Copy_u8Value);

#endif
