#include "LCD_helper.h"

void LCDSetupPins()
{
	//Port B Setup
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_0);
	GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_5|GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_0,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD);
	
	//Port E Setup
	GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTE_BASE,GPIO_PIN_5|GPIO_PIN_4,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD);
}

void SetupLCD()
{
	

}


/*****************************************************/
void dispPic(unsigned char *lcd_string)
{

}
