#include <Protocolo_USART.h>
#include <stm32f103xb.h>
void usart_init(USART_TypeDef* usart, int baudrate){
    usart->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE; 
    usart->CR1 &= ~(USART_CR1_M); 
    usart->CR1 |= USART_CR1_PCE | ~(USART_CR1_PS);
    usart->CR2 &= ~USART_CR2_STOP;
    if(usart == USART1){
        RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
        GPIOA->CRH &= ~(0XF << (9 *4));
        GPIOA->CRH |= (0xA << (9 *4));
        GPIOA->CRH &= ~(0XF << (10 *4));
        GPIOA->CRH |= (0x4 << (10 *4));
        USART1->BRR = (16 * baudrate) / 72000000;
    }else if(usart == USART2){
        RCC->APB2ENR|=RCC_APB1ENR_USART2EN;
        GPIOA->CRL &= ~(0XF << (2 * 4));
        GPIOA->CRL |= (0xA << (2 * 4));
        GPIOA->CRL &= ~(0XF << (3 * 4));
        GPIOA->CRL |= (0x4 << (3 * 4));
        USART2->BRR = (16 * baudrate) / 36000000;
    }else if(usart == USART3){
        RCC->APB2ENR|=RCC_APB1ENR_USART3EN;
        GPIOA->CRH &= ~(0XF << (10 * 4));
        GPIOA->CRH |= (0xA << (10 * 4));
        GPIOA->CRH &= ~(0XF << (11 * 4));
        GPIOA->CRH |= (0x4 << (11 * 4));
        USART3->BRR = (16 * baudrate) / 36000000;
    }
}

void usart_send_char(USART_TypeDef* usart, char c){
    usart->DR = c;
}

void usart_send_string(USART_TypeDef* usart, char* str){
    while(*str){
        while (!(USART1->SR & USART_SR_TXE));
        USART1->DR = *str++;
    }
}

char usart_recibir_char(USART_TypeDef* usart){
    int c;
    while((usart->SR & USART_SR_RXNE) == 0);
    if(usart-> SR & USART_SR_RXNE){
        return c = usart->DR;
    }
}