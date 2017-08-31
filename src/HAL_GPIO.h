
#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "hw_gpio.h"
#include "hw_types.h"

void GpioSetup(void);		//sets up Uart for my configuration using library
void GpioSetup2(void);	//sets up Uart for my configuration registers
void UpdateSwitches(void);  //updates switch values

// 1 = Pushed down
// 0 = Not pushed down
// Note: User needs to config correct logic on whether or not pin is 
// pulled up or down.  

struct MySwitches {
	
	uint8_t SW1;
	uint8_t SW2;
	uint8_t SW3;
	uint8_t SW4;
	uint8_t SW5;
	
};

//global variable
extern struct MySwitches MySwitches;

