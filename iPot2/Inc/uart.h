#ifndef __uart__h
#define __uart__h
#include "stm32f1xx.h"                  // Device header
#include "stdio.h"
void USART2_Init(void);

void UART_Write_String(char *p);

void USART_Init(void);
void USART_SendChar(char c);
void USART_SendString(const char* str);


#endif
