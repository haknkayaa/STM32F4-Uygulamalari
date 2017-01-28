#ifndef __ddSpi1_H
#define __ddSpi1_H

#define PORTA_CLOCK_ON() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN) 
#define SPI1_CLOCK_ON()  (RCC->APB2ENR |= RCC_APB2ENR_SPI1EN) 

//Exported Variables

//Exported Functions
void SPI1_Setup(void);
uint8_t SPI_TX_RX_Byte_Polling(uint8_t txData);

#endif /* __ddSpi1_H */

