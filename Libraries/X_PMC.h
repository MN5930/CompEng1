#ifndef X_PMC
#define X_PMC

//Peripheral Identifiers Instance ID
typedef enum PIID
{
    SUPC_PIID = 0,  //Supply Controller
    RSTC_PIID = 1,  //Reset Controller
    RTC_PIID  = 2,  //Real Time Clock
    RTT_PIID  = 3,  //Real Time Timer
    PMC_PIID  = 5,  //Power Management Controller
    PIOA_PIID = 11, //Parallel I/O Controller A
    PIOB_PIID = 12, //Parallel I/O Controller B
    PIOC_PIID = 13, //Parallel I/O Controller C
    PIOD_PIID = 14, //Parallel I/O Controller D
    TWI0_PIID = 22, //Two-Wire Interface 0
    TWI1_PIID = 23, //Two-Wire Interface 1
    TC0_PIID  = 27, //Timer Counter 0
    TC1_PIID  = 28, //Timer Counter 1
    TC2_PIID  = 29, //Timer Counter 2
    TC3_PIID  = 30, //Timer Counter 3
    TC4_PIID  = 31, //Timer Counter 4
    TC5_PIID  = 32, //Timer Counter 5
    TC6_PIID  = 33, //Timer Counter 6
    TC7_PIID  = 34, //Timer Counter 7
    TC8_PIID  = 35, //Timer Counter 8
    PWM_PIID  = 36, //Pulse Width Modulation Controller
    ADC_PIID  = 37, //ADC Controller
    DACC_PIID = 38, //DAC Controller
    DMAC_PIID = 39 //DMA Controller 
}PIID_TYPE;

//enable clock
void enableClock(PIID_TYPE piid);
//disable clock
void disableClock(PIID_TYPE piid);

#endif