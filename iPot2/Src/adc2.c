///*
// * adc2.c
// *
// *  Created on: Mar 19, 2024
// *      Author: mazen
// */
//
//
//#include "stm32f1xx.h"
//#include "adc2.h"
//#include <stdio.h>
//
//#define ADC2EN            (1U<<10) // ADC2 enable bit in RCC_APB2ENR
//#define ADC_CH2           (1U<<0)  // Channel 2 selection
//#define ADC_SEQ_LEN_1     0x00     // 1 conversion in the sequence
//#define CR2_ADON          (1U<<0)
//#define CR2_SWSTART       (1U<<22)
//#define SR_EOC            (1U<<1)
//
//#define ADC_CHANNEL_TEMP_SENSOR 2 // PA2 corresponds to ADC channel 2
//#define VREF 5.0f // Reference voltage in volts
//#define ADC_RESOLUTION 4095.0f // 12-bit ADC
//
//
//
//
//
////----PA2 CH2 FOR Temp. Sensor----//
//void pa2_adc_init(void) {
//
//
//void delay_ms(uint32_t delayTime) {
//	for(uint32_t i = 0; i < delayTime * 4000; i++) {
//	            // Empty loop for delay
//	        }
//	    }
//
//    // Enable the clock for ADC2 and GPIOA
//    RCC->APB2ENR |= RCC_APB2ENR_ADC2EN | RCC_APB2ENR_IOPAEN; // Correctly enabling ADC2 clock
//
//    // Configure PA2 as analog input
//    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // Reset PA2 configuration
//
//    ADC2->CR2 |= ADC_CR2_ADON; // Turn on the ADC
//    delay_ms(20);
//
//    // Calibration (optional but recommended)
////    ADC2->CR2 |= ADC_CR2_CAL; // Start ADC calibration
////    while (ADC2->CR2 & ADC_CR2_CAL); // Wait for calibration to finish
//
//    // Configure ADC2 to read from channel corresponding to PA2
//    ADC2->SQR3 = ADC_CHANNEL_TEMP_SENSOR; // Setting the first conversion in regular sequence to channel 2
//
////    ADC2->SMPR2 |= ADC_SMPR2_SMP2; // Sample time configuration for channel 2
//
//    ADC2->SMPR2 |= ADC_SMPR2_SMP1; // Sample time for channel 1
//        ADC2->SQR1 &= ~ADC_SQR1_L; // Sequence length = 1 conversion
//        ADC2->SQR3 = 1; // 1st conversion in sequence to channel 1
//        ADC2->CR2 |= ADC_CR2_ADON; // Enable ADC
//}
//
//void start_conversion2(void) {
//	ADC2->CR2 |= ADC_CR2_ADON; // Wake up the ADC from power down mode
//		ADC2->CR2 |= ADC_CR2_SWSTART; // Start conversion
//		// We now enable continuous conversion
//		ADC2->CR2 |= ADC_CR2_CONT;
//
//}
//
//float adc_read_temp_sensor(void) {
//    // Ensure ADC2 and GPIOA clock are enabled
//    RCC->APB2ENR |= RCC_APB2ENR_ADC2EN | RCC_APB2ENR_IOPAEN;
//
//    // Configure PA2 as an analog input
//    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
//
//    // Configure ADC2 for temperature sensor reading
//    ADC2->SQR3 = ADC_CHANNEL_TEMP_SENSOR; // Set the ADC channel for PA2
//    ADC2->SMPR2 |= ADC_SMPR2_SMP2; // Set sample time for channel 2
//
//    // Start ADC calibration (optional but recommended)
//    ADC2->CR2 |= ADC_CR2_CAL;
//    while (ADC2->CR2 & ADC_CR2_CAL); // Wait for calibration to complete
//
//    // Start conversion for temperature sensor reading
//    start_conversion2();
//
//    // Wait for conversion to complete
//    while (!(ADC2->SR & SR_EOC));
//
//    // Read conversion result
//    uint32_t adcValue = ADC2->DR;
//
//    // Calculate temperature from ADC value (LM35 with 10mV/°C and VREF)
//    float temperature = (3300 * adcValue) / 4095.0 / 35.0;
//
//    return temperature;
//}
//
