#include "X_PHOTO.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_NVIC.h"
#include "X_COMMON.h"

#include "..\at91sam3x8.h"

static char flag = 0;//flag indicates if photo sensor has been initialed, 0 is no, 1 is yes

static unsigned int photo1 = 0;//store result for channel 1
static unsigned int photo2 = 0;//store result for channel 2


void initial_photo()
{
  enableClock(PIOA_PIID);
  enableClock(ADC_PIID);
  
  *AT91C_ADCC_MR &= 0xFFFF00FF; // PRESCAL assigned 2
  *AT91C_ADCC_MR |= 0x1 << 9 ; // PRESCAL assigned 2 
  
  setNVIC(ADC_IRQn);
  flag = 1;
}

void get_value(char device)
{
 if(device == 1)
  {
    //disablePin(PIOA_PIOS, 4);//Disable Sensor 1
    enablePin(PIOA_PIOS, 3);//Enable Sensor 2
    
    //*AT91C_ADCC_CHDR = 0x1 << 2;
    *AT91C_ADCC_CHER = 0x1 << 1 ; // chanell 1 analog 6
  }
  if(device == 2)
  {
    //disablePin(PIOA_PIOS, 3);//Disable Sensor2
    enablePin(PIOA_PIOS, 4);//Enable Sensor1
    
    //*AT91C_ADCC_CHDR = 0x1 << 1;
    *AT91C_ADCC_CHER = 0x1 << 2 ; // chanell 2 analog 5 
  }
  
  *AT91C_ADCC_CR = 0x2 ; // Start an ADC in ADC_CR
  Delay(10000);
  *AT91C_ADCC_IER = 0x1 << 24; //enable interrupt
}

void getPhoto(unsigned int * first, unsigned int * second)
{
  
  if(flag == 0)
  {
    initial_photo();
  }
  
  get_value(1);
  do
  {
    *first = photo1;    
  }while(*first == 0);
  photo1 = 0;
  
  get_value(2);
  do
  {
    *second = photo2;
  }while(*second == 0);  
  photo2 = 0;
  
}

void ADC_Handler(void)
{
  *AT91C_ADCC_IDR = 0x1 << 24;  
  photo1 = (*AT91C_ADCC_CDR1) & 0xFFF;
  photo2 = (*AT91C_ADCC_CDR2) & 0xFFF;
  
}
