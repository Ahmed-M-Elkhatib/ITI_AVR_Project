#ifndef _I2C_PRIVATE_
#define _I2C_PRIVATE_

#define TWBR  *((volatile u8*) 0x20)
#define TWCR  *((volatile u8*) 0x56)
#define TWSR  *((volatile u8*) 0x21)
#define TWDR  *((volatile u8*) 0x23)
#define TWAR  *((volatile u8*) 0x22)
#define TWINT    7  // TWCR
#define TWEA     6
#define TWSTA    5
#define TWSTO    4
#define TWWC     3
#define TWEN     2
#define TWIE     0

#define TWPS1    1
#define TWPS0    0







#endif
