/*******************************************************************************
* STM32F4 - USART Haberlesmesi (Kesme ile)
* ------------------------------------------------------------------------------
* @author  : Hakan Kaya
* @mail    : mail@hakankaya.kim
* @date    : 23.12.2016
* @brief   : USART1 haberlesmesiyle seri porttan veri okuma-yazma
*******************************************************************************/

#include "stm32f4xx.h"
#include <stdio.h>

// Degiskenler
#define MAX_STRLEN 10 
volatile char received_string[MAX_STRLEN + 1]; 

// Fonksiyon prototipleri
void init_USART1(uint32_t baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);

int main(void) {

  init_USART1(9600); 

  USART_puts(USART1, "STM32F4'den merhaba!\r\n"); 

  
  while (1){  
   
      // calismasini istediginiz fonksiyonlari 
      // buraya yazabilirsiniz...
     
  }
}

void init_USART1(uint32_t baudrate){
	               
        /*  RX-TX pinlerinin ayarlamalari */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);                   // GPIOB icin clock bus'ý aktif etme
        
	GPIO_InitTypeDef GPIO_InitStruct;                                       // Pointer tanimlamasi
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;                     // Pins 6 (TX) and 7 (RX) are used
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			        // Alternatif fonksiyon modunun acilmasi
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		                // 50 mHz hýz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			        // Push Pull
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			        // Up
	GPIO_Init(GPIOB, &GPIO_InitStruct);				        // Pointer yönlendirmesi
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);               // Pin 6 icin AF ayarlanmasi
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);               // Pin 7 icin AF ayarlanmasi

	
        /*  USART ayarlari */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                  // USART icin clock bus'ý aktif etme
        
        USART_InitTypeDef USART_InitStruct;                                     // Pointer tanimlamasi
        
	USART_InitStruct.USART_BaudRate = baudrate;			        // Baudrate
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;                // Veri uzunlugu
	USART_InitStruct.USART_StopBits = USART_StopBits_1;	                // STOP bit
	USART_InitStruct.USART_Parity = USART_Parity_No;		        // Parity
	USART_InitStruct.USART_HardwareFlowControl = 
           USART_HardwareFlowControl_None;                                      // Flow Control
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;            // Alici-verici mode
	USART_Init(USART1, &USART_InitStruct);					// Pointer yonlendirmesi
	
        /* Interrupt ayarlamalari */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                          // Interrupt acilmasi
	
        NVIC_InitTypeDef NVIC_InitStructure;                                    // Pointer tanimlanmasi
        
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		        // 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;               //
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	                //
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			        // 
	NVIC_Init(&NVIC_InitStructure);						// Pointer yonlendirmesi	 

	USART_Cmd(USART1, ENABLE);                                              // USART aktif
}


void USART_puts(USART_TypeDef* USARTx, volatile char *s){

	while(*s){
		while( !(USARTx->SR & 0x00000040) ); 
                while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USARTx, *s);
		*s++;
	}
}


void USART1_IRQHandler(void){
	
	
	if( USART_GetITStatus(USART1, USART_IT_RXNE) ){
           
		printf("Interrupta girildi. Veri okundu\n");
		static int cnt = 0; 
		char t = USART1->DR; 
		
		if( (t != '\n') && (cnt < MAX_STRLEN) ){ 
			received_string[cnt] = t;
			cnt++;                        
		}
                
		else{ 
                        received_string[cnt] = '\0';
                        cnt = 0;
                        USART_puts(USART1, received_string);
                        printf("Veri yollandý\n");
			
		}
                
	}
}
