//***********LED****************
//Pins:Pin28
//Ports:PIOD.P3

#include "X_LED.h"
#include "X_PIO.h"
#include "X_PMC.h"

static char flag = 0;  //flag indicates if led has been initialed, 0 is no, 1 is yes

void initial_LED()
{
   enableClock(PIOA_PIID);
   enablePin(PIOD_PIOS, 3);
   disablePullUp(PIOD_PIOS, 3);
   enableOutput(PIOD_PIOS, 3);
   clearPin(PIOD_PIOS, 3);
   
   enablePin(PIOD_PIOS, 6);
   disablePullUp(PIOD_PIOS, 6);
   enableOutput(PIOD_PIOS, 6);
   clearPin(PIOD_PIOS, 6);
   flag = 1;
}

//turn on key led
void keyLedOn()
{
  if(flag == 0)
  {
    initial_LED();
  }
  setPin(PIOD_PIOS, 3);
}
//turn off key led
void keyLedOff()
{
  if(flag == 0)
  {
    initial_LED();
  }
  clearPin(PIOD_PIOS, 3);
}

//turn on alarm led
void alarmLedOn()
{
  if(flag == 0)
  {
    initial_LED();
  }
  setPin(PIOD_PIOS, 6);
}
//turn off alarm led
void alarmLedOff()
{
  if(flag == 0)
  {
    initial_LED();
  }
  clearPin(PIOD_PIOS, 6);
}