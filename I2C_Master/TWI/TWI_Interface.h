/*
 * TWI_Interface.h
 *
 *  Created on: Dec 28, 2020
 *      Author: mazen
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

#include "../LIB/STD_TYPES.h"


#define TWI_READ  1
#define TWI_WRITE 0


#define TWI_TX_FAIL      0
#define TWI_TX_SUCCESS   1
#define TWI_RX_FAIL      0
#define TWI_RX_SUCCESS   1


#define TWI_CLR_INT_FLAG()	TWCR = (1<<TWINT)|(1<<TWEN)
#define TWI_CLR_INT_FLAG_WITH_INT()	TWCR = (1<<TWIE)|(1<<TWINT)|(1<<TWEN)
#define TWI_START()			TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_START_WITH_INT()  TWCR = (1<<TWIE)|(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP()			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
#define TWI_STOP_WITH_INT()  TWCR = (1<<TWIE)|(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
#define TWI_ACK()			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA)
#define TWI_NACK()			CLR_BIT(TWCR,BIT(TWEA))
#define TWI_CheckFlag()		GET_BIT(TWCR,TWINT)

u8 TWI_u8GetStatus(void);
u8 TWI_u8CheckIfBusy(void);
void TWI_VidEnableInterrupt(void);
void TWI_VidDisableInterrupt(void);
void TWI_VidSetBitRate(u32 bit_rate);
void TWI_VidInit(void);
u8 TWI_SendSlaveAddress(u8 slave_addr, u8 rw);
u8 TWI_SendData(u8 data);
u8 TWI_ReadDataACK(void);
u8 TWI_ReadDataNACK(void);
u8 TWI_Start_TRX(void);
u8 TWI_RepeatedStart_TRX(void);
u8 TWI_Stop_TRX(void);
u8 TWI_SendLast(void);
u8 TWI_Master_TX(u8 data, u8 slave_addr);
u8 TWI_Master_RX(u8 slave_addr);

u8 TWI_Slave_TX(u8 data); /*  TODO */
u8 TWI_Slave_RX(u8 *data); /*  TODO */

/* buffered functions */
void TWI_SetSlaveAddress(u8 sla, u8 rw);
void TWI_Write(u8 data);  // puts data into tx buffer
u8 TWI_Read(void);	// gets data from rx buffer
void TWI_WriteString(u8* str,u8 str_size);
void TWI_ReadString(u8* str,u8 str_size);


/*  IMPORTANT NOTE:
 *******************
 * when we say " ACK has been returned " , we mean the ACK bit
 * or the ACK signal ,this ACK can be either:
 * - ACK=0 -> actual acknowlegment
 * - ACK=1 -> No acknowlegment
 *
 * ------ ON THE OTHER HAND ---------------
 * when we receive an ACK, we actually specify what we recieved
 * so we " an ACK has be received ", ACK here means an actual acknowledgement
 *  which means the ACK-bit = 0, and when
 * we say " a NOT ACK has been received ",
 * its obvious that the ACK-bit = 1
 * */

/*   NAMING CONVENTION:
 * ********************
 * - all conditions start with TWI_
 * - for master we use M~ prefix,
 * - for slave we use S~ prefix
 * - for Transmit we use ~TX suffix
 * - for Receive we use ~RX suffix
 *
 * 	>> EX: MTX -> Master Transmit
 * 		   SRX -> Slave Receive
 *  */



/*         MASTER TX_RX STATUS CODES        */
#define TWI_MTX_START				0x08 // A START condition has been transmitted
#define TWI_MTX_REP_START			0x10 // A repeated START condition has been transmitted
#define TWI_MTX_SLAW_ACK			0x18 // SLA+W has been transmitted; ACK has been received
#define TWI_MTX_SLAW_NACK			0x20 // SLA+W has been transmitted; NOT ACK has been received
#define TWI_MTX_SLAR_ACK			0x40 // SLA+R has been transmitted; ACK has been received
#define TWI_MTX_SLAR_NACK			0x48 // SLA+R has been transmitted; NOT ACK has been received
#define TWI_MTX_DATA_ACK			0x28 // Data byte has been transmitted;ACK has been received
#define TWI_MTX_DATA_NACK			0x30 // Data byte has been transmitted;NOT ACK has been received
#define TWI_MRX_DATA_ACK			0x50 // Data byte has been received; ACK has been returned
#define TWI_MRX_DATA_NACK			0x58 // Data byte has been received; NOT ACK has been returned


/*         SLAVE TX_RX STATUS CODES           */
#define TWI_SRX_SLAW_ACK			0x60  // Own SLA+W has been received; ACK has been returned
#define TWI_SRX_SLAR_ACK			0xA8  // Own SLA+R has been received;ACK has been returned
#define TWI_SRX_GENCALL_ACK			0x70  // General call address has been received; ACK has been returned
#define TWI_SRX_DATA_ACK			0x80  /* Previously addressed with own
											SLA+W; data has been received;
											ACK has been returned
											*/
#define TWI_SRX_DATA_NACK			0x88  /* Previously addressed with own
											SLA+W; data has been received;
											NOT ACK has been returned
											*/
#define TWI_SRX_GENCALLDATA_ACK		0x90 /* Previously addressed with
											general call; data has been received;
											ACK has been returned */
#define TWI_SRX_GENCALLDATA_NACK	0x98 /* Previously addressed with
											general call; data has been
											received; NOT ACK has been
											returned
											*/
#define TWI_SRX_STOP_COND			0xA0
#define TWI_SRX_REP_START			0xA0 /* A STOP condition or repeated
											START condition has been
											received while still addressed as
											slave
											*/											*/
#define TWI_STX_DATA_ACK			0xB8  // Data byte in TWDR has been transmitted; ACK has been received
#define TWI_STX_DATA_NACK			0xC0  // Data byte in TWDR has been transmitted; NOT ACK has been received


/******* WHAT DOES THIS MEAN ?? ************* */
#define TWI_STX_LAST_BYTE_ACK		0xC8  // Last data byte in TWDR has been transmitted (TWEA = “0”); ACK has been received
/***********************************************/



/*   Arbitration lost conditions   */
#define TWI_ARB_LOST				0x38 // Arbitration lost in SLA+R/W or data bytes

#define TWI_ARB_LOST_SLAW_ACK		0x68  /* Arbitration lost in SLA+R/W as master;
											 own SLA+W has been received;
											  ACK has been returned
											*/
#define TWI_ARB_LOST_SLAR_ACK		0xB0  /* Arbitration lost in SLA+R/W asmaster;
											own SLA+R has been received;
											ACK has been returned
											*/
#define TWI_ARB_LOST_GENCALL_ACK	0x78  /* Arbitration lost in SLA+R/W as master;
											General call address has been received;
											ACK has been returned
											*/
/* 				OTHER STATES			 */
#define BUS_ERROR					0x00
#define NO_INFO						0xF8



#endif /* TWI_INTERFACE_H_ */
