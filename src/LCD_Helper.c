#include "LCD_helper.h"

//using SSI0
//MOSI 	PA5
//CS 		PA3
//RST 	PB3
//CLK		PA2
//DC		PA4


void LCDSetupPins(void);
void LCDSetupSSI(void);


void SetupLCD()
{
	LCDSetupPins();
	LCDSetupSSI();
}

