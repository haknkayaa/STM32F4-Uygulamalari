#include "stm32f411xe.h"
#include "ddSpi.h"

// brief  : SPI1 Setup
// Arg1   : None 
// return : None
void SPI1_Setup(void)
{
  // RCC
  SPI1_CLOCK_ON();
  PORTA_CLOCK_ON(); 

  // GPIO
  // MISO,MOSI,SCK  
  GPIOA->MODER   |= (0x02 << (5*2));    //PA.5 AF --> SPI1_SCK
  GPIOA->MODER   |= (0x02 << (6*2));    //PA.6 AF --> SPI1_MISO
  GPIOA->MODER   |= (0x02 << (7*2));    //PA.7 AF --> SPI1_MOSI
  GPIOA->AFR[0]  |= 0x55500000;         //PA.5 AF05, PA.6 AF05, PA.7 AF05,
  GPIOA->OSPEEDR |= (0x02 << (5*2));    //PA.5 Fast Speed
  GPIOA->OSPEEDR |= (0x02 << (6*2));    //PA.6 Fast Speed
  GPIOA->OSPEEDR |= (0x02 << (7*2));    //PA.7 Fast Speed

  // SPI1
  SPI1->CR1 |= (SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2); // PS : 256
  SPI1->CR1 |= SPI_CR1_SSI;             // 
  SPI1->CR1 |= SPI_CR1_SSM;             // Software NSS(CS) Pin Kontrol
  SPI1->CR1 |= SPI_CR1_MSTR;            // SPI Master Mode
  SPI1->CR2 = 0x00000000;               // SPI in StandarMode (Motorola)
  SPI1->CR1 |= SPI_CR1_SPE;             // SPI ON  

}


// brief  : buton_task
// Arg1   : uint8_t txData : Data to SEND 
// return : uint8_t : Received Data
uint8_t SPI_TX_RX_Byte_Polling(uint8_t txData)
{
  uint8_t rxData = 0;
  while((SPI1->SR & (1 << 1)) == 0);    //SPI TX Boþ mu?
  SPI1->DR = txData;                    //Send TX   
  while((SPI1->SR & (1 << 0)) == 0);    //SPI RX Boþ mu?
  rxData = SPI1->DR;                    //Get RX        
  return rxData;                       
}



