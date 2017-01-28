#ifndef __ddI2C1_H
#define __ddI2C1_H

#define PORTB_CLOCK_ON() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN) 
#define I2C1_CLOCK_ON()  (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN) 

//Exported Variables

//Exported Functions
void I2C1_Setup(void);
uint8_t I2C1_Read_Single_Register(uint8_t slave_address, uint8_t reg_address);
uint8_t I2C1_Write_Single_Register(uint8_t slave_address, uint8_t reg_address, uint8_t data);

#endif /* __ddSpi1_H */