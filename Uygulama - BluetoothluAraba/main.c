#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <stdio.h>
#include "main.h"

void delayzz(unsigned long zaman){
   while(zaman > 0 ){
      zaman--;
  }
}

int main()
{
  SystemInit (); 
  SystemCoreClockUpdate();
  SysTick_Config (SystemCoreClock/1000); 
  
  STM_EVAL_LEDInit(LED6);
 
  GPIO_Hazirliklari();
  FAR(1);
  STM_EVAL_LEDToggle(LED6); 
  usart_rxtx();
  
  while(1){
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

void GPIO_Hazirliklari(void){
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef GPIO_InitStruct; 

  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    
  GPIO_Init(GPIOA, &GPIO_InitStruct);  
  
  GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    
  GPIO_Init(GPIOC, &GPIO_InitStruct);  
 

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


void FAR(unsigned char durum){
   if(durum == 0){ // Kapalý
      GPIO_ResetBits(GPIOC, GPIO_Pin_6);
      GPIO_ResetBits(GPIOC, GPIO_Pin_7);
   }
   else if (durum == 1){ // Sürekli açýk
      GPIO_SetBits(GPIOC, GPIO_Pin_6);
      GPIO_SetBits(GPIOC, GPIO_Pin_7);     
   }
   else if(durum == 2){ // Blinking
      GPIO_ResetBits(GPIOC, GPIO_Pin_6);
      GPIO_ResetBits(GPIOC, GPIO_Pin_7);
   }
   else{ // Açýk
      GPIO_SetBits(GPIOC, GPIO_Pin_6);
      GPIO_SetBits(GPIOC, GPIO_Pin_7); 
   }
}

void ileri(){   
      // ileri
     
      GPIO_SetBits(  GPIOA, EN1);
      GPIO_SetBits(  GPIOA, IN1);
      GPIO_ResetBits(GPIOA, IN2);             
   }
void geri(){
      // geri
      
      GPIO_SetBits(  GPIOA, EN1);
      GPIO_SetBits(  GPIOA, IN2);
      GPIO_ResetBits(GPIOA, IN1); 
}

void stop(){
      // stop
      GPIO_ResetBits(GPIOA, EN1);
      GPIO_ResetBits(GPIOA, IN2);
      GPIO_ResetBits(GPIOA, IN1);    
}
void sag(){
    
   if(duzDogruluk == 0 || duzDogruluk == 1){
      GPIO_SetBits(  GPIOA, EN2);
      GPIO_SetBits(  GPIOA, IN4);
      GPIO_ResetBits(GPIOA, IN3);
      duzDogruluk = 2;
      
     
   }
}

void sol(){
     
   if(duzDogruluk == 1 || duzDogruluk == 2){
      GPIO_SetBits(  GPIOA, EN2);
      GPIO_SetBits(  GPIOA, IN3);
      GPIO_ResetBits(GPIOA, IN4); 
      duzDogruluk = 0;
      
     
   }
}
void duz(){
    duzDogruluk = 1;
    GPIO_ResetBits(GPIOA, EN2);
    GPIO_SetBits(GPIOA, IN3);
    GPIO_ResetBits(GPIOA, IN4);

}
void Delay(__IO uint32_t time)
{
  TimmingDelay = time;
  STM_EVAL_LEDToggle(LED6);
  while(TimmingDelay !=0);
}

void USART1_IRQHandler(void)
{
   
    a++;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) )
    {
        i = USART_ReceiveData(USART1);
        if(i == 0x30){
            stop();   
            duz();
            UARTSend("stop\r\n",sizeof("LED ON\r\n"));
            
            
        }
        else if(i == 0x31){
            GPIO_ResetBits(GPIOB, GPIO_Pin_8);    
            UARTSend("LED OFF\r\n",sizeof("LED OFF\r\n"));
           
        }
         else if(i == 0x32){
            ileri();    
            UARTSend("ileri\r\n",sizeof("LED OFF\r\n"));
           
        }
        else if(i == 0x33){
            geri();    
            UARTSend("geri\r\n",sizeof("LED OFF\r\n"));
           
        }
         else if(i == 0x34){
            sag();   
            UARTSend("sag\r\n",sizeof("LED OFF\r\n"));
           
        }
         else if(i == 0x35){
            sol();    
            UARTSend("sol\r\n",sizeof("LED OFF\r\n"));
           
        } 
         else if(i == 0x36){
            FAR(1);    
            UARTSend("far acik\r\n",sizeof("LED OFF\r\n"));
           
        }
         else if(i == 0x37){
            FAR(0);    
            UARTSend("kapali\r\n",sizeof("LED OFF\r\n"));
          
        }
         else if(i == 0x38){
            ileri();    
            UARTSend("7\r\n",sizeof("LED OFF\r\n"));
           
        }        
         else{
               
            UARTSend("Sacma sapan deger\r\n",sizeof("LED OFF\r\n"));
           
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
    GPIO_Hazirliklari();

    /* Configure the USART1 */
    USART_Configuration();

    
   
    /* print welcome information */
    UARTSend(welcome_str, sizeof(welcome_str));
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