#ifndef _BIT_MATH_
#define _BIT_MATH_

#define SET_BIT( REG,PIN_NUM)              REG|=(1<<(PIN_NUM))
#define CLR_BIT( REG,PIN_NUM)              REG&=(~(1<<(PIN_NUM)))
#define TOGGLE_BIT( REG,PIN_NUM)           REG^=(1<<(PIN_NUM))
#define GET_BIT( REG,PIN_NUM)             ((REG>>(PIN_NUM))&1)
#define SET_PORT(REG)						REG=0XFF	
#define CLR_PORT(REG)						REG=0X00
#define WRITEON_PORT(REG,VALUE)				REG=VALUE
#endif
