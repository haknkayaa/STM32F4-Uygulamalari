/*
** Karasimsek - Stm32f411
** @author: Hakan Kaya
** @date : 2.11.2016
** @mail : mail@hakankaya.kim
*/

#include "stm32f4xx.h"

void GPIO_Ayarlari();
void delay(unsigned long zaman);



int main()
{
  GPIO_Ayarlari();

  uint16_t pin = 0x1000; 
  
  while(1){ 
    GPIO_ToggleBits(GPIOD, pin);
    pin = pin << 1;
    delay(2000000);
    if(pin == 0x0) pin = 0x1000;
  } 
}

void GPIO_Ayarlari(){
 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef GPIO_D;

  GPIO_StructInit(&GPIO_D);

  GPIO_Init(GPIOD, &GPIO_D);

}

void delay(unsigned long zaman){
   while(zaman > 0){
      zaman--;
   }
}
