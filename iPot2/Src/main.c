#include "i2c.h"
#include "uart.h"
#include "stdlib.h"
#include "LiquidCrystal_PCF8574.h"
#include "adc.h"
#include "adc2.h"
#include "i2c_lcd_driver.h"
#include "timer.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "dht.h"
#include "stdbool.h"

#define MAX_ACTIVATIONS 3
//#define ACTIVATION_PERIOD 86400000 // 24 hours in milliseconds
#define ACTIVATION_PERIOD 6000 // 1 minute in milliseconds (test)
#define RELAY_OFF_DELAY 10000 // 10 seconds delay for the relay to be turned off

/***********************************RELAY*********************************************/

// Initialization for Relay Control with the Moisture Sensor
uint32_t activationTimes[MAX_ACTIVATIONS] = {0};
uint8_t activationCount = 0;
uint32_t periodStartTime = 0; // Time when the current period started
bool isRelayOn = false;
uint32_t relayOnTime = 0;
uint32_t relayOffTime = 0; // Last time the relay was turned off


char str[40];


volatile uint32_t msTicks; // Counter for milliseconds


/*******************************TIM2 INITIALIZATION***********************************/

// Initialize TIM2 to trigger an interrupt every 1ms
void Timer2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // Enable clock for TIM2
    TIM2->PSC = 7200 - 1; // Pre-scaler to tick at 10kHz assuming 72MHz clock, adjust for your clock
    TIM2->ARR = 10 - 1;  // Auto-reload at 10 ticks = 1ms
    TIM2->DIER |= TIM_DIER_UIE; // Enable update interrupt
    TIM2->CR1 |= TIM_CR1_CEN; // Start the timer

    NVIC_EnableIRQ(TIM2_IRQn); // Enable TIM2 interrupt in NVIC
}

// TIM2 Interrupt Handler updates msTicks
void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) { // Check interrupt source
        msTicks++; // Increment the millisecond counter
        TIM2->SR &= ~TIM_SR_UIF; // Clear the interrupt flag
    }
}

void Delay_ms(uint32_t ms) {
    uint32_t tickStart = msTicks;
    while ((msTicks - tickStart) < ms);
}

uint32_t get_millis(void) {
    return msTicks;
}

/********************************MAIN FUNCTION***********************************/


int main() {

	// Call Functions
	Timer2_Init(); // Initialize timer
    i2c_init(); // Initialize I2C
    lcd_init(); // Initialize LCD
    adc_init(); // Initialize ADC for Sensors and Relay
    //USART2_Init(); // Initialize USART for debugging

//-------------------------------------------------------------------------//

    // Variable declarations
    uint32_t moistureValue = 0;
    uint32_t rawTempValue = 0;
    float temperature = 0.0f;


//-------------------------------------------------------------------------//
    void delay_ms(uint32_t delayTime) {
        for(uint32_t i = 0; i < delayTime * 18000; i++) {
            __NOP(); // NOP (No Operation) is used here to ensure the compiler doesn't optimize the loop away.
        }
    }
//----------------------------------PA0 INITIALIZATION----------------------------------//

    // Enable GPIOA clock for PA0 button
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// Set PA0 as input with pull-up
	GPIOA->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0); // Input mode
	GPIOA->CRL |= GPIO_CRL_CNF0_1; // Input with pull-up / pull-down
	GPIOA->ODR |= GPIO_ODR_ODR0; // Enable pull-up

//---------------------------PB0 INITIALIZATION FOR RELAY-------------------------------//

	// Enable clock for GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	// Configure PB0 as output push-pull, max speed 10 MHz
	GPIOB->CRL &= ~GPIO_CRL_MODE0; // Clear MODE0 bits
	GPIOB->CRL &= ~GPIO_CRL_CNF0;  // Clear CNF0 bits
	GPIOB->CRL |= GPIO_CRL_MODE0_0; // Output mode, max speed 10 MHz

//--------------------------------MESSAGE WHEN REBOOTING----------------------------------//

lcd_clear();
setCursor(0, 0);
lcd_send_string("--------------------");
setCursor(0, 1);
lcd_send_string("        iPot"); // 8 spaces before "ipot"
setCursor(0, 2);
lcd_send_string("      By: Mazen ");
setCursor(0, 3);
lcd_send_string("--------------------");
delay_ms(100);
lcd_clear();

//--------------------------------WHILE LOOP----------------------------------//

    while(1) {

    	// DAC -> Button Press Initialization
        if (!(GPIOA->IDR & GPIO_IDR_IDR0)) { // Check if button is pressed
            setCursor(0, 0);
            lcd_send_string("                    "); // Clear the first line
            setCursor(0, 1);
            lcd_send_string("                    "); // Clear the second line
            setCursor(0, 2);
            lcd_send_string("I'm a Cactus!       "); // Display message
            delay_ms(50); // Display the message for 2 seconds
            lcd_clear();

//--------------------------------RELAY & SENSOR READINGS----------------------------------//

        } else {

            // Read from the soil moisture sensor on PA1
            moistureValue = start_conversion(1); // Selecting ADC channel for PA1 (1)

            // Convert ADC value to moisture percentage
            moistureValue = (moistureValue * 100 / 4095); // Read sensor value

//--------------------------------RELAY FUNCTIONALITY----------------------------------//


            // Control relay based on moisture level
            uint32_t currentTime = get_millis(); // Get the current time in milliseconds

            // Check if the period has elapsed to reset activation count
            if (currentTime - periodStartTime >= ACTIVATION_PERIOD) {
                periodStartTime = currentTime; // Start a new period
                activationCount = 0; // Reset the activation count for the new period
            }

            // Relay activation logic
            if (moistureValue <= 30) {
                if (!isRelayOn && activationCount < MAX_ACTIVATIONS) {
                    // Turn on the relay
                    GPIOB->BSRR = GPIO_BSRR_BS0; // Example for turning on the relay
                    relayOnTime = currentTime;
                    isRelayOn = true;
                    activationCount++; // Increment the activation count
                }
            } else if (moistureValue >= 60 && isRelayOn) {
                // Turn off the relay
                GPIOB->BSRR = GPIO_BSRR_BR0; // Example for turning off the relay
                isRelayOn = false;
                relayOffTime = currentTime; // Update last off time
            }

            // Automatic turn-off after 10 seconds
            if (isRelayOn && (currentTime - relayOnTime > 1000)) { // 10 seconds
                GPIOB->BSRR = GPIO_BSRR_BR0; // Turn off the relay
                isRelayOn = false;
                relayOffTime = currentTime; // Update last off time
            }

        }

 //-------------------------READ & DISPLAY SENSOR VALUES TO LCD--------------------------//

            // Read from the temperature sensor on PA4
            rawTempValue = start_conversion(4); // Select ADC channel for PA4 (4)

            // Convert raw ADC value to temperature here
            temperature = ((rawTempValue * 3300 )/ 4096 /10);

            setCursor(0, 0);
            snprintf(str, sizeof(str), "Temp: %.1fC", temperature);
            lcd_send_string(str); // Display temperature

            setCursor(0, 1);
            snprintf(str, sizeof(str), "Moisture: %lu%%    ", moistureValue); // Add spaces to clear extra characters
            lcd_send_string(str); // Display moisture value
            delay_ms(10);

        }
    }

/*****************************************THE END****************************************/



