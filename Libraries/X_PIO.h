#ifndef X_PIO
#define X_PIO

//PIO Ports
typedef enum PIOS
{
  PIOA_PIOS = 0,  //PIOA 
  PIOB_PIOS = 1,  //PIOB
  PIOC_PIOS = 2,  //PIOC
  PIOD_PIOS = 3   //PIOD
}PIOS_TYPE;

//enable pin
void enablePin(PIOS_TYPE type, int pin);
//disable pin
void disablePin(PIOS_TYPE type, int pin);
//enable pull up
void enablePullUp(PIOS_TYPE type, int pin);
//disable pull up
void disablePullUp(PIOS_TYPE type, int pin);
//enable output
void enableOutput(PIOS_TYPE type, int pin);
//disable output
void disableOutput(PIOS_TYPE type, int pin);
//set pin to 1
void setPin(PIOS_TYPE type, int pin);
//clear pin to 0
void clearPin(PIOS_TYPE type, int pin);
//select A/B function, AB = 0 means A, AB = 1 means B
void selectAB(PIOS_TYPE type, int pin, int AB);

#endif