#ifndef __ddUsart2_H
#define __ddUsart2_H

#define PORTA_CLOCK_ON() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN) 
#define USART2_CLOCK_ON() (RCC->APB1ENR |= RCC_APB1ENR_USART2EN) 

#define TX_Buffer_Size  100
#define RX_Buffer_Size  100

//Exported Variables

//Exported Functions
void USART2_Setup(void);
uint8_t USART2_TX_Polling(uint8_t* tBuffer, uint8_t tCount);
uint8_t USART2_TX_INT(uint8_t* tBuffer, uint8_t tCount);

#endif /* __ddUsart2_H */

