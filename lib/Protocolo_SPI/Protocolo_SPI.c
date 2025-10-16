#include "Protocolo_SPI.h"
#include "stm32f103xb.h"

void spi_init(SPI_TypeDef* spi){
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // hay que habilitarlo para que los pines puedan conectar con el periferico
    spi->CR1 |= SPI_CR1_SPE | SPI_CR1_MSTR | SPI_CR1_SSM; // habilito el periferico en modo maestro, y hago que el estado del esclavo sea manejado por SSI
    spi->CR1 |= SPI_CR1_CPOL | SPI_CR1_CPHA; // estado alto cuando este en reposo
    spi->CR1 &= ~SPI_CR1_BR; // Limpia los bits BR
    spi->CR1 |= (0b010 << 3); // BR[0]
    if(spi == SPI1){
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        for(int i = 4; i < 8; i++){
            GPIOA->CRL &= ~(0xF << (i * 4));
        }
        GPIOA->CRL |= (0b0010 << (4 * 4)); // SS
        GPIOA->CRL |= (0b1010 << (5 * 4)); // SCK
        GPIOA->CRL |= (0b0100 << (6 * 4)); // MOSI
        GPIOA->CRL |= (0b1010 << (7 * 4)); // MISO
    }else{
        RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; 
        for(int i = 12; i < 16; i++){
            GPIOA->CRL &= ~(0xF << (i * 4));
        }
        GPIOA->CRL |= (0b0010 << (12 * 4)); // SS
        GPIOA->CRL |= (0b1010 << (13 * 4)); // SCK
        GPIOA->CRL |= (0b0100 << (14 * 4)); // MOSI
        GPIOA->CRL |= (0b1010 << (15 * 4)); // MISO
        
    }
}
void spi_ss(SPI_TypeDef* spi){
    spi->CR1 &= ~(SPI_CR1_SSI); //cuando esta en 0, SS
} 
void spi_ds(SPI_TypeDef* spi){
    spi->CR1 |= SPI_CR1_SSI; //cuando esta en 1, DS
} 
char spi_rw_byte(SPI_TypeDef* spi, char c){
    while(!(spi->SR & SPI_SR_TXE)); // espero mientras es DR no este listo para transmitir
    spi->DR = c; // transmito byte
    while(!(spi->SR & SPI_SR_RXNE)); // espero miertras no haya nada para leer
    return spi->DR; // leo y retorno esa lectura
}
