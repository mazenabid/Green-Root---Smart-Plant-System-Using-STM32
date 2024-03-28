/*
 * dht.h
 *
 *  Created on: Mar 19, 2024
 *      Author: mazen
 */



#ifndef DHT_H_
#define DHT_H_
#include <stdint.h>

typedef enum {
    Response_OK,
    Response_ERR
} DHT11_Response_Typedef;



void readDHT11(void);
extern uint8_t humidity;
extern uint8_t temperature;

void dht11_Pin_Init(void);
void dht11_start(void);
DHT11_Response_Typedef Check_Response();
uint32_t DHT11_Read(void);
void Get_DHT_Data(float *TEMP, float *RH);




#endif /* DHT_H_ */
