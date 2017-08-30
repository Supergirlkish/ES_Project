#include "project.h"


int main()
{
	uint32_t i;
	uint8_t arr[100];
	
	for (i=0;i<100;i++)
	{
		arr[i] = 0x23;
	}
	
	i=0;
	while(i<1234)
	{
		i++;
	}
	while(GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_6));
	
	switch (i)
	{
		case 0: 
			//sdfsdfs
		break;
		
		case 1:
			//
		break;
		
		default:
			//asdfj;lsk
		break;
	}
	
	if (i!=1)
	{
		//asd;ofja;s
	}
	else
	{
		//sadlkfjhaskldj
	}
}