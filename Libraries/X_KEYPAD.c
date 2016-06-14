#include "X_KEYPAD.h"
#include "X_PMC.h"
#include "X_PIO.h"

#include "..\at91sam3x8.h"

void initial_KEYPAD();

static char flag = 0;//flag indicates if keypad has been initialed, 0 is no, 1 is yes

//read keyboard
void read_keyboard(int *value)
{ 
  if(flag == 0)
  {
    initial_KEYPAD();
  }
  clearPin(PIOD_PIOS, 2);
  int ii, jj;
  int rows[4]={2,3,4,1};
  int cols[3]={3,1,2};
  *value = -1;
  *AT91C_PIOC_OER = 0x380;//enable PC7,8,9 as output
  *AT91C_PIOC_SODR = 0x380;//set all col (PC7,8,9) to high
  for(ii = 7; ii < 10; ii++)
  {
    
    *AT91C_PIOC_CODR = 0x1<<ii;//clear one col each time
    for(jj = 2; jj < 6; jj++)
    {
      if(((*AT91C_PIOC_PDSR)&(0x1<<jj)) == 0)
      {
          *value=(rows[jj-2]-1)*3+cols[ii-7];
          //break;
      }
    }    
    *AT91C_PIOC_SODR = 0x1<<ii;    
    if(*value>0)
    {
      break;
    }
   // *AT91C_PIOC_PPUDR =0x380; //Disable the pull up for all col(PC7,8,9)
  }
  *AT91C_PIOC_ODR = 0x380;//make PC7,8,9 as input
  setPin(PIOD_PIOS, 2);
}

void initial_KEYPAD()
{
  enableClock(PIOD_PIID);
  enablePin(PIOD_PIOS, 2);
 //  *AT91C_PIOD_PER = 0xE ;   //enable the botton 26 ,27 and 28
  enablePin(PIOC_PIOS, 2);
  enablePin(PIOC_PIOS, 3);
  enablePin(PIOC_PIOS, 4);
  enablePin(PIOC_PIOS, 5);
  enablePin(PIOC_PIOS, 7);
  enablePin(PIOC_PIOS, 8);
  enablePin(PIOC_PIOS, 9);
  
  disablePullUp(PIOD_PIOS, 2);
  enableOutput(PIOD_PIOS, 2);
  
  disablePullUp(PIOC_PIOS, 7);
  disablePullUp(PIOC_PIOS, 8);
  disablePullUp(PIOC_PIOS, 9);
  
  //clear G to 0
  
  
  flag = 1;
}