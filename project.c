#include "project.h"

//Momentary switches are connected to
//

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

uint8_t test = 0;
void accel2color()
{
	static uint32_t red, blue, green;
	static uint32_t red_n, blue_n, green_n;
	
	
	red_n = ADC_Values[4];
	blue_n = ADC_Values[5];		
	green_n = ADC_Values[6];	
	
	red_n >>= 4; 
	blue_n >>= 4;
	green_n >>= 4;
	
	
	WSSetAllLeds((uint8_t)(red_n-red),(uint8_t)(blue_n-blue),(uint8_t)(green_n-green),0);

	red = red_n;
	blue = blue_n;
	green = green_n;
}

void PlayArea ()
{
	int32_t scratch;
	scratch = GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
	scratch = ~scratch & (GPIO_PIN_4|GPIO_PIN_0) ; 
	switch (scratch)
	{
		case GPIO_PIN_4:
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0xF);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0);
			break;
		case GPIO_PIN_0:
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0xF);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
			break;
		case (GPIO_PIN_4|GPIO_PIN_0):
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0xF);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
			break;
		default:
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0);
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0);
			break;
	}
}

//call this periodically to update services
void ServiceRoutine()
{
		UpdateSwitches();
	//	WSRand();
//		WSNormalizeAll();
		WSSendMatrix(RGB_TYPE);
		SysTickWait10ms(2);
}

//Hardware abstraction Layer.  Setup all the hardware
//Do it once.  
void SetupHardware()
{
	SetupPLL();								// Setup the clock to 80Mhz
	SetupSystick();           // initialize SysTick timer
	UartSetup();							// Setup the Uart to print to terminal
	GpioSetup();							// GPIO
	SetupADC();								// Setup the ADC module
	WSinitPin();							// Pin for WS LEDs
	
}

int  main(void)
{
		uint8_t temp;
		uint32_t ADC[10];
		int32_t bytesread;
	
		HALSasu();								//Custom Startup script for TIVA board
															//Unlocks pins, turns on all ports, etc.
	
		SetupHardware();					// Call all HAL setup functions
		
//		while(1)
//		{
//			for (int i=0;i<LED_SIZE;i++)
//			{
//					for(int j=0;j<i+1;j++)WSShiftColor(i);
//			}
//			
//			WSSendMatrix(RGBW_TYPE);
//			SysTickWait10ms(1);
//		}
//	
	
//		while(1)
//		{
//			WSShiftColor(0);
//			WSSetAllLeds(rgbwmatrix[0][RED_IDX],rgbwmatrix[0][GRE_IDX],rgbwmatrix[0][BLU_IDX],rgbwmatrix[0][WHI_IDX]);
//			WSSendMatrix(RGBW_TYPE);
//			SysTickWait10ms(2);
//		}
//	
//	

    while(1)
    {
				UARTCharPut(UART0_BASE, (uint8_t)(ADC[0] >> 4));
				UARTCharPut(UART0_BASE, 0xFF);
			  //UARTCharPut(UART0_BASE, temp);
			  //temp++;
				//UARTCharPut(UART0_BASE, '\n');
				//UARTCharPut(UART0_BASE, '\r');

				PlayArea();
				ServiceRoutine();
			//	printf("Hello Everyone\n\r");
			//	WSSetChar(0,0,0,0);
				if (MySwitches.SW5==1)
				{
					WSShiftColor_static(0);
					WSSetAllLeds(rgbwmatrix[0][RED_IDX],rgbwmatrix[0][GRE_IDX],rgbwmatrix[0][BLU_IDX],rgbwmatrix[0][WHI_IDX]);
				}
				else 
				{
					WSSetAllLeds(0,0,0,0);
				}
				//accel2color();
				//WSSendMatrix(RGB_TYPE);
				//ADCReadChan();				
    }
	
	
}


