#include "HAL_Sasu.h"

//  Super Awesome Startup functions.  These are some hacks
//  to help out with booting up the TIVA Board.  

void HALSasu()
{
	EnableAllPorts();
	UnlockPins();
}


void UnlockPins()
{
	//Need to Unlock PF4
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0xFF;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
	
		
	//Need to Unlock PD7
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xFF;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
	
		//Need to Unlock PC7
	HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTC_BASE + GPIO_O_CR) = 0xFF;
	HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = 0;
	
}

//this is bad practice but whatever for now.
void EnableAllPorts()
{
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
  {
    
	}
	
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
  {
    
	}
	
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
  {
    
	}
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
  {
    
	}
    
		// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
  {
    
	}
	
	// Enable the GPIO port that is used for the on-board LED.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		
	// Check if the peripheral access is enabled.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  {
    
	}
}

