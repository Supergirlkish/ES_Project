#include "project.h"
#include <stdio.h>
#include <stdint.h>


#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000008  // port F Clock Gating Control
#define LEDS                    (*((volatile unsigned long *)0x4000703C))
	

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif



int  main(void)
{
	uint32_t delay; 
	uint8_t test1;
	uint16_t test;
	
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
    
	}
	
//	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // activate port D
//  delay = SYSCTL_RCGC2_R;      // allow time for clock to stabilize
  GPIO_PORTF_DIR_R |= 0x0F;    // make PD3-0 out
  GPIO_PORTF_AFSEL_R &= ~0x0F; // regular port function 
  GPIO_PORTF_DEN_R |= 0x0F;    // enable digital I/O on PD3-0
	
  while(1){
   GPIO_PORTF_DATA_R = 0x0E;
		//__nop();
		//GPIO_PORTF_DATA_R = GPIO_PORTF_DATA_R | 0x0E;
		//GPIO_PORTF_DATA_R &= ~0x01;
	
  }
}
