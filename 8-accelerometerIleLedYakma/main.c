#include "stm32f411xe.h"
#include "lsm303dlhc.h"
#include <stdio.h>
#define SYS_CLOCK       168000000
#define GPIOD_MODER     *((unsigned int *)0x40020C00)
#define GPIOD_ODR       *((unsigned int *)0x40020C14)
#define RCC_AHB1ENR     *((unsigned int *)0x40023830)


static int16_t data[3];


int main(){

  RCC_AHB1ENR   = 0x00000008;   // Open GPIOD Clock
  GPIOD_MODER   = 0x55000000;   
  
  NVIC_SetPriorityGrouping(7);          
  SysTick_Config(SYS_CLOCK / 1000);     
 
  
  LSM303DLHC_AccInit(0);

  /*
  if ( 1 == L3GD20_ReadID() )
    //USART2_TX_INT((uint8_t *)GYRO_FOUND_MSG, sizeof(GYRO_FOUND_MSG));
  else
    USART2_TX_INT((uint8_t *)GYRO_NOT_FOUND_MSG, sizeof(GYRO_NOT_FOUND_MSG));
  
  if( LSM303DLHC_AccReadID() == I_AM_LMS303DLHC)
    USART2_TX_INT((uint8_t *)ACC_FOUND_MSG, sizeof(ACC_FOUND_MSG));
  else
    USART2_TX_INT((uint8_t *)ACC_NOT_FOUND_MSG, sizeof(ACC_NOT_FOUND_MSG));
  // LOOP
  
  */
  
  
  while(1){
    LSM303DLHC_AccReadXYZ(data);
    
    // kablo bize donuk kablo tarafý aþaðýda
    if(data[0] < -150){
       //printf("kablo bize donuk kablo tarafi asagida\n");
       GPIOD_ODR   = 0x00008000; 
       
    }
    
    // kablo bize donuk kablo tarafý yukarýda
    else if(data[0] > 150){
       //printf("kablo bize donuk kablo tarafi yukarida\n");
       GPIOD_ODR   = 0x00002000;
    }
    
    // kablo bize donuk sola yatýk
    else if(data[1] > 300){
       //printf("kablo bize donuk sola yatik\n");
       GPIOD_ODR   = 0x00001000;
    }
    
    // kablo bize donuk saða yatýk
    else if(data[1] < -300){
       //printf("kablo bize donuk saga yatik\n");
       GPIOD_ODR   = 0x00004000;
    }
    
    // diðer olasýklar - düz
    else{
       //printf("Duz\n");
       GPIOD_ODR   = 0x00000000;
    }
  
  }
  
}

void SysTick_Handler(void){ 
  

  
}




