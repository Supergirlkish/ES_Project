#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "hw_gpio.h"
#include "hw_types.h"

void HALSasu(void);							//Super Awesome start up, calls all functions
void EnableAllPorts(void);  //just enable all the ports for now
void UnlockPins(void);
