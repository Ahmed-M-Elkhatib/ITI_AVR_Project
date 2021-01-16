/*
 * TWI_prog.c
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MAN.h"
#include "../DIO/DIO_Interface.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"
#include "TWI_Register.h"
#include "queue_buffer.h"

u8 lastTransOK = 0 ;

//static u8 TWI_status=0 ;
static Bool TWI_Busy = false;
static u8 TWI_TargetSlaveAddress;

#if TWI_Interrupt_Enable==ENABLE
static u8 TWI_TX_Buffer[TWI_TX_BUFFER_SIZE];
static u8 TWI_RX_Buffer[TWI_RX_BUFFER_SIZE];
queue_type tx_buf;
queue_type rx_buf;

#endif

u8 TWI_u8GetStatus(void)
{
	return (TWSR&0xF8) ;
}

u8 TWI_u8CheckIfBusy(void)
{
	return TWI_Busy ;
}

void TWI_VidEnableInterrupt(void)
{
	SET_BIT(TWCR,BIT(TWEN)|BIT(TWINT));
}

void TWI_VidDisableInterrupt(void)
{
	CLR_BIT(TWCR,BIT(TWINT));
}




void TWI_VidSetBitRate(u32 bit_rate)
{
	u32 TWBR_VAL = 0 ;

	u32 DIV = FCPU/bit_rate ;

	TWBR_VAL = (DIV - 16)>>( (2*PRESCALER) +1 ) ;

	if(TWBR_VAL<10)
	{
		TWBR = 10;
	}
	else
	{
		TWBR = (u8)TWBR_VAL;
	}
#if TWI_FORCE_BITRATE_VALUE==ENABLE
	TWBR = TWI_BITRATE_VALUE;
#endif


}




void TWI_VidInit(void)
{

	/*  Enable of I2C Interrupt */

#if TWI_Interrupt_Enable == ENABLE
	SET_BIT(TWCR,TWIE );
	// initialize FIFO buffers
	queue_Init(&tx_buf,TWI_TX_BUFFER_SIZE,TWI_TX_Buffer);
	queue_Init(&rx_buf,TWI_RX_BUFFER_SIZE,TWI_RX_Buffer);

#elif TWI_Interrupt_Enable == DISABLE
	CLR_BIT(TWCR,TWIE);
#endif
	/* set bit rate */

	TWI_VidSetBitRate(SCL_FREQ);

	/* Enable of I2C */

	TWAR = (TWI_OWN_SLAVE_ADDRESS<<1);



#if TWI_Enable == ENABLE
	#if TWI_ALWAYS_SLAVE==YES
		TWI_ACK();
	#else
		TWI_CLR_INT_FLAG();
	#endif
//	SET_BIT(TWCR , TWEN);

#elif TWI_Enable == DISABLE
	CLR_BIT(TWCR , TWEN);

#endif


	///TWDR = 0xFF ; //default value on bus (bec 1 is the recessive bit)

}

u8 TWI_SendSlaveAddress(u8 slave_addr, u8 rw)
{
	u8 status = 0;

	TWDR = (slave_addr<<1) | rw ; // OR with 0x00 for Write operation

	/* as soon as the flag is cleared transmission begins */
	TWI_CLR_INT_FLAG();
	CLR_BIT(TWCR,BIT(TWSTA));

	//4. wait for flag to set
	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for slave address to be sent */}
	status = TWI_u8GetStatus();
	return status ;
}

u8 TWI_SendData(u8 data)
{
	u8 status = 0;
	/*load data in TWDR */
	TWDR = data ;
	TWI_CLR_INT_FLAG();
	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for data to be transmitted */}
	status = TWI_u8GetStatus();
	return status ;
}

u8 TWI_ReadDataACK(void)
{
	//	TWI_CLR_INT_FLAG();
	TWI_ACK();
	/*wait for flag */
	//	while(TWI_CheckFlag() == 0)
	while (!(TWCR & (1 << TWINT)))
	{/*wait for data to be recieved */}

	/*read data from TWDR */
	return TWDR ;
}

u8 TWI_ReadDataNACK(void)
{
	TWI_CLR_INT_FLAG();
	TWI_NACK();
	/*wait for flag */
	//	while(TWI_CheckFlag() == 0)
	while (!(TWCR & (1 << TWINT)))
	{/*wait for data to be recieved */}

	/*read data from TWDR */
	return TWDR ;
}

