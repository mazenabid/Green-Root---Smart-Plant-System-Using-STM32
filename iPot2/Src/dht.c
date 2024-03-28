/*
 * dht.c
 *
 *  Created on: Mar 19, 2024
 *      Author: mazen
 */



#include "stm32f1xx.h"
#include "dht.h"

uint8_t humidity = 0;
uint8_t temperature = 0;

void readDHT11(void) {
    uint8_t bits[5] = {0, 0, 0, 0, 0};
    uint8_t i, j = 0;

    // Prepare the pin (PA2) for communication
    GPIOA->CRL &= ~(GPIO_CRL_MODE2); // Clear mode for PA2
    GPIOA->CRL |= GPIO_CRL_MODE2_0;  // Output mode, max speed 10 MHz.
    GPIOA->CRL &= ~(GPIO_CRL_CNF2);  // General purpose output push-pull

    // Send start signal
    GPIOA->BRR = GPIO_BRR_BR2; // PA2 low
    delay_ms(18); // At least 18ms
    GPIOA->BSRR = GPIO_BSRR_BS2; // PA2 high
    delay_us(30); // 20-40us

    // Set PA2 back to input
    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2); // Input mode
    GPIOA->CRL |= GPIO_CRL_CNF2_1; // Input with pull-up / pull-down
    GPIOA->ODR |= GPIO_ODR_ODR2; // Enable pull-up

    // Wait for DHT11 response
    delay_us(40);
    if(!(GPIOA->IDR & GPIO_IDR_IDR2)) { // DHT11 pulls line low
        delay_us(80);
        if(GPIOA->IDR & GPIO_IDR_IDR2) { // DHT11 pulls line high
            delay_us(80);
            // Start reading 40 bits (5 bytes) of data
            for (j = 0; j < 5; j++) { // Read 5 bytes
                for(i = 0; i < 8; i++) { // Read each bit
                    while(!(GPIOA->IDR & GPIO_IDR_IDR2)); // Wait for the pin to go high
                    delay_us(40); // DHT11 data bit start
                    if(GPIOA->IDR & GPIO_IDR_IDR2) { // If high after 40us, bit is 1
                        bits[j] |= (1 << (7 - i));
                        while(GPIOA->IDR & GPIO_IDR_IDR2); // Wait for the pin to go low
                    }
                }
            }
            // Check checksum
            if (((bits[0] + bits[1] + bits[2] + bits[3]) & 0xFF) == bits[4]) {
                // Convert to values
                humidity = bits[0];
                temperature = bits[2];
            }
        }
    }
}




//
//
//#include "dht.h"
//#include "stm32f1xx.h" // Make sure this include matches your project
//#include <stdint.h>
//void dht11_Pin_Init(void)
//{
//    /* Enable clock access to GPIOA */
//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
//
//    /* Set PA2 as input floating (default state) */
//    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
//    GPIOA->CRL |= GPIO_CRL_CNF2_0;
//}
//
//void dht11_start(void)
//{
//    /* Set PA2 as output */
//    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
//    GPIOA->CRL |= (GPIO_CRL_MODE2_1 | GPIO_CRL_MODE2_0); // Output mode, max speed 50 MHz.
//
//    /* Pull the pin low for at least 18ms */
//    GPIOA->BSRR = GPIO_BSRR_BR2;
//    delay(18);
//
//    /* Pull the pin high for ~20-40us before switching to input */
//    GPIOA->BSRR = GPIO_BSRR_BS2;
//    delay_us(30); // Ensure you have a function that accurately delays for microseconds
//
//    /* Set PA2 back to input floating */
//    GPIOA->CRL &= ~(GPIO_CRL_MODE2 | GPIO_CRL_CNF2);
//    GPIOA->CRL |= GPIO_CRL_CNF2_0;
//}
//
//DHT11_Response_Typedef Check_Response()
//{
//    uint8_t Response = 0;
//    if (!(GPIOA->IDR & GPIO_IDR_IDR8))
//    {
//        delay(80);
//        if (GPIOA->IDR & GPIO_IDR_IDR8)
//        {
//            Response = Response_OK;
//        }
//        else
//        {
//            Response = Response_ERR;
//        }
//    }
//    while (GPIOA->IDR & GPIO_IDR_IDR8); // wait for the pin to go low
//    return Response;
//}
//
//
//uint32_t DHT11_Read(void){
//    uint32_t i, j, result=0;
//    for (j = 0; j < 8; j++)
//    {
//        while (!(GPIOA->IDR & GPIO_IDR_IDR8)); // Wait for the pin to go high
//
//        if (GPIOA->IDR & GPIO_IDR_IDR8) // If the pin is high after 40 us, it's a '1'
//        {
//            result |= (1 << (7 - j)); // Write 1
//        }
//        else // Otherwise, it's a '0' and result is left unchanged for that bit
//        {
//            // The line below is not necessary, but shown here for clarity
//            // result &= ~(1 << (7 - j)); // Write 0, though the bit is already 0 in the initialized 'result'
//        }
//
//        while (GPIOA->IDR & GPIO_IDR_IDR8); // Wait for the pin to go low (end of bit transmission)
//    }
//    return result;
//}
//
//void Get_DHT_Data(float *TEMP, float *RH)
//{
//    // Send start signal and check for response
//    dht11_start();
//    if (Check_Response() == Response_OK)
//    {
//        uint8_t Rh_byte1 = DHT11_Read();
//        uint8_t Rh_byte2 = DHT11_Read();
//        uint8_t Temp_byte1 = DHT11_Read();
//        uint8_t Temp_byte2 = DHT11_Read();
//        uint8_t SUM = DHT11_Read();
//
//        // Validate data integrity with checksum
//        if (SUM == (Rh_byte1 + Rh_byte2 + Temp_byte1 + Temp_byte2))
//        {
//            // Assuming the DHT11 sensor, where Rh_byte2 and Temp_byte2 are always zero
//            *TEMP = Temp_byte1; // Whole number part, DHT11 doesn't provide fractional temperature data
//            *RH = Rh_byte1; // Whole number part, DHT11 doesn't provide fractional humidity data
//        }
//        else
//        {
//            // Handle checksum mismatch error, for example by indicating invalid data
//            *TEMP = -1.0f;
//            *RH = -1.0f;
//        }
//    }
//    else
//    {
//        // Handle no response error
//        *TEMP = -1.0f;
//        *RH = -1.0f;
//    }
//}


