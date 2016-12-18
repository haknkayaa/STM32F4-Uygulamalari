/*******************************************************************************
* STM32F4 - LED Yakip Sondurma
* ------------------------------------------------------------------------------
* @author  : Hakan Kaya
* @mail    : mail@hakankaya.kim
* @date    : 18.12.2016
* @brief   : Kart uzerinde bulunan ledleri yakip söndürmek
* 
*******************************************************************************/

// Kütüphaneler
#include "stm32f4xx.h"
//#include "stm32f4xx_rcc.h"    // system_conf.h icerisinden cagrildi
//#include "stm32f4xx_gpio.h"   // system_conf.h icerisinden cagrildi

// Fonksiyon prototipleri
void canimDelayim(unsigned long zaman);
void GPIO_Hazirliklari(void);

// Main fonksiyonu
int main(void) {

   // GPIO islemlerinin oldugu fonksiyonun cagrilmasi
   GPIO_Hazirliklari();
   
   // Sonsuz dongu
    while (1) {
       
       
        GPIO_SetBits(GPIOD, GPIO_Pin_All);
        canimDelayim(2000000);
        GPIO_ResetBits(GPIOD, GPIO_Pin_All);
        canimDelayim(2000000);
    }
    
    //return 0;
}

void canimDelayim(unsigned long zaman){
  while(zaman > 0){
    zaman--;
  }
}


void GPIO_Hazirliklari(void){
   
    // A ve D portu icin RCC aktiflestirme
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);
    
    // D portu icin pointer vektoru tanımlanması
    GPIO_InitTypeDef GPIO_D;
    
    // Port ayarlamalari
    GPIO_D.GPIO_Pin = GPIO_Pin_All; 
    GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_D.GPIO_OType = GPIO_OType_PP;
    GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_D.GPIO_Speed = GPIO_Speed_100MHz;
    
    // Vektorun tanimlanmasi
    GPIO_Init(GPIOD, &GPIO_D);
      
    // A portu icin nesne tanimlanmasi
    GPIO_InitTypeDef GPIO_A;
    
    // A Portu ayarlamaları
    GPIO_A.GPIO_Pin = GPIO_Pin_0;
    GPIO_A.GPIO_Mode = GPIO_Mode_IN;
    GPIO_A.GPIO_OType = GPIO_OType_PP;
    GPIO_A.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_A.GPIO_Speed = GPIO_Speed_100MHz;

    // Vektorun tanimlanmasi
    GPIO_Init(GPIOA, &GPIO_A);
   
}
