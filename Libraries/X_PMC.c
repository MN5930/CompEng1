#include "X_PMC.h"
#include "..\at91sam3x8.h"

//enable clock
void enableClock(PIID_TYPE piid)
{
  if(piid >= 0 && piid <= 31)
  {
    *AT91C_PMC_PCER = 0x1 << piid;
  }else if(piid >= 32 && piid <=44)
  {
    *AT91C_PMC_PCER1 = 0x1 << (piid - 32);
  }
}

//disable clock
void disableClock(PIID_TYPE piid)
{
  if(piid >= 0 && piid <= 31)
  {
    *AT91C_PMC_PCDR = 0x1 << piid;
  }else if(piid >= 32 && piid <=44)
  {
    *AT91C_PMC_PCDR1 = 0x1 << (piid - 32);
  }
}