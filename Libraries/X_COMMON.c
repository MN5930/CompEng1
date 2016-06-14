#include "X_COMMON.h"
#include "..\system_sam3x.h"

static int global = 0;

void Delay(int value)
{ 
  int i; 
  for(i = 0; i<value;i++) 
  { 
    asm("nop"); 
  } 
} 

void startSysTick(int value)
{
  SysTick_Config(value);
}

void SysTick_Handler(void)
{
  global++;
}