#ifndef __BUTON_H
#define __BUTON_H

// brief  : Buton Pins Setup
// Arg1   : None 
// return : None
void buton_setup(void);


// brief  : buton_oku_task, 1msde bir buton okuma iþlmeleri yapýlýr..
// Arg1   : None 
// return : None
void buton_oku_task(void);

extern uint8_t buton_state;
extern uint8_t buton_old_state;

#endif