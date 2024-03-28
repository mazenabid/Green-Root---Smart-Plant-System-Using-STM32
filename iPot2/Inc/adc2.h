/*
 * adc2.h
 *
 *  Created on: Mar 19, 2024
 *      Author: mazen
 */

#ifndef ADC2_H_
#define ADC2_H_

#include <stdint.h>
#include "stm32f1xx.h"

void pa2_adc_init(void);
float adc_read_temp_sensor(void);
void start_conversion2(void);


#endif /* ADC2_H_ */
