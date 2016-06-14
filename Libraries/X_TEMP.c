#include "X_TEMP.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_NVIC.h"
#include "X_COMMON.h"

#include "..\at91sam3x8.h"

static char flag = 0;//flag indicates if temperature sensor has been initialed, 0 is no, 1 is yes
static unsigned int a;
static unsigned int b;
char temp_ready = 0;//flag indicates if temp value is ready

void initial_temp()
{
  enableClock(PIOB_PIID);
  enableClock(TC0_PIID);
  
  *AT91C_TC0_CMR &= 0xFFFFFFF8; //select TCLK1 as TCCLK
  *AT91C_TC0_CCR = 0x1; // enable clock
  *AT91C_TC0_CCR = 0x1 << 2; // reset and start clock
  
  *AT91C_TC0_CMR |= 0x1 << 17;
  *AT91C_TC0_CMR &= 0xFFFEFFFF; //select Falling for RA
  
  *AT91C_TC0_CMR |= 0x1 << 18;
  *AT91C_TC0_CMR &= 0xFFF7FFFF; //select Rising for RB
  
  enablePin(PIOB_PIOS, 25);
  disablePullUp(PIOB_PIOS, 25);
  
  setNVIC(TC0_IRQn);
  flag = 1;  
}

void request_temp()
{
  if(flag == 0)
  {
    initial_temp();
  }
  temp_ready = 0;
  
  *AT91C_TC0_IER = 0x1 << 6; //enable LDRBS interrupt  
  enableOutput(PIOB_PIOS, 25);
  clearPin(PIOB_PIOS, 25);
  Delay(25); // make a start pulse delay, about 9 ms 
  disableOutput(PIOB_PIOS, 25);     
  *AT91C_TC0_CCR = 0x1 << 2; // reset and start clock
}

float get_temp()
{
  float temp;
  if(b < a)
    return -1;
  temp = ((b - a)/5) * 0.0238095 - 273.15;  
  if(temp < -10 || temp >= 50)
    return -1;
  temp_ready = 0;
  return temp;
}

void TC0_Handler(void)
{  
  *AT91C_TC0_IDR = 0x1 << 6; //disable LDRBS interrupt
  b = *AT91C_TC0_RB;
  a = *AT91C_TC0_RA;
  temp_ready = 1;
}