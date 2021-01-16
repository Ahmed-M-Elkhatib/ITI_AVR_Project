/*
 * LCDI2C_prog.c
 *
 *  Created on: Jan 16, 2021
 *      Author: mazen
 */
#include "../LIB/STD_TYPES.h"
#include "../TWI/TWI_Interface.h"
#include "../LCD/LCD_Interface.h"


#include "LCDI2C_Interface.h"
#include "LCDI2C_Config.h"

void LCDI2C_Init(void)
{
	LCD_VidInt(); 		// intialize LCD with a default configuration
					 	   // because the user can send a configuration or not
					      // so some default configuration must be guranteed
		                 // if the user wants to change it , he simply can by sending
					    // any configuration commands
	I2C_slave_init();
}

void LCDI2C_Receive_2Byte( u8*byte1,u8*byte2)
{

}

void LCDI2C_Receive_String(char*buffer)
{

}

void LCDI2C_Receive_CGram(u8*CGram_buffer)
{

}
