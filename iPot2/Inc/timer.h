#include "stm32f1xx.h"
#include <stdbool.h>

void delay(uint32_t);

/* Timer 1 provides PWM output functions */
void tim1_init(void);
void tim1_init_ch(uint8_t, uint16_t);
void tim1_update_ccr(uint8_t, uint16_t);
void TIM1_int_enable(void);
void TIM1_UP_IRQHandler(void);

extern volatile uint16_t target_tim1_ccr1;
extern volatile uint16_t target_tim1_ccr2;
extern volatile uint16_t current_tim1_ccr1;
extern volatile uint16_t current_tim1_ccr2;

/* Timer 2 provides delay time functions */
void tim2_init(void);
void delay_us(uint16_t);
void delay_ms(uint16_t);

/* Timer 3 provides PWM output functions */
void tim3_init(void);
void tim3_init_ch(uint8_t, uint16_t);
void tim3_update_ccr(uint8_t, uint16_t);
void TIM3_int_enable(void);
void TIM3_IRQHandler(void);

extern volatile uint16_t target_tim3_ccr1;
extern volatile uint16_t target_tim3_ccr2;
extern volatile uint16_t target_tim3_ccr3;
extern volatile uint16_t target_tim3_ccr4;
extern volatile uint16_t current_tim3_ccr1;
extern volatile uint16_t current_tim3_ccr2;
extern volatile uint16_t current_tim3_ccr3;
extern volatile uint16_t current_tim3_ccr4;

/* Timer 4 provides the millis() function using an interrupt and a global variable */
void tim4_init(void);
void TIM4_IRQHandler(void);
uint32_t millis(void);


//volatile uint32_t millis_counter = 0; //Define this in main.c
extern volatile uint32_t millis_counter;



