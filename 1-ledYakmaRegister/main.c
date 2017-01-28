/*
** Led Blinking - Stm32f411
** @author: Hakan Kaya
** @date : 2.11.2016
*/
 
 
// Adres Tanımlamaları
#define RCC_AHBENR *((unsigned int*)0x40023830U) 
#define GPIOD_BASE *((unsigned int*)0x40020C00U)
 
#define GPIOD_MODER *((unsigned int*)0x40020C00U)
#define GPIOD_OTYPER *((unsigned int*)0x40020C04U)
#define GPIOD_OSPEEDR *((unsigned int*)0x40020C08U)
#define GPIOD_PUPDR *((unsigned int*)0x40020C0CU)
#define GPIOD_ODR *((unsigned int*)0x40020C14U)
 
// Gecikme için zaman fonksiyonu
void delayzz(unsigned long zaman){  // İsaretsiz arguman girisi
 while(zaman > 0){                   // Koşullu döngü
 zaman--;                             // Her defasında bir azalt
 }
}
 
int main(void)
{
 RCC_AHBENR = 0x00000008;  // AHB1 Enable Register D portu için aktif
  
 GPIOD_MODER = 0x55000000;  // Pin modu tanimlamasi
  
  
 GPIOD_OTYPER = 0x0U;  // Cikis tipi tanımlamasi (push-pull/reset state)
  
 GPIOD_OSPEEDR = 0x0U;  // Cikis hizi tanımlaması (Low speed)
  
 GPIOD_PUPDR = 0x0U;   // Non pull-up-pull-down
  
 while(1){              // Sonsuz döngü
 GPIOD_ODR = 0xF000U;   // Lojik-1
 delayzz(2000000);   // Bekle
 GPIOD_ODR = 0x0000U;  // Lojik-0
 delayzz(2000000);  // Bekle
 }
 return 0; 
}
