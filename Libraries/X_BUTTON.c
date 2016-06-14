#include "X_BUTTON.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_NVIC.h"

#include "..\at91sam3x8.h"

void initial_BUTTON();

static int piod_interrupt = 0; 

static char flag = 0;//flag indicates if button has been initialed, 0 is no, 1 is yes

char getButtonValue()
{
  if(flag == 0)
  {
    initial_BUTTON();
  }
  if(piod_interrupt & 0x2)
  {
    piod_interrupt = 0;
    return 1;    
  }
  else
  {
    return 0;
  }
}

void initial_BUTTON()
{
  enableClock(PIOD_PIID);
  enablePin(PIOD_PIOS, 1);

  //enable interrupt 
  *((volatile unsigned int *)0x400E14B0) = 0x2; 
  *AT91C_PIOD_IFER = 0x2; 
  *((volatile unsigned int *)0x400E1484) = 0x2; 
  //change 
  *((volatile unsigned int *)0x400E148C) = 0x1<<5; 
    
  *AT91C_PIOD_ISR & 0x2; 
  
  setNVIC(PIOD_IRQn);
  
  *AT91C_PIOD_PER = 0x2; 
  *AT91C_PIOD_IER = 0x2; 
  
  flag = 1;
}

void PIOD_Handler(void) 
{ 
  piod_interrupt = *AT91C_PIOD_ISR; 
} 