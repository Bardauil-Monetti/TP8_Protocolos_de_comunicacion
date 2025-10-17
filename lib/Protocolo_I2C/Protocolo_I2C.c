#include "Protocolo_I2C.h"
#include "stm32f103xb.h"
#include "stdbool.h"
void i2c_init(I2C_TypeDef* i2c){
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; 
    i2c->CR1 |= I2C_CR1_PE; //habilito periferico
    i2c->CR2 |= ~(I2C_CR2_FREQ) | (36); // limpio el clk del periferico y seteo la velocidad en 36MHz
    I2C1->CCR = 180; // calculado para valores estandar (revisar)
    I2C1->TRISE = 37;
    if(i2c == I2C1){
        //PB6 = TX, PB7 = RX para I2C1
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
        // Ambos estan configurados en salida de Función Alternativa Open-Drain
        GPIOB->CRL &= ~(0xF << (6 * 4));
        GPIOB->CRL |= (0b1011 << (6 * 4));
        GPIOB->CRL &= ~(0xF << (7 * 4));
        GPIOB->CRL |= (0b1011 << (7 * 4));
    }else if(i2c == I2C2){
        //PB10 = TX, PB11 = RX para I2C2
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
        // Ambos estan configurados en salida de Función Alternativa Open-Drain
        GPIOB->CRH &= ~(0xF << ((6%8) * 4));
        GPIOB->CRH |= (0b1011 << ((6%8) * 4));
        GPIOB->CRH &= ~(0xF << ((7%8) * 4));
        GPIOB->CRH |= (0b1011 << ((7%8) * 4));
    }
}

void i2c_start(I2C_TypeDef* i2c){
    i2c->CR1 |= I2C_CR1_START; // Genero condición de START
    while(!(i2c->SR1 & I2C_SR1_SB)); // Espero para confirmar el envio de la condición de START
}

void i2c_stop(I2C_TypeDef* i2c){
    while(!(I2C_SR1_BTF)); // espero hasta que el ultimo byte sea transferido
    i2c->CR1 |= I2C_CR1_STOP;
}
void i2c_send_direccion(I2C_TypeDef* i2c, char dir){
    if(i2c->SR1 & I2C_SR1_SB){ // Si se generó una condición de START
        i2c->DR = dir; // se manda la dirección
    }
    while(!(i2c->SR1 &= I2C_SR1_ADDR)); // Espero hasta que la dirección de esclavo sea reconocida
    i2c->SR2; // leo sr2 
}
void i2c_send_byte(I2C_TypeDef* i2c, char b){
    // logica parecida a la anterior
    while(!(i2c->SR1 & I2C_SR1_TXE));
    i2c->DR = b;
}

char i2c_recibir_byte_ack(I2C_TypeDef* i2c){
    i2c->CR1 |= I2C_CR1_ACK; // habilito el mandar un ACK
    while(!(i2c->SR1 & I2C_SR1_RXNE)); // si hay algo nuevo para leer
    return i2c->DR; // lo hago, y retorno eso
}

char i2c_recibir_byte_nack(I2C_TypeDef* i2c){
    i2c->CR1 &= ~(I2C_CR1_ACK); // lo mismo que lo anterior, pero negado para NACK
    while(!(i2c->SR1 & I2C_SR1_RXNE));
    return i2c->DR;;
}