u8 TWI_Start_TRX(void)
{
	u8 status = 0;
	//send a start condition signal
	TWI_START();

	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for start condition */}
	status = TWI_u8GetStatus();
	return status ;

}

u8 TWI_RepeatedStart_TRX(void)
{
	u8 status = 0;
	//send a start condition signal
	TWI_START();

	/*wait for flag */
	while(TWI_CheckFlag() == 0)
	{/*wait for start condition */}
	status = TWI_u8GetStatus();
	return status ;
}


u8 TWI_Stop_TRX(void)
{
	u8 status = 0;
	TWI_STOP();
	status = TWI_u8GetStatus();
	return status ;
}

u8 TWI_SendLast(void)
{
	u8 status = 0;

	// if there was a problem sending the last
	// byte of data:
	//send a start condition signal
	TWI_START();

	while(TWI_CheckFlag() == 0)
	{/*wait for flag */}

	status = TWI_u8GetStatus();
	return status ;
}


u8 TWI_Master_TX(u8 data, u8 slave_addr)
{
	u8 status = 0 ;

	// 1. start condition
	status = TWI_Start_TRX();
	// 2. wait for flag to set (this happens inside TWI_Start_TRX() )
	// 3. check TWSR, load SLA+W in TWDR , Send SLA+W
	if(status != TWI_MTX_START){ return TWI_TX_FAIL; }

	status = TWI_SendSlaveAddress(slave_addr, TWI_WRITE); // rw = 1 -> write operation
	//4. wait for flag to set (this happens inside TWI_SlaveAddr() )
	//5. check TWSR, load data in TWDR, send data
	if(status != TWI_MTX_SLAW_ACK){ return TWI_TX_FAIL; }

	status = TWI_SendData(data);
	//6.wait for flag to set (this happens inside TWI_SendData() )
	//7. check TWSR , send STOP cond
	if(status != TWI_MTX_DATA_ACK){ return TWI_TX_FAIL; }

	TWI_Stop_TRX();

	lastTransOK = 1 ;
	return TWI_TX_SUCCESS;



}
u8 TWI_Master_RX(u8 slave_addr)
{
	u8 status = 0 ;
	u8 rx = 0 ;
	// 1. start condition
	status = TWI_Start_TRX();
	// 2. wait for flag to set (this happens inside TWI_Start_TRX() )
	// 3. check TWSR, load SLA+R in TWDR , Send SLA+R
	if(status != TWI_MTX_START){ return TWI_TX_FAIL; }

	status = TWI_SendSlaveAddress(slave_addr, TWI_READ); // rw = 0 -> read operation
	//4. wait for flag to set (this happens inside TWI_SlaveAddr() )
	//5. check TWSR, read data in TWDR, send ACK to slave
	if(status != TWI_MTX_SLAR_ACK){ return TWI_TX_FAIL; }

	rx = TWI_ReadDataACK();
	status = TWSR ;
	//6.wait for flag to set (this happens inside TWI_SendData() )
	//7. check TWSR , send STOP cond
	if(status != TWI_MRX_DATA_ACK){ return TWI_TX_FAIL; }

	TWI_STOP();


	return rx;
}

u8 TWI_Slave_Listen(void)
{
	while(1)
	{
		u8 status;							/* Declare variable */
		while (!(TWCR & (1<<TWINT)))
		{/* Wait to be addressed */}

		status = TWI_u8GetStatus();					/* Read TWI status register with masking lower three bits */
		if (status == TWI_SRX_SLAW_ACK || status == TWI_ARB_LOST_SLAW_ACK)
		{
			/* Check weather own SLA+W received & ack returned (TWEA = 1) */
			return 0;
		}
											/* If yes then return 0 to indicate ack returned */
		if (status == TWI_SRX_SLAR_ACK || status == TWI_ARB_LOST_SLAR_ACK)
		{
			/* Check weather own SLA+R received & ack returned (TWEA = 1) */
			return 1;
		}
											/* If yes then return 1 to indicate ack returned */
		if (status == TWI_SRX_GENCALL_ACK || status == TWI_ARB_LOST_GENCALL_ACK)
		{
			/* Check weather general call received & ack returned (TWEA = 1) */
			return 2;
		}
											/* If yes then return 2 to indicate ack returned */
		else
		{
			continue;
		}

	}
	return 0;
}

