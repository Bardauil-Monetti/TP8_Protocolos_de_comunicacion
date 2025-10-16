#ifndef PROTOCOLO_SPI
#define PROTOCOLO_SPI
#include "stm32f103xb.h"
void spi_init(SPI_TypeDef* spi);
void spi_ss(SPI_TypeDef* spi); 
void spi_ds(SPI_TypeDef* spi);
char spi_rw_byte(SPI_TypeDef* spi, char c);
#endif