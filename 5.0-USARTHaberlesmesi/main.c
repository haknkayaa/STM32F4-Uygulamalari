#include "stm32f4xx.h"

void USART1_Setup(void);
void USART1_Send(char* data);


int main(void){
    
    USART1_Setup();
 
    USART1_Send("Hello World!\r\n");
    
    while(1){
       
        /* Buraya yapilmasini istediginiz
          baska kodlar yazabilirsiniz */
    }  
}

// USART 1 Kurulum Fonksiyonu
// TX: PB6
// RX: PB7
void USART1_Setup(void){
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  
    
    GPIO_InitTypeDef GPIO_InitStructure;                   

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);  
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1); 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;           
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      
    
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   

    
    
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  
    USART_Init(USART1, &USART_InitStructure);

    

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                         
	
    NVIC_InitTypeDef NVIC_InitStructure;                                
        
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		        
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;               
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	                
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
    
    NVIC_Init(&NVIC_InitStructure); 
    
    USART_Cmd(USART1, ENABLE);
}

void USART1_Send(char* data){
    while(*data) {
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, *data);
        data++;
    }
}

void USART1_IRQHandler(void){ 
    // Okunan data registerý bos ise
    // yani herhangi veri gelmediyse bekle 
    // RXNE: RX data register not empty 
    while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET); 
    
    // Data registeri dolu ise okunan veriyi gelenVeri'ye kaydet 
    char gelenVeri = USART_ReceiveData(USART1); 
       
    // Gelen veriyi ekrana basmak icin
    // Yollanan data registerin bos olup olmamasini denetle
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, gelenVeri);
}
