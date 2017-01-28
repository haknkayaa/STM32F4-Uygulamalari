/*******************************************************************************
* STM32F4 - Kullanici Butonu ile LED Kontrol
* ------------------------------------------------------------------------------
* @author  : Hakan Kaya
* @mail    : mail@hakankaya.kim
* @date    : 18.12.2016
* @brief   : Kart uzerinde bulunan USER butonuyla ledleri yakip söndürmek
* 
*******************************************************************************/

// Kütüphaneler
#include "stm32f4xx.h"

// Fonksiyon prototipleri
void GPIO_Hazirliklari(void);

// Main fonksiyonu
int main(void) {

   // GPIO islemlerinin oldugu fonksiyonun cagrilmasi
   GPIO_Hazirliklari();
   
   // Sonsuz dongu
    while (1) {
       
       // Okuma islemi
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
            GPIO_SetBits(GPIOD, GPIO_Pin_All);
        } else {
            GPIO_ResetBits(GPIOD, GPIO_Pin_All);
        }
    }
    
    //return 0;
}
void GPIO_Hazirliklari(void){
   
    // A ve D portu icin RCC aktiflestirme
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOA, ENABLE);
    
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
      
    // A portu icin nesne tanimlanmasi
    GPIO_InitTypeDef GPIO_A;
    
    // A Portu ayarlamalarý
    GPIO_A.GPIO_Pin = GPIO_Pin_0;
    GPIO_A.GPIO_Mode = GPIO_Mode_IN;
    GPIO_A.GPIO_OType = GPIO_OType_PP;
    GPIO_A.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_A.GPIO_Speed = GPIO_Speed_100MHz;

    // Vektorun tanimlanmasi
    GPIO_Init(GPIOA, &GPIO_A);
   
}