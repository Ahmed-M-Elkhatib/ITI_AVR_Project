/*
 * TWI_Register.h
 *
 *  Created on: Jul 18, 2020
 *      Author: mazen
 */

#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_


#define TWINT  		7
#define TWEA  		6
#define TWSTA		5
#define TWSTO		4
#define TWWC		3
#define TWEN 		2
////RESERVED////	1
#define TWIE		0




#define PS_1   0x00
#define PS_4   0x01
#define PS_16  0x02
#define PS_64  0x03


#define MASTER_TX_MODE	1
#define MASTER_RX_MODE	2
#define SLAVE_TX_MODE	3
#define SLAVE_RX_MODE	4




#define TWCR (*(volatile u8 *)(0x56))
#define TWDR (*(volatile u8 *)(0x23))
#define TWAR (*(volatile u8 *)(0x22))
#define TWSR (*(volatile u8 *)(0x21))
#define TWBR (*(volatile u8 *)(0x20))

#if TWI_Interrupt_Enable==ENABLE
void __vector_19(void) __attribute__((signal));
#endif

#endif /* TWI_REGISTER_H_ */
