#include "project.h"

#define SYSTICK_STCTRL  	(*((volatile uint32_t *)0xE000E010))
#define SYSTICK_RELOAD  	(*((volatile uint32_t *)0xE000E014))
#define SYSTICK_CURRENT  	(*((volatile uint32_t *)0xE000E018))
												
void SetupSysTick()
{
  NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value
  NVIC_ST_CURRENT_R = 0;                // any write to current clears it
	
                                        // enable SysTick with core clock
NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC; 
}

int main ()
{
	int x;
	char w;
	bool f;
	
	uint8_t  variable;
	uint16_t anothervariable;
	int8_t signedvariable;
	
	//Using library
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	
	SetupSysTick();
	
}