#include "stm32f1xx.h"
#include "adc.h"
#include <stdio.h>
#define GPIOAEN
#define ADC1EN			(1U<<9) // bit 9 in the APB2
#define ADC_CH1			(1U<<0) //1 at bit 0, position 0.
#define CR2_ADON		(1U<<0)
#define SR_EOC			(1U<<1)

/********************************ADC1 INITIALIZATION************************************/

void adc_init(void)
{

	// Enable ADC1 and GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;

    // Initialize PA1 and PA4 as analog inputs for ADC
    GPIOA->CRL &= ~((GPIO_CRL_MODE1 | GPIO_CRL_CNF1) | (GPIO_CRL_MODE4 | GPIO_CRL_CNF4)); // Clear MODE and CNF for PA1 and PA4


    //1 Set ADC pre-scaler to divide APB2 clock by 8 (72MHz/8 = 9Mhz)
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;

    // Enable ADC1
    ADC1->CR2 |= ADC_CR2_ADON;


    // 2 Set ADC sampling rate to its lowest value for PA0, PA1, and PA4
    ADC1->SMPR2 = 0x0000703F; //I'm using PA0, PA1,PA4

    // 3 ADC1 calibration
    ADC1->CR2 |= ADC_CR2_CAL;
    while ((ADC1->CR2 & (ADC_CR2_CAL)) == ADC_CR2_CAL);

}

/***************************ADC1 CONVERSION FUNCTION BASED ON CHANNEL************************/

uint32_t start_conversion(uint32_t channel) {

    // Select the ADC channel
    ADC1->SQR3 = channel;

    // Start the conversion
    ADC1->CR2 |= ADC_CR2_ADON ;//| ADC_CR2_SWSTART;

    // Wait for the conversion to complete
    while (!(ADC1->SR & ADC_SR_EOC));

    // Return the conversion result
    return ADC1->DR;

}



