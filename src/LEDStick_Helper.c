#include "LEDStick_Helper.h"

uint8_t rgbwmatrix[LED_SIZE][5];

void ResetMatrix()
{
	for (int i; i<LED_SIZE;i++)
	{
		rgbwmatrix[i][0]=0;
		rgbwmatrix[i][1]=0;
		rgbwmatrix[i][2]=0;
		rgbwmatrix[i][3]=0;
		rgbwmatrix[i][4]=0;
	}
}

void SetRGBColor(uint8_t RED,uint8_t GRE,uint8_t BLU, uint8_t LED)
{
	rgbwmatrix[LED][0]=RED;
	rgbwmatrix[LED][1]=GRE;
	rgbwmatrix[LED][2]=BLU;
	rgbwmatrix[LED][3]=0;
}

void SetWColor(uint8_t WHI, uint8_t LED)
{
	rgbwmatrix[LED][0]=0;
	rgbwmatrix[LED][1]=0;
	rgbwmatrix[LED][2]=0;
	rgbwmatrix[LED][3]=WHI;
}


void ShiftColor(uint8_t lednum)
{
	//r->R, //b<-B,	//g->G, //r<-R,	//b->B,	//g<-G
	
	//make sure led number is within array
	if(lednum>LED_SIZE)return;
	
	//what rotating state is it in.
	switch (rgbwmatrix[lednum][LED_STATE])
	{
		case 0:  //increase red
		  if ((++rgbwmatrix[lednum][RED_IDX]) == 255)
			{
				  rgbwmatrix[lednum][LED_STATE]++;
				  //check to make sure next state doesnt crap out
				  if (rgbwmatrix[lednum][BLU_IDX]==CLR_MIN)
					{
						rgbwmatrix[lednum][BLU_IDX]=CLR_MIN+1;
					};
			}
		break;		
		case 1: //decrease blue
		  if (--rgbwmatrix[lednum][BLU_IDX] == 0)
			{
				  rgbwmatrix[lednum][LED_STATE]++;
					if (rgbwmatrix[lednum][GRE_IDX]==CLR_MAX)
					{
						rgbwmatrix[lednum][GRE_IDX]=CLR_MAX-1;
					};
			}
		break;		
		case 2: //increase green
		  if (++rgbwmatrix[lednum][GRE_IDX] == CLR_MAX)
			{
				  rgbwmatrix[lednum][LED_STATE]++;
					if (rgbwmatrix[lednum][RED_IDX]==CLR_MIN)
					{
						rgbwmatrix[lednum][RED_IDX]=CLR_MIN+1;
					};
			}
		break;		
		case 3: //decrease red
		  if (--rgbwmatrix[lednum][RED_IDX] == CLR_MIN)
			{
				  rgbwmatrix[lednum][LED_STATE]++;
					if (rgbwmatrix[lednum][BLU_IDX]==255)
					{
						rgbwmatrix[lednum][BLU_IDX]=254;
					};
			}
		break;		
		case 4: //increase blue
		  if (++rgbwmatrix[lednum][BLU_IDX] == CLR_MAX)
			{
				  rgbwmatrix[lednum][LED_STATE]++;
					if (rgbwmatrix[lednum][GRE_IDX]==CLR_MIN)
					{
						rgbwmatrix[lednum][GRE_IDX]=CLR_MAX-1;
					};
			}
		break;		
		case 5: //decrease green
		  if (--rgbwmatrix[lednum][GRE_IDX] == CLR_MIN)
			{
				  rgbwmatrix[lednum][LED_STATE]=0;
					if (rgbwmatrix[lednum][RED_IDX]==255)
					{
						rgbwmatrix[lednum][RED_IDX]=254;
					};
			}
		break;
		default:
				  rgbwmatrix[lednum][LED_STATE]=0;
		break;
	}
}

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

void SendMatrix()
{
	uint8_t n,j,scratch;
	latch();
	for (int i = 0;i<LED_SIZE;i++)
	{
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][GRE_IDX]>>n)&0x01; 
			if (scratch == 1) test_one();
			else test_zero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][RED_IDX]>>n)&0x01; 
			if (scratch == 1) test_one();
			else test_zero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][BLU_IDX]>>n)&0x01; 
			if (scratch == 1) test_one();
			else test_zero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][WHI_IDX]>>n)&0x01; 
			if (scratch == 1) test_one();
			else test_zero();
		}
	}
	latch();
}

void test_stick(uint8_t RED,uint8_t GRE,uint8_t BLU,uint8_t WHI)
{
	//green red blue order
	//most sig bit first
	uint8_t n,j,scratch;
	
	latch();
	for (j=0;j<8;j++)
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
		
		for(n=8; n>0; --n)
		{
			scratch = (WHI>>n)&0x01; 
			
			if (scratch == 1) test_one();
			else test_zero();
			
		}
		
	}
	latch();
	
}

