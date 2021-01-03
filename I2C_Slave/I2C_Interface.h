/*************Auther:Ahmed Elkhatib              */
/*************Date:29/11/2020                    */
/*************Version:1                          */
/*************Desc:                              */

#ifndef _I2C_interface_
#define _I2C_interface_
u8 I2C_send_start(void );
u8 I2C_select_slave(u8 Copy_slave_add,u8 Copy_W_R);
u8 I2C_Master_send_data(u8 Copy_data);
u8 I2C_Slave_recive_data(u8 *status);
void I2C_stop(void );
void I2C_slave_init();
void I2C_master_init();
#endif
