#include "stm32f4xx.h"
//#include "stm32f4xx_rcc.h"
//#include "stm32f4xx_gpio.h"

void GPIO_Hazirliklari(void);

int main(void) {

   GPIO_Hazirliklari();
   
    while (1) {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            GPIO_SetBits(GPIOD, GPIO_Pin_All);
        } else {
            GPIO_ResetBits(GPIOD, GPIO_Pin_All);
        }
    }
    
    //return 0;
}
void GPIO_Hazirliklari(void){
   
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_D;
    
    GPIO_D.GPIO_Pin = GPIO_Pin_All; 
    GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_D.GPIO_OType = GPIO_OType_PP;
    GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_D.GPIO_Speed = GPIO_Speed_100MHz;
    
    GPIO_Init(GPIOD, &GPIO_D);

    GPIO_InitTypeDef GPIO_A;
    // A Pini
    GPIO_A.GPIO_Pin = GPIO_Pin_0;
    GPIO_A.GPIO_Mode = GPIO_Mode_IN;
    GPIO_A.GPIO_OType = GPIO_OType_PP;
    GPIO_A.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_A.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_Init(GPIOA, &GPIO_A);
   
}