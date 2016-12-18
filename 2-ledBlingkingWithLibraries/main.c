/*******************************************************************************
* STM32F4 - LED Yakip Sondurma
* ------------------------------------------------------------------------------
* @author  : Hakan Kaya
* @mail    : mail@hakankaya.kim
* @date    : 18.12.2016
<<<<<<< HEAD
* @brief   : Kart uzerinde bulunan ledleri yakip söndürmek
* 
*******************************************************************************/

// Kütüphaneler
=======
* @brief   : Kart uzerinde bulunan ledleri yakip sÃ¶ndÃ¼rmek
* 
*******************************************************************************/

// KÃ¼tÃ¼phaneler
>>>>>>> origin/master
#include "stm32f4xx.h"
//#include "stm32f4xx_rcc.h"    // system_conf.h icerisinden cagrildi
//#include "stm32f4xx_gpio.h"   // system_conf.h icerisinden cagrildi

// Fonksiyon prototipleri
void canimDelayim(unsigned long zaman);
void GPIO_Hazirliklari(void);
<<<<<<< HEAD

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
=======

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
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    // D portu icin pointer vektoru tanÄ±mlanmasÄ±
    GPIO_InitTypeDef GPIO_D;
    
    // Port ayarlamalari
    GPIO_D.GPIO_Pin = GPIO_Pin_All; 
    GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_D.GPIO_OType = GPIO_OType_PP;
    GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_D.GPIO_Speed = GPIO_Speed_100MHz;
    
    // Vektorun tanimlanmasi
    GPIO_Init(GPIOD, &GPIO_D);
    
   
>>>>>>> origin/master
}

void canimDelayim(unsigned long zaman){
  while(zaman > 0){
    zaman--;
  }
}


void GPIO_Hazirliklari(void){   
    // D portu icin RCC aktiflestirme
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    // D portu icin pointer vektoru tanýmlanmasý
    GPIO_InitTypeDef GPIO_D;
    
    // Port ayarlamalari
    GPIO_D.GPIO_Pin = GPIO_Pin_All; 
    GPIO_D.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_D.GPIO_OType = GPIO_OType_PP;
    GPIO_D.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_D.GPIO_Speed = GPIO_Speed_100MHz;
    
    // Vektorun tanimlanmasi
    GPIO_Init(GPIOD, &GPIO_D);
    
   
}