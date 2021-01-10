/*
 * LCDI2C_slave.h
 *
 *  Created on: Jan 10, 2021
 *      Author: mazen
 */

#ifndef LCDI2C_SLAVE_H_
#define LCDI2C_SLAVE_H_


#define SLAVE_BUFFER_SIZE 40


void Receive_2Byte(u8* Copy_char,u8* Copy_command);
void Receive_String(u8* buffer);


#endif /* LCDI2C_SLAVE_H_ */
