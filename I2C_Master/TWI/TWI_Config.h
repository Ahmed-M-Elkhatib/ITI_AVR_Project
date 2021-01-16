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



/*  			CONFIGS					 */


#define TWI_Enable   				ENABLE
#define TWI_Interrupt_Enable		ENABLE

#define PRESCALER   				PS_1

#define TWI_OWN_SLAVE_ADDRESS		15

/*     OPtional Configs        */
#define TWI_TX_BUFFER_SIZE     5
#define TWI_RX_BUFFER_SIZE     5



#endif /* I2C_CONFIG_H_ */
