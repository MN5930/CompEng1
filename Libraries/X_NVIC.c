#include "X_NVIC.h"
#include "..\system_sam3x.h"

void setNVIC(IRQn_Type IRQn)
{
    NVIC_ClearPendingIRQ(IRQn); 
    NVIC_SetPriority(IRQn, 1); 
    NVIC_EnableIRQ(IRQn); 
}