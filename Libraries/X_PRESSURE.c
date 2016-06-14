#include "X_PRESSURE.h"
#include "X_PMC.h"
#include "X_PIO.h"
#include "X_COMMON.h"

#include "..\at91sam3x8.h"

char pressure_error = 0;

void initial_AIR();
void transmitData(unsigned char data, unsigned char address);
unsigned char readData(unsigned char address);

static char flag = 0;//flag indicates if pressure sensor has been initialed, 0 is no, 1 is yes

float getPressure()
{ 
  if(flag == 0)
    initial_AIR();
  unsigned char status;
  unsigned char P_MSB, P_CSB, P_LSB;
  unsigned char reg1Data = readData(0x26);  //read control register
  reg1Data &= 0xFE;
  transmitData(reg1Data, 0x26); //set mode to standby

  reg1Data |= 0x38;
  transmitData(reg1Data, 0x26);//set OSR to 128

  reg1Data &= 0x7F;
  transmitData(reg1Data, 0x26); //set to Altimeter mode
  transmitData(0x07, 0x13); //event enable  
    
  reg1Data |= 0x01;
  transmitData(reg1Data, 0x26); //set to Active mode  
  if(pressure_error == 1)
    return -1;
  /*
  int ii;
  for(ii = 0; ii < 100; ii++)
  {
    status = readData(0x00);
    if((status & 0x0C) == 0x0C)
      break;
  }
  if(ii >= 100 || pressure_error == 1)
    return -1;
  */
  do
  {
    status = readData(0x00);
  }
  while((status & 0x0C) != 0x0C);
  
  float value = 0;
  P_MSB = readData(0x01);
  P_CSB = readData(0x02);
  P_LSB = readData(0x03);
  value = (P_LSB >> 6) + P_CSB * 0x04 + P_MSB * 0x400 + ((P_LSB & 0x10) >> 4) * 0.5 + ((P_LSB & 0x20) >> 5) * 0.25;
  
  transmitData(reg1Data & 0xFE, 0x26); //set mode to standby
  return value;
}

void transmitData(unsigned char data, unsigned char address)
{
  int ii;
  *AT91C_TWI0_CR = 0x24;
  *AT91C_TWI0_MMR = 0x00600100;//set slave adress to 0xC0, write direction, 1 byte internal address
  *AT91C_TWI0_IADR = address; //set internal address
  *AT91C_TWI0_THR = data; //write data to THR    
  
  //check if the data is transmitted
  /*
  for(ii = 0; ii < 10000; ii++)
  {
    if((*AT91C_TWI0_SR) & (0x1 << 2))
      break;
  }  
  *AT91C_TWI0_CR = 0x1 << 1;//stop signal
  if(ii >= 10000)
  {
    pressure_error = 1;
    return;
  }
  for(ii = 0; ii < 10000; ii++)
  {
    if((*AT91C_TWI0_SR) & 0x1)
      break;
  }  
  *AT91C_TWI0_CR = 0x1 << 3;//disable master mode
  if(ii >= 10000)
  {
    pressure_error = 1;
    return;
  }  
  */
  while(!((*AT91C_TWI0_SR) & (0x1 << 2)))
  {
    
  }
  *AT91C_TWI0_CR = 0x1 << 1;//stop signal
  //check if the conversition is over
  while((*AT91C_TWI0_SR & 0x1) != 0x1)
  {
    
  }  
  *AT91C_TWI0_CR = 0x1 << 3;//disable master mode
}

unsigned char readData(unsigned char address)
{
  int ii;  
  unsigned char data;
  *AT91C_TWI0_CR = 0x24;
  *AT91C_TWI0_MMR = 0x00601100;//set slave adress to 0x60, read direction, 1 byte internal address  
  *AT91C_TWI0_IADR = address; //set internal address  
  *AT91C_TWI0_CR = 0x03;//start and stop signal  

  while(!((*AT91C_TWI0_SR) & (0x01 << 1)))
  {
    
  }
  data = (*AT91C_TWI0_RHR) & 0xFF; 
  
  *AT91C_TWI0_CR = 0x01 << 1;//stop signal  
  //check if the conversition is over
  while((*AT91C_TWI0_SR & 0x01) != 0x01)
  {
    
  }  
  *AT91C_TWI0_CR = 0x01 << 3;//disable master mode
  return data;
}

void initial_AIR()
{
  disablePin(PIOA_PIOS, 17);
  disablePin(PIOA_PIOS, 18);
  enableClock(TWI0_PIID);
  
  *AT91C_TWI0_CWGR = 0x0001D0D0;////Clock Waveform both is 5 micro second
  *AT91C_TWI0_CR = 0x1 << 5;//disable slave mode
  
  transmitData(0x04, 0x26); //reset sensor
  Delay(70);
  flag = 1;
}
