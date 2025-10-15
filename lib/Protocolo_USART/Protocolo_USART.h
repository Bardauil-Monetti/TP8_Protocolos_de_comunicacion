#ifndef PROTOCOLO_USART
#define PROTOCOLO_USART
#include "stm32f103xb.h"

void usart_init(USART_TypeDef* usart, int baudrate);
void usart_send_char(USART_TypeDef* usart, char c);
void usart_send_string(USART_TypeDef* usart, char* str);
char usart_recibir_char(USART_TypeDef* usart);

#endif