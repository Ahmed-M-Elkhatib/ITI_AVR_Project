#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "DIO_Interface.h"
#include"I2C_PRIVATE.h"
#include "I2C_config.h"
#include "avr/delay.h"
 u8 I2C_send_start(void )
 {
	 // start bit condition
	 TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	 while(GET_BIT(TWCR,TWINT)==0);  // wait the flag
	 if ((TWSR & 0xF8) != 0x08){return 0;}
	 else{return 1;}
 }
 u8 I2C_select_slave(u8 Copy_slave_add,u8 Copy_W_R)
 {u8 status=0;
	 if (Copy_W_R==0)         // write
	 {TWDR=(Copy_slave_add<<1);
	  TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	  while(GET_BIT(TWCR,TWINT)==0);  // wait the flag
	  if ((TWSR & 0xF8) != 18) {status= 0;}   // no ACK
	  else {status= 1;}
	 }
	 else if(Copy_W_R==1)   // read
	 {TWDR=(Copy_slave_add<<1)|1;
	 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	 while(GET_BIT(TWCR,7)==0);  // wait the flag
	 if ((TWSR & 0xF8) != 40) {status= 0;}   // no ACK
	 else {status= 1;}
	 }
	 return status;
 }

 u8 I2C_send_data(u8 Copy_data)
 {

	 TWDR =Copy_data;
	 TWCR=(1<<TWINT)|(1<<TWEN);
	 while (GET_BIT(TWCR,TWINT)==0);        // wait flag
	 if ((TWSR & 0xF8) != 28){return 0;}
	 else{return 1;}

 }

 u8 I2C_recive_data(u8 *status)
 {u8 Temp=0;
 	 TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)  ;
 	 //while ((TWSR&0xf8) != 0x60) ;   // status =received data
 	 while (GET_BIT(TWCR,TWINT)==0);  // wait flag
	 Temp=TWDR;
	 if ((TWSR & 0xF8) != 50){*status= 0;}
	 	 else{*status= 1;}
	 return Temp;

 }
void I2C_stop(void )
{
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	//while(!(TWCR&(1<<TWSTO)));  // wait till slop flag
}

void I2C_master_init(void )
{
	TWSR=(0<<TWPS0)|(0<<TWPS1);     //prescaler
	TWBR=32;		  // bit rate
	TWAR=10;       /// 0000 or 1111
	//TWCR=(1<<TWEN)|(1<<TWEA);
}


void I2C_slave_init(void )
{
	TWAR=5<<1;     /// 0000 or 1111   address
	TWCR=(1<<TWEN)|(1<<TWEA);
}

