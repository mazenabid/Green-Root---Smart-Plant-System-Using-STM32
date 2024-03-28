#include "uart.h"
#include "stdarg.h"

void USART2_Init(void) {
    // Enable clocks for USART2 and GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // Enable GPIOA clock for F1 series

    // Configure GPIOA pins for USART2. PA2(TX) and PA3(RX)
    // For STM32F103, we use the CRL register to configure pins < 8
    // Set PA2 as alternate function push-pull and PA3 as floating input (default state after reset)
    GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2); // Clear CNF and MODE bits for PA2
    GPIOA->CRL |= (GPIO_CRL_CNF2_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1); // Output mode, max speed 50 MHz for PA2
    // Note: RX pin PA3 is already in floating input mode after reset, so no need for explicit configuration

    // Configure USART2
    // Assuming a PCLK1 of 36MHz, calculate the correct BRR for 115200 baud
    // For oversampling by 16, USARTDIV = PCLK1 / (16 * baudrate)
    USART2->BRR = 72000000 / (16 * 115200); // Adjust if your PCLK1 is different

    USART2->CR1 |= USART_CR1_TE; // Enable transmitter
    USART2->CR1 |= USART_CR1_UE; // Enable USART
}


void USART_write(int ch){
while(!(USART2->SR&0x0080)){
}
USART2->DR=(ch);

}

void UART_Write_String(char *p)
	{
	while(*p!='\0')
{
USART_write(*p);
p++;
}
}

