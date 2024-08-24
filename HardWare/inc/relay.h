#ifndef __RELAY_H__
#define __RELAY_H__

#include "gpio.h"

typedef enum
{
    RELAY_OFF = 0,
    RELAY_ON,
} Relay_State;

extern GPIO_Struct Relay_Pin; 

void Relay_Init(void);
void Relay_Control(Relay_State state);

#endif


