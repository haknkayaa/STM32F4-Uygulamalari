#include "stm32f4xx.h"
#include <stdio.h>

int i;
static int a = 0;

void NVIC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void USART1_IRQHandler(void);
void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount);
void usart_rxtx(void);
void delayzz(unsigned long zaman);

int main(void)
{
   SystemInit();
   printf("Starting...\n");
    usart_rxtx();
    while(1)
    {
      printf("OK\n");
      GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
      delayzz(2000000);
      GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
      delayzz(2000000);
      GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
      delayzz(2000000);
      GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
      delayzz(2000000);
    }
}

void delayzz(unsigned long zaman){
   while(zaman > 0 ){
      zaman--;
  }
}

void USART1_IRQHandler(void)
{
   printf("Interrupt\n");
    a++;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) )
    {
        i = USART_ReceiveData(USART1);
        if(i == '1'){
            GPIO_SetBits(GPIOB, GPIO_Pin_8);     
            UARTSend("LED ON\r\n",sizeof("LED ON\r\n"));    
            printf("1\n");
        }
        else if(i == '0'){
            GPIO_ResetBits(GPIOB, GPIO_Pin_8);    
            UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
           printf("0\n");
        }
         else{
               
            UARTSend("Sacma sapan deger\r\n",sizeof("LED OFF\r\n"));
           printf("0\n");
        }
    }
}

void usart_rxtx(void)
{
    const unsigned char welcome_str[] = " Welcome to Bluetooth!\r\n";

    /* Enable USART1 and GPIOA clock */


    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the GPIOs */
    GPIO_Configuration();

    /* Configure the USART1 */
    USART_Configuration();

    
    /* Enable the USART1 Receive interrupt: this interrupt is generated when the
         USART1 receive data register is not empty */
   
    /* print welcome information */
    UARTSend(welcome_str, sizeof(welcome_str));
}


void GPIO_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE); 
   
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct); 
  
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStruct); 

  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7; 
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);               
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
}

void USART_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
       
  USART_InitTypeDef USART_InitStructure;

  USART_InitStructure.USART_BaudRate = 9600;        // Baud Rate
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  
  USART_Cmd(USART1, ENABLE);
  
  
}


void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)
{

    while(ulCount--)
    {
        USART_SendData(USART1, (uint16_t) *pucBuffer++);
        /* Loop until the end of transmission */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
        {
        }
    }
}