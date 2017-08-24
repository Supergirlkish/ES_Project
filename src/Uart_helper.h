#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "tm4c123gh6pm.h"


void UartSetup(void);		//sets up Uart for my configuration using library
void UartSetup2(void);	//sets up Uart for my configuration registers