#include "X_RTC.h"
#include "X_NVIC.h"
#include "..\at91sam3x8.h" 
#include "..\system_sam3x.h" 

char second, minute, hour;
char centery, year, month, date, day;
char isSecond = 0;
char isMinute = 0;
char isWeek = 0;
static unsigned int status;


void initial_RTC()
{
  *AT91C_RTC_MR = 0x00; //set 24-hour mode
  *AT91C_RTC_CR = 0x00000000; //select minute and week time event
  enableSecondEvent(); // enable second event interrupt
  //enableTimeEvent(); // enable time event interrupt
  enableCalendar(); // enable calendar event interrupt
  
  setNVIC(RTC_IRQn);
}

void getTime()
{
  unsigned int reg;
  reg = *AT91C_RTC_TIMR;
  second = reg & 0x7F;
  second = (second & 0xF) + ((second & 0x70) >> 4) * 10;
  minute = (reg & 0x7F00) >> 8;
  minute = (minute & 0xF) + ((minute & 0x70) >> 4) * 10;
  hour = (reg & 0x3F0000) >> 16;
  hour = (hour & 0xF) + ((hour & 0x30) >> 4) * 10;
  
  reg = *AT91C_RTC_CALR;
  day = (reg & 0x00E00000) >> 21;
}

void getRTCStatus()
{
  if(status & (0x1 << 2))
  {
    isSecond = 1;
  }
  if(status & (0x1 << 3))
  {
    isMinute = 1;
  }
  if(status & (0x1 << 4))
  {
    isWeek = 1;
  }
  status = 0;
}

void enableSecondEvent()
{
  *AT91C_RTC_IER = 0x01 << 2;
}

void enableTimeEvent()
{
  *AT91C_RTC_IER = 0x01 << 3;
}

void enableCalendar()
{
  *AT91C_RTC_IER = 0x01 << 4;
}

void disableSecondEvent()
{
  *AT91C_RTC_IDR = 0x01 << 2;
}

void disableTimeEvent()
{
  *AT91C_RTC_IDR = 0x01 << 3;
}

void disableCalendar()
{
  *AT91C_RTC_IDR = 0x01 << 4;
}

void RTC_Handler(void)
{  
  status = *AT91C_RTC_SR; //read event status
  
  *AT91C_RTC_SCCR = 0x01 << 2; //clear second event status
  *AT91C_RTC_SCCR = 0x01 << 3; //clear time event status
  *AT91C_RTC_SCCR = 0x01 << 4; //clear calendar event status
}