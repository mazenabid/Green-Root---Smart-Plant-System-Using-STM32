#include "i2c.h"
#include "uart.h"
#include "stdio.h"

char data[50];
void i2c_init(void) {
    // Enable clock for GPIOB and I2C1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock (IOPBEN in APB2ENR for F1 series)
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // Enable I2C1 clock

    // Configure PB6 and PB7 for I2C use
    GPIOB->CRL &= ~(GPIO_CRL_CNF6 | GPIO_CRL_CNF7 | GPIO_CRL_MODE6 | GPIO_CRL_MODE7); // Clear CNF and MODE bits for PB6 and PB7
    GPIOB->CRL |= (GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1); // Set PB6/PB7 as alternate function open-drain
    GPIOB->CRL |= (GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1); // Set PB6/PB7 to Fast mode (10 MHz)

    // Reset and release reset of I2C1
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // Configure I2C1
    I2C1->CR2 |= 36; // Set I2C clock speed (36MHz PCLK1, adjust if your clock setup is different)
    I2C1->CCR = 180; // CCR value for standard mode I2C (100kHz) with PCLK1 at 36MHz
    I2C1->TRISE = 37; // Maximum rise time (in APB1 clock cycles in standard mode, 1000ns/27.78ns = 36 + 1)

    // Enable I2C1
    I2C1->CR1 |= I2C_CR1_PE;
}


char i2c_readByte(char saddr,char maddr, char *data)
{
volatile int tmp;
while(I2C1->SR2&I2C_SR2_BUSY){;}
I2C1->CR1|=I2C_CR1_START;
while(!(I2C1->SR1&I2C_SR1_SB)){;}
I2C1->DR=saddr<<1;
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}
tmp=I2C1->SR2;
while(!(I2C1->SR1&I2C_SR1_TXE)){;}
I2C1->DR=maddr;
while(!(I2C1->SR1&I2C_SR1_TXE)){;}
I2C1->CR1|=I2C_CR1_START;
while(!(I2C1->SR1&I2C_SR1_SB)){;}
I2C1->DR=saddr<<1|1;
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}
I2C1->CR1&=~I2C_CR1_ACK;
tmp =I2C1->SR2;
I2C1->CR1|=I2C_CR1_STOP;
while(!(I2C1->SR1&I2C_SR1_RXNE)){;}
*data=I2C1->DR;
return 0;
}


void delay(int ms)
	{
	SysTick->LOAD=16000-1;
	SysTick->VAL=0;
	SysTick->CTRL=0x5;
		for (int i=0;i<ms;i++)
		{
			while(!(SysTick->CTRL &0x10000)){}
		}
	SysTick->CTRL=0;

	}

void i2c_bus_scan(void)
{
					int a=0; //address variable
         for (uint8_t i=0;i<128;i++) //go through all 127 address
   {
            I2C1->CR1 |= I2C_CR1_START; //generate start
            while(!(I2C1->SR1 & I2C_SR1_SB)); // wait to start to be generated
            I2C1->DR=(i<<1|0); // transmit the address
            while(!(I2C1->SR1)|!(I2C1->SR2)){}; //clear status register
            I2C1->CR1 |= I2C_CR1_STOP; //generate stop condition
            delay(1);//minium wait time is 40 uS, but for sure, leave it 100 uS
            a=(I2C1->SR1&I2C_SR1_ADDR); //read the status register address set
            if (a==2)//if the address is valid
         {
					 //print the address
					 sprintf(data,"Found I2C device at adress 0x%X (hexadecimal), or %d (decimal)\r\n",i,i);
           UART_Write_String(data);
         }
     }
}

void i2c_write_byte(char saddr,char maddr, char *data)
	{
volatile int Temp;
while(I2C1->SR2&I2C_SR2_BUSY){;}          /*wait until bus not busy*/
I2C1->CR1|=I2C_CR1_START;                 /*generate start*/
while(!(I2C1->SR1&I2C_SR1_SB)){;}         /*wait until start bit is set*/
I2C1->DR = saddr<< 1;                 	 /* Send slave address*/
while(!(I2C1->SR1&I2C_SR1_ADDR)){;}      /*wait until address flag is set*/
Temp = I2C1->SR2; 											 /*clear SR2 by reading it */
while(!(I2C1->SR1&I2C_SR1_TXE)){;}       /*Wait until Data register empty*/
I2C1->DR = maddr;                        /* send memory address*/
while(!(I2C1->SR1&I2C_SR1_TXE)){;}       /*wait until data register empty*/
I2C1->DR = *data;
while (!(I2C1->SR1 & I2C_SR1_BTF));      /*wait until transfer finished*/
I2C1->CR1 |=I2C_CR1_STOP;								 /*Generate Stop*/
}

void i2c_ReadMulti(char saddr,char maddr, int n, char* data)
{
	volatile int temp;
	while (I2C1->SR2 & I2C_SR2_BUSY){;}
	I2C1->CR1|=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)){;}
	I2C1->DR=saddr<<1;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)){;}
	temp=I2C1->SR2;
	while(!(I2C1->SR1&I2C_SR1_TXE)){;}
	I2C1->DR = maddr;
	while(!(I2C1->SR1&I2C_SR1_TXE)){;}
	I2C1->CR1|=I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB)){;}
	I2C1->DR=saddr<<1|1;
	while(!(I2C1->SR1 & I2C_SR1_ADDR)){;}
	temp=I2C1->SR2;
	I2C1->CR1|=I2C_CR1_ACK;
	while(n>0U)
		{
		if(n==1U)
				{
				I2C1->CR1&=~I2C_CR1_ACK;
					I2C1->CR1|=I2C_CR1_STOP;
					while(!(I2C1->SR1&I2C_SR1_RXNE)){;}
					*data++=I2C1->DR;
						break;
				}
			else
					{

					while(!(I2C1->SR1&I2C_SR1_RXNE)){;}
						(*data++)=I2C1->DR;
							n--;

					}


		}

}

void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length)
{
while (I2C1->SR2 & I2C_SR2_BUSY);           //wait until bus not busy
I2C1->CR1 |= I2C_CR1_START;                   //generate start
while (!(I2C1->SR1 & I2C_SR1_SB)){;}					//wait until start is generated
volatile int Temp;
I2C1->DR = saddr<< 1;                 	 			// Send slave address
while (!(I2C1->SR1 & I2C_SR1_ADDR)){;}        //wait until address flag is set
Temp = I2C1->SR2; 														//Clear SR2
while (!(I2C1->SR1 & I2C_SR1_TXE));           //Wait until Data register empty
I2C1->DR = maddr;                      				// send memory address
while (!(I2C1->SR1 & I2C_SR1_TXE));           //wait until data register empty
//sending the data
for (uint8_t i=0;i<length;i++)
 {
 I2C1->DR=buffer[i]; 													//filling buffer with command or data
	while (!(I2C1->SR1 & I2C_SR1_BTF));
 }

I2C1->CR1 |= I2C_CR1_STOP;										//wait until transfer finished

}

void lcd_write_i2c(char saddr,uint8_t *buffer, uint8_t length)
{
while (I2C1->SR2 & I2C_SR2_BUSY);           //wait until bus not busy
I2C1->CR1 |= I2C_CR1_START;                   //generate start
while (!(I2C1->SR1 & I2C_SR1_SB)){;}					//wait until start is generated
volatile int Temp;
I2C1->DR = saddr<< 1;                 	 			// Send slave address
while (!(I2C1->SR1 & I2C_SR1_ADDR)){;}        //wait until address flag is set
Temp = I2C1->SR2; 														//Clear SR2
//sending the data
for (uint8_t i=0;i<length;i++)
 {
 I2C1->DR=buffer[i]; 													//filling buffer with command or data
	while (!(I2C1->SR1 & I2C_SR1_BTF));
 }

I2C1->CR1 |= I2C_CR1_STOP;										//wait until transfer finished

}
