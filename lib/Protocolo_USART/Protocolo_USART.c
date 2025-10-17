#include <Protocolo_USART.h>
#include <stm32f103xb.h>
void usart_init(USART_TypeDef* usart, int baudrate){
    usart->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; //Habilitación del periferico, el TX y el RX
    usart->CR1 &= ~(USART_CR1_M); //Longitud de datos de 8 bits
    usart->CR1 |= USART_CR1_PCE | ~(USART_CR1_PS); //Habilitación de control de paridad par
    usart->CR2 &= ~USART_CR2_STOP; //un bit de parada
    RCC->APB2ENR|=RCC_APB2ENR_IOPAEN; 
    if(usart == USART1){ 
        // UART1: APB2 (72MHz) - TX = PA9, RX = PA10
        RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
        GPIOA->CRH &= ~(0XF << (9 *4));
        GPIOA->CRH |= (0xA << (9 *4)); //1010 es para Función alternativa Push-Pull.
        GPIOA->CRH &= ~(0XF << (10 *4));
        GPIOA->CRH |= (0x4 << (10 *4)); //Floating input
    }else if(usart == USART2){
        // UART2: APB1 (36MHz) - TX = PA2, RX = PA3
        RCC->APB2ENR|=RCC_APB1ENR_USART2EN;
        GPIOA->CRL &= ~(0XF << (2 * 4));
        GPIOA->CRL |= (0xA << (2 * 4)); //1010 es para Función alternativa Push-Pull.
        GPIOA->CRL &= ~(0XF << (3 * 4));
        GPIOA->CRL |= (0x4 << (3 * 4)); //Floating input
    }else if(usart == USART3){
        // UART3: APB1 (36MHz) - TX = PB10, RX = PB11
        RCC->APB2ENR|=RCC_APB1ENR_USART3EN;
        GPIOA->CRH &= ~(0XF << (10 * 4));
        GPIOA->CRH |= (0xA << (10 * 4)); //1010 es para Función alternativa Push-Pull.
        GPIOA->CRH &= ~(0XF << (11 * 4));
        GPIOA->CRH |= (0x4 << (11 * 4)); //Floating input
    }
    float divisor = (float)pclk_freq / (16.0f * (float)baudrate);
    uint16_t mantissa = (uint16_t)divisor; // Parte entera
    uint16_t fraction = (uint16_t)((divisor - (float)mantissa) * 16.0f); // Parte con coma
    USARTx->BRR = (mantissa << 4) | (fraction & 0x0F);
}

void usart_send_char(USART_TypeDef* usart, char c){
    while (!(USART1->SR & USART_SR_TXE)); //esperar mientras el DR no este listo para admitir un nuevo char
    usart->DR = c;
}

void usart_send_string(USART_TypeDef* usart, char*str){
    while(*str){//mientras haya caracteres en la direccion de la memoria de str
        while (!(usart->SR & USART_SR_TXE)); //esperar mientras el DR no este listo para admitir un nuevo char del string
        usart->DR = *str++; //recorre el puntero
    }
}

char usart_recibir_char(USART_TypeDef* usart){
    while(!(usart->SR & USART_SR_RXNE)); //esperar mientras no haya nada nuevo para leer en el DR
    return usart->DR; //lo leo y retorno eso
}
