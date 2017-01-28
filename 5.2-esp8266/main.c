#include "stm32f4xx.h"

#define MAX_STRLEN 2 // this is the maximum string length of our string in characters
volatile char gelenVeri[MAX_STRLEN+1]; // this will hold the recieved string

void USART_ESP8266(uint32_t Baudrate);
void USART_Send(USART_TypeDef* USARTx, volatile char *data);

void delay(unsigned long zaman)
{
   while(zaman>0)
   {
    zaman--;
   }
}

int main()
{
  USART_ESP8266(115200); 
  USART_Send(USART1, "AT\r\n");
  
  while (1)
  {  
      // selam
  }
}

void USART_Send(USART_TypeDef* USARTx, volatile char *data)
{
    while(*data)
    {
        while(!(USARTx->SR & 0x00000040));
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
        USART_SendData(USARTx, *data);
        *data++;
    }
}
 


void USART_ESP8266(uint32_t Baudrate)
{
   
  // USART1 kullanilmistir.
  // TX pin: PA9 
  // RX pin: PA10
  
  /* USART Pin */
  GPIO_InitTypeDef GPIO_B;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
    
  GPIO_B.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_B.GPIO_Mode = GPIO_Mode_AF;
  GPIO_B.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_B.GPIO_OType = GPIO_OType_PP;
  GPIO_B.GPIO_PuPd = GPIO_PuPd_UP;
  
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
  
  GPIO_Init(GPIOB, &GPIO_B);
   
  /* USART */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
  
  USART_InitTypeDef USART_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;
   
  USART_InitStruct.USART_BaudRate = Baudrate;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  
  USART_Init(USART1, &USART_InitStruct);
   
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
   

  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

  NVIC_Init(&NVIC_InitStruct);

 
  USART_Cmd(USART1, ENABLE);
}
void USART1_IRQHandler(void){
	
	
	while( USART_GetITStatus(USART1, USART_IT_RXNE))
        {	
		static uint8_t cnt = 0; 
		char dataRegister = USART1->DR; 

		if( (dataRegister != '\n') && (cnt < MAX_STRLEN) ){ 
			gelenVeri[cnt] = dataRegister;
			cnt++;
		}
		else{ 
			cnt = 0;	
		}
	}
}