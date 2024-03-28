/*
 * adc.h
 *
 *  Created on: Mar 17, 2024
 *      Author: mazen
 */

#ifndef ADC_H_
#define ADC_H_
#include<stdint.h>

void adc_init(void);
uint32_t start_conversion(uint32_t channel);

#endif /* ADC_H_ */
