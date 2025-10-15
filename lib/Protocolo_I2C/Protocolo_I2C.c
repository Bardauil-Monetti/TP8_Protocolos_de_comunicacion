#include "Protocolo_I2C.h"
#include "stm32f103xb.h"

void i2c_init(I2C_TypeDef* i2c){
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    i2c->CR1 |= I2C_CR1_PE;
    i2c->CR1 |= I2C_CR1_ACK;
    /*i2c->CR1 |= I2C_CR1_FREC;*/
    if(i2c == I2C1){
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        GPIOB->CRL &= ~(0xF << (6 * 4));
        GPIOB->CRL |= (0b1011 << (6 * 4));
        GPIOB->CRL &= ~(0xF << (7 * 4));
        GPIOB->CRL |= (0b1011 << (7 * 4));
    }else if(i2c == I2C2){
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        GPIOB->CRH &= ~(0xF << (6 * 4));
        GPIOB->CRH |= (0b1011 << (6 * 4));
        GPIOB->CRH &= ~(0xF << (7 * 4));
        GPIOB->CRH |= (0b1011 << (7 * 4));
    }
}

void i2c_start(I2C_TypeDef* i2c){
    i2c->CR1 |= I2C_CR1_START;
}

void i2c_stop(I2C_TypeDef* i2c){
    i2c->CR1 |= I2C_CR1_STOP;
}
void i2c_send_direccion(I2C_TypeDef* i2c, char dir){
    if(i2c->SR1 |= I2C_SR1_SB){
        i2c->DR = dir;
    }
    
}
void i2c_send_byte(I2C_TypeDef* i2c, char b){
    while(i2c->SR1 |= I2C_SR1_ADDR);
    
}
char i2c_recibir_byte_ack(I2C_TypeDef* i2c);
char i2c_recibir_byte_nack(I2C_TypeDef* i2c);