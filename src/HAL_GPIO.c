#include "HAL_GPIO.h"

struct MySwitches MySwitches;

// /CS1 = PB0
// /RST = PB1
// A0   = PE4
// SCL  = PE5
// SI   = PB4
	
void GpioSetup()		//sets up GPIO
{
	
	//Port F Setup
	
	// On Board RGB LED Pins
	
	// Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
  // enable the GPIO pin for digital function.
	
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
	
	
	// On Board Momentary Switches
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
	
	//these two switchs need an internal pull up on pins
	GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
	//Port D Setup
	
	// Off Board Momentary Switches
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_6);
	GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_7);	
	
	//use internal pull ups for other switches as well. 
	GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_6|GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
	
	
	//Port C Setup
	
	// Off Board Momentary Switches
	GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_7);
		
	//use internal pull ups for other switches as well. 
	GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_7,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);	
	
	//Port B Setup
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD);

	//Port E Setup
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_5|GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD);

}

//A secondary version of Gpio Setup that enables switches on Port D and F
//This is just here to demonstrate how you would write code between the two 
//different methods: libraries or direct register access
void GpioSetup2()
{
	//setup port F

	//need to unlock the pins first
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;  //allow write access to CR reg
	GPIO_PORTF_CR_R = 0xFF; 						//write CR reg
	GPIO_PORTF_LOCK_R = 0;							//lock access to CR reg

	GPIO_PORTF_DIR_R = 0x0000000E; //PF1-3, outputs, all others inputs
	GPIO_PORTF_PUR_R = 0x00000011; //Pullups on PF0, PF4
	
	GPIO_PORTF_DEN_R = 0x0000001F; //PF0-4, digital enable, all others not
	//alternatively, set the digital enable while preserving the register contents
	GPIO_PORTF_DEN_R = GPIO_PORTF_DEN_R | 0x0000001F; 
	//short hand
	GPIO_PORTF_DEN_R |= 0x0000001F; 
	
	//Setup port D

	//need to unlock the pins first
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;  //allow write access to CR reg
	GPIO_PORTD_CR_R = 0xFF; 						//write CR reg
	GPIO_PORTD_LOCK_R = 0;							//lock access to CR reg

	
	//clearing bits
	GPIO_PORTD_DIR_R &= ~0x000000C0; //Make sure PD6, PD7 are inputs
	//Setting  bits
	GPIO_PORTD_PUR_R |=  0x000000C0; //PD6, PD7 pullups enabled
	GPIO_PORTD_DEN_R |=  0x000000C0; //enable digtial pins

}

//call this routine periodically to update the pin values in the global struct
void UpdateSwitches()
{
		uint32_t scratch;
		//pullups on pins so logic is reversed. 
	
		scratch = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4);
		if (scratch != 0) MySwitches.SW1 = 0;
		else MySwitches.SW1 = 1;
		
		scratch = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0);
		if (scratch != 0) MySwitches.SW2 = 0;
		else MySwitches.SW2 = 1;
	
		scratch = GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_6);
		if (scratch != 0) MySwitches.SW3 = 0;
		else MySwitches.SW3 = 1;
	
		scratch = GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_7);
		if (scratch != 0) MySwitches.SW4 = 0;
		else MySwitches.SW4 = 1;
	
		// cap sense is not inverse logic
		scratch = GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_7);
		if (scratch != 0) MySwitches.SW5 = 1;
		else MySwitches.SW5 = 0;
		
	
}
