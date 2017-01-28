#include "stm32f411xe.h"
#include "ddUsart2.h"

// USART BUFFER
uint8_t RX_Buffer[RX_Buffer_Size];
uint8_t RX_Buffer_Pointer = 0;

uint8_t TX_Buffer[TX_Buffer_Size];
uint8_t TX_Buffer_Pointer = 0;
uint8_t TX_NumberofTransfer = 0;


// brief  : buton_task
// Arg1   : None 
// return : None
void USART2_Setup(void)
{
  // RCC
  USART2_CLOCK_ON();
  PORTA_CLOCK_ON();     
  // GPIO
  GPIOA->MODER   |= (0x02 << (2*2));    //PA.2 AF
  GPIOA->MODER   |= (0x02 << (3*2));    //PA.3 AF
  GPIOA->AFR[0]  |= 0x00007700;         //PA.2 AF07, PA.3 AF07
  GPIOA->OSPEEDR |= (0x02 << (2*2));    //PA.2 Fast Speed
  GPIOA->OSPEEDR |= (0x02 << (3*2));    //PA.3 Fast Speed
  // USART
  USART2->CR1 = 0x0000200C;             //USART ON, TX ON, RX ON
  USART2->CR2 = 0x00000000;             //STOP Bit = 1 bit
  USART2->BRR = (8 << 4) | (0x0B);      //115200 Baud Rate
  // USART INTERRUPT
  USART2->CR1 |= (1 << 5);              //USART2 RXNE INT Enable
  NVIC_SetPriority(USART2_IRQn, 0x0);   //Set Lowest Pri. to USART2
  NVIC_EnableIRQ(USART2_IRQn);          //Enable USART2 INTERRUPTs
}


// brief  : USART Send Bytes (Polling Method)
// Arg1   : tBuffer : Buffer To Send
// Arg2   : tCount : Number of Bytes To Send
// return : 0 : No ERROR, 0xFF : Overflow ERROR 
uint8_t USART2_TX_Polling(uint8_t* tBuffer, uint8_t tCount)
{
  uint8_t counter = 0;
  if(tCount > TX_Buffer_Size)
    return 0xFF;
  TX_NumberofTransfer = tCount;
  for(counter = 0; counter < TX_NumberofTransfer; counter++)
    TX_Buffer[counter] = tBuffer[counter];
  counter = 0;
  while(TX_NumberofTransfer > 0)
  {
    while((USART2->SR & (1 << 7)) == 0);    //USART TX Boþ mu?
    USART2->DR = TX_Buffer[counter];
    TX_NumberofTransfer--;
    counter++;
  }
  return 0;
}

// brief  : USART Send Bytes (Interrupt Method)
// Arg1   : tBuffer : Buffer To Send
// Arg2   : tCount : Number of Bytes To Send
// return : 0 : No ERROR, 0xFF : Overflow ERROR 
uint8_t USART2_TX_INT(uint8_t* tBuffer, uint8_t tCount)
{
  uint8_t counter = 0;
  if(tCount > TX_Buffer_Size)
    return 0xFF;
  TX_NumberofTransfer = tCount;
  TX_Buffer_Pointer = 0;
  for(counter = 0; counter < TX_NumberofTransfer; counter++)
    TX_Buffer[counter] = tBuffer[counter];
  USART2->CR1 |= (1 << 7);              //USART2 TXE INT Enable
  return 0;
}

// brief  : USART2 INT Handler
// Arg1   : None 
// return : None
void USART2_IRQHandler(void)
{
  // RX Interrupt
  if((USART2->SR & (1<<5)) != 0)        // USART RXNE 1 mi??
  {
    RX_Buffer[RX_Buffer_Pointer] = USART2->DR;
    RX_Buffer_Pointer++;
    if( RX_Buffer_Pointer >= RX_Buffer_Size )
      RX_Buffer_Pointer = 0;
  }
  // TXE Interrupt
  if(((USART2->SR & (1<<7)) != 0) &&     // USART TXE 1 mi??
     ((USART2->CR1 & (1<<7)) != 0))      // USART TXEIE 1 mi??
  {
    USART2->DR = TX_Buffer[TX_Buffer_Pointer];
    TX_Buffer_Pointer++;
    if( TX_Buffer_Pointer >= TX_NumberofTransfer )
    {
      TX_Buffer_Pointer = 0;            //        
      TX_NumberofTransfer = 0;          //
      USART2->CR1 &= ~(1 << 7);         //USART2 TXE INT Disable
      USART2->CR1 |= (1 << 6);          //USART2 TC INT Disable
    }  
  }  
  // TC Interrupt
  if(((USART2->SR & (1<<6)) != 0) &&    // USART TC 1 mi??
     ((USART2->CR1 & (1<<6)) != 0))     // USART TCIE 1 mi??
  {
    USART2->CR1 &= ~(1 << 6);           //USART2 TC INT Disable
  } 
}


