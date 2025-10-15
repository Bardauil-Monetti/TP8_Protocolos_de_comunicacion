#ifndef PROTOCOLO_I2C
#define PROTOCOLO_I2C
#include "stm32f103xb.h"

void i2c_init(I2C_TypeDef* i2c);
void i2c_start(I2C_TypeDef* i2c);
void i2c_stop(I2C_TypeDef* i2c);
void i2c_send_direccion(I2C_TypeDef* i2c, char dir);
void i2c_send_byte(I2C_TypeDef*, char b);
char i2c_recibir_byte_ack(I2C_TypeDef* i2c);
char i2c_recibir_byte_nack(I2C_TypeDef* i2c);

#endif