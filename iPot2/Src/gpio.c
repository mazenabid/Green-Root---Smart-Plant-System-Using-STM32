#include "stm32f1xx.h"
#include "gpio.h"

void LD2_init(void)
{	
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~GPIO_CRL_CNF5 & ~GPIO_CRL_MODE5;
	GPIOA->CRL |= GPIO_CRL_MODE5;
}

void LD2_OFF(void)
{
	GPIOA->BSRR |= GPIO_BSRR_BR5;	
}

void LD2_ON(void)
{
	GPIOA->BSRR |= GPIO_BSRR_BS5;
}

void LD2_TOGGLE(void)
{
	GPIOA->ODR ^= GPIO_ODR_ODR5;
}