u8 TWI_Slave_TX(u8 data)
{
	u8 status;
	TWDR = data;								/* Write data to TWDR to be transmitted */
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);		/* Enable TWI and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)))
	{
		/* Wait until TWI finish its current
	 	 job (Write operation) */
	}

	status = TWI_u8GetStatus();						/* Read TWI status register with masking lower three bits */
	if (status == TWI_SRX_STOP_COND)							/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return -1 */
		return 5;
	}
	if (status == TWI_STX_DATA_ACK)							/* Check weather data transmitted & ack received */
	{
		return 0;
	}									/* If yes then return 0 */
	if (status == TWI_STX_DATA_NACK)							/* Check weather data transmitted & nack received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return -2 */
		return 6;
	}
	if (status == TWI_STX_LAST_BYTE_ACK)							/* If last data byte transmitted with ack received TWEA = 0 */
	{
		return 7;
	}									/* If yes then return -3 */
	else
	{
		return 8;
	}
}

u8 TWI_Slave_RX(u8 *data)
{
	u8 status;								/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);		/* Enable TWI, generation of ack and clear interrupt flag */
	while (!(TWCR & (1<<TWINT)))
	{
		/* Wait until TWI finish
		 * its current job (read operation) */
	}
	status = TWI_u8GetStatus();						/* Read TWI status register with masking lower three bits */
	if (status == TWI_SRX_DATA_ACK || status == TWI_SRX_GENCALLDATA_ACK)
	{
		/* Check weather data received & ack returned (TWEA = 1) */
		*data=TWDR;
		return 0;
	}
										/* If yes then return received data */
	if (status == TWI_SRX_DATA_NACK || status == TWI_SRX_GENCALLDATA_NACK)
	{
		/* Check weather data received, nack returned and switched to not addressed slave mode */
		*data=TWDR;
		return 0;
	}
										/* If yes then return received data */
	if (status == TWI_SRX_STOP_COND)							/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);						/* If yes then clear interrupt flag & return 0 */
		return 5;
	}
	else
	{
		return 6;
	}

}




void TWI_SetSlaveAddress(u8 sla, u8 rw)
{
	TWI_TargetSlaveAddress = (sla<<1)| rw;
}




#if TWI_Interrupt_Enable==ENABLE
void __vector_19(void)
{

	TWI_status = TWI_u8GetStatus();
	switch(TWI_status);
	{
	case  TWI_MTX_START:  // start condition transmitted
	case  TWI_MTX_REP_START:
		TWI_Busy = true;  // communication started so we are busy
		// send slave address;
		TWDR = TWI_TargetSlaveAddress;
		// clear flag
		TWI_CLR_INT_FLAG_WITH_INT();
		break;
	case  TWI_MTX_SLAW_ACK	: // master wants to write to slave, slave ACKed
		TWDR = queue_Pop(&tx_buf); // pop front element from buffer
		// clear flag
		TWI_CLR_INT_FLAG_WITH_INT();
		break;
	case  TWI_MTX_SLAW_NACK	:	break;
	case  TWI_MTX_SLAR_ACK	:	break;
	case  TWI_MTX_SLAR_NACK	:	break;
	case  TWI_MTX_DATA_ACK	:	break;
	case  TWI_MTX_DATA_NACK	:	break;
	case  TWI_MRX_DATA_ACK	:	break;
	case  TWI_MRX_DATA_NACK	:	break;

	case  TWI_SRX_SLAW_ACK	:	break;
	case  TWI_SRX_SLAR_ACK	:	break;
	case  TWI_SRX_GENCALL_ACK:	break;
	case  TWI_SRX_DATA_ACK	:	break;
	case  TWI_SRX_DATA_NACK	:	break;
	case  TWI_SRX_GENCALLDATA_ACK:	break;
	case  TWI_SRX_GENCALLDATA_NACK	:	break;
	case  TWI_SRX_STOP_COND	:	break;
	case  TWI_STX_DATA_ACK	:	break;
	case  TWI_STX_DATA_NACK	:	break;


	case  TWI_ARB_LOST	:	break;

	case  TWI_ARB_LOST_SLAW_ACK	:	break;
	case  TWI_ARB_LOST_SLAR_ACK	:	break;
	case  TWI_ARB_LOST_GENCALL_ACK	:	break;
	case  BUS_ERROR	:	break;
	case  NO_INFO	:	break;


	}

}
#endif
