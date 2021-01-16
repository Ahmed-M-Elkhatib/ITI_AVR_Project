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
	LCD_VidInit(); 		// intialize LCD with a default configuration
					 	   // because the user can send a configuration or not
					      // so some default configuration must be guranteed
		                 // if the user wants to change it , he simply can by sending
					    // any configuration commands
	TWI_VidInit();
}

void LCDI2C_Receive_2Byte( u8*byte1,u8*byte2)
{
	u8 TwoBytes[2]={0};
	u8 iDx=0;
	u8 status = 0;
	while(1)
	{
		if(TWI_Slave_Listen()==0) /* SLA+W */
		{
			do
			{
				status = TWI_Slave_RX(&TwoBytes[iDx]);
				iDx=(iDx+1)%2;  /* if no stop condition recieved after two bytes
				 	 	 	 	 it will alternate between 0 & 1 */
			}while(status!= 5); /* a stop condition or a represted start */
			break; /* break from while(1) ONLY if
			 	 	 SLA+W is True, which means slave waiting to recieve */
		}
	}
	*byte1=TwoBytes[0];
	*byte2=TwoBytes[1];
}

void LCDI2C_Receive_String(u8*buffer)
{
	u8 iDx=0;
	u8 status = 0;
	while(1)
	{
		if(TWI_Slave_Listen()==0) /* SLA+W */
		{
			do
			{
				status = TWI_Slave_RX(&buffer[iDx]);
				iDx++;  /* if no stop condition recieved after two bytes */
			}while((status!= 5) || (iDx>SLAVE_BUFFER_SIZE-1)); /* a stop condition or a represted start */
			buffer[iDx]='\0';
			break; /* break from while(1) ONLY if
				 	 	 SLA+W is True, which means slave waiting to recieve */
		}
	}

}

void LCDI2C_Receive_CGram(u8*CGram_buffer, u8 CGram_address)
{
	u8 iDx=0;
	u8 status = 0;
	while(1)
	{
		if(TWI_Slave_Listen()==0) /* SLA+W */
		{
			do
			{
				status = TWI_Slave_RX(&CGram_buffer[iDx]);
				iDx=(iDx+1)%CGRAM_BUFFER_SIZE;  /* if no stop condition recieved after two bytes */
			}while(status!= 5); /* a stop condition or a represted start */
			break; /* break from while(1) ONLY if
					 	 	 SLA+W is True, which means slave waiting to recieve */
		}
	}
	LCD_VidSaveCustomChar(CGram_buffer,CGram_address);
}
