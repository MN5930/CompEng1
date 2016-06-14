#include "X_PIO.h"
#include "X_PMC.h"
#include "..\at91sam3x8.h"

//enable pin
void enablePin(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_PER + type * 0x200) = 0x1 << pin;
}
//disable pin
void disablePin(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_PDR + type * 0x200) = 0x1 << pin;
}
//enable pull up
void enablePullUp(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_PPUER + type * 0x200) = 0x1 << pin;
}
//disable pull up
void disablePullUp(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_PPUDR + type * 0x200) = 0x1 << pin;
}
//enable output
void enableOutput(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_OER + type * 0x200) = 0x1 << pin;
}
//disable output
void disableOutput(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_ODR + type * 0x200) = 0x1 << pin;
}
//set pin to 1
void setPin(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_SODR + type * 0x200) = 0x1 << pin;
}
//clear pin to 0
void clearPin(PIOS_TYPE type, int pin)
{
	*(AT91_REG *)((unsigned int)AT91C_PIOA_CODR + type * 0x200) = 0x1 << pin;
}
//select A/B function, AB = 0 means A, AB = 1 means B
void selectAB(PIOS_TYPE type, int pin, int AB)
{
	if(AB == 0)
	{
		int tmp = 0x1 << pin;
		tmp = ~tmp;
		*(AT91_REG *)((unsigned int)AT91C_PIOA_ABMR + type * 0x200) &= tmp;
	}else if(AB == 1)
	{
		*(AT91_REG *)((unsigned int)AT91C_PIOA_ABMR + type * 0x200) |= 0x1 << pin;
	}
}