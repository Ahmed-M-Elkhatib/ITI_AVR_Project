/*
 * TWI_Config.h
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */

#ifndef TWI_CONFIG_H_
#define TWI_CONFIG_H_


#ifndef FCPU
#define FCPU 8000000
#endif

#define SCL_FREQ   400000


#define ENABLE  1
#define DISABLE 0
#define YES 1
#define NO 0


/*  			CONFIGS					 */


#define TWI_Enable   				ENABLE
#define TWI_Interrupt_Enable		DISABLE

#define PRESCALER   				PS_1

#define TWI_ALWAYS_SLAVE			YES
#define TWI_OWN_SLAVE_ADDRESS		5

/*     OPtional Configs        */
#define TWI_TX_BUFFER_SIZE     5
#define TWI_RX_BUFFER_SIZE     5


/*    for testing purposes ONLY */
#define TWI_FORCE_BITRATE_VALUE  ENABLE
#define TWI_BITRATE_VALUE		32   // this is bit-rate value that
									// will be in TWBR register
									// its calculated manually and defined here


#endif /* I2C_CONFIG_H_ */
