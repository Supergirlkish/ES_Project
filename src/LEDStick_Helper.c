#include "LEDStick_Helper.h"



void this_delay(uint32_t i)
{
	uint32_t j;
	for (j = 0; j<i; j++)
	{
		__nop();
	}
}
void send_zero()
{
	GPIO_PORTB_DATA_R |= 0x10;
	//GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0xFF) ; 
	//.4us delay
	__nop();
	GPIO_PORTB_DATA_R &= ~0x10;
	//GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0x00) ; 
	//.8us delay
	__nop();
	__nop();
}

void send_one()
{
	GPIO_PORTB_DATA_R |= 0x10;
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0xFF) ; 
	//.8us delay
	__nop();
	__nop();
	GPIO_PORTB_DATA_R &= ~0x10;
	//GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0x00) ; 
	//.4us delay
	__nop();
	
}

void latch()
{
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4,0x00) ; 
	this_delay(20); //at least 50us
}


void test_one()
{
		GPIO_PORTB_DATA_R |= 0x10; //.8us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		GPIO_PORTB_DATA_R &= ~0x10; //.45us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();
}

void test_zero()
{
		GPIO_PORTB_DATA_R |= 0x10;
		//.4us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	
		GPIO_PORTB_DATA_R &= ~0x10;
		//.85us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
	
		__nop();__nop();__nop();__nop();
		
}

void test_stick()
{
	//green red blue order
	//most sig bit first
	uint8_t n,j,scratch;
	static uint8_t RED=0x2;
	uint8_t BLU=0x0;
	uint8_t GRE=0x0;

	RED++;
	//BLU++;
	//GRE++;
	latch();
	for (j=0;j<2;j++)
	{
		for(n=8; n>0; --n)
		{
			scratch = (GRE>>n)&0x01; 
			
			if (scratch == 1) test_one();
			else test_zero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (RED>>n)&0x01; 
			
			if (scratch == 1) test_one();
			else test_zero();
			
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (BLU>>n)&0x01; 
			
			if (scratch == 1) test_one();
			else test_zero();
			
		}
		
	}
	latch();
}

