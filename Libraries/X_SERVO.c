#include "X_SERVO.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_COMMON.h"

#include "..\at91sam3x8.h"

static char flag = 0;//flag indicates if servo has been initialed, 0 is no, 1 is yes

void initial_Servo()
{
  //enable clock for PWM 
  enableClock(PWM_PIID);
  
	//Let peripheral control the pin17 // Disable the pin
  disablePin(PIOB_PIOS, 17);
  
  selectAB(PIOB_PIOS, 17, 1);
  //select peripheral B function for pin17
  
  *AT91C_PWMC_ENA = 0x1 << 1; // Enable PWM-channel in ENA_CHID1
  
  
  *AT91C_PWMC_CH1_CMR &= 0xFFFFFFF5;
  *AT91C_PWMC_CH1_CMR |= 0x5; //select MCK_32
  
  *AT91C_PWMC_CH1_CMR &= 0xFFFFFDFF; // make CPOL 0
  //*AT91C_PWMC_CH1_CMR |= 0x1 << 9; // make CPOL 0
    
  *AT91C_PWMC_CH1_CPRDR = 0xCD14; //give 20ms
  //*AT91C_PWMC_CH1_CPRDR = 0x501BD0;
  *AT91C_PWMC_CH1_CDTYR = NUETRAL_POSITION;  //give 1ms idle
   Delay(100000);
   flag = 1;
}

//move servo , 1 is left , 2 is right
float moveServo(int value)
{
  if(flag == 0)
  {
    initial_Servo();
  }
  unsigned int a;
  a = *AT91C_PWMC_CH1_CDTYR;
  
  if(value == 1 && (a + INTERVAL)<= LEFT_POSITION)
  {   
    a += INTERVAL;  //left    
  }else if(value == 2 && (a - INTERVAL)>= RIGHT_POSITION)
  {      
    a -= INTERVAL;  //right
  }
  *AT91C_PWMC_CH1_CDTYR = a;
  return (180 - (((a - RIGHT_POSITION) * 180 ) / (float)(LEFT_POSITION - RIGHT_POSITION)));
}