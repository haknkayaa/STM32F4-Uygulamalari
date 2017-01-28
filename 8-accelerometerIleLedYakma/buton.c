#include "stm32f411xe.h"
#include "bsp.h"

uint8_t buton_state = 0;
uint8_t buton_old_state = 0;
uint8_t buton_dig_cap = 0;

// brief  : Buton Pins Setup
// Arg1   : None 
// return : None
void buton_setup(void)
{
  // RCC
  PORTA_CLOCK_ON();                     
  //
}

// brief  : buton_oku_task, 1msde bir buton okuma iþlmeleri yapýlýr..
// Arg1   : None 
// return : None
void buton_oku_task(void)
{       
  // Buton Fiziksel okuma (buton_current)
  if(BUTTON_CURRENT() != 0 )
  {
    buton_dig_cap ++;
    if(buton_dig_cap > 20)
      buton_dig_cap = 20;
  }
  else
  {    
    buton_dig_cap --;  
    if(buton_dig_cap > 20)
      buton_dig_cap = 0;
  }
  // Buton digital capacitor kontrol, state deðiþimi
  if(buton_dig_cap > 17)                //TODO make it define
  {
    buton_state = 1;                    // set buton state
  }
  else if(buton_dig_cap < 3)            //TODO make it define
  {
    buton_state = 0;                    // reset buton state
  }

}
