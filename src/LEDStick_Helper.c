#include "LEDStick_Helper.h"

//bit bang method to control WS Leds
//Matrix data is public global, other modules can access
//Call initWSPin once to set pin as output
//

uint8_t rgbwmatrix[LED_SIZE][5];


void WSSendOne(void);
void WSSendZero(void);
void WSResetMatrix(void);

uint32_t WSMatrix2Pixel(uint8_t row,uint8_t col)
{
	return(row*8+col);
}

void WSSetChar(uint8_t thischar, uint8_t RED,uint8_t GRE,uint8_t BLU)
{
    uint8_t gyu[5]=WS_E;
		int k=0;
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<8;j++)
			{
				if(((gyu[i]>>j)&0x1)==1)
				{
					//WSSetRGBColor(255,0,0,k);
				}
				else
				{
					WSSetRGBColor(0,0,0,k);
				}
				k++;
			}
		}
}

//color related functions

//resets the color matrix to zero
void WSResetMatrix()
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

//set all the leds in the matrix to a single color
void WSSetAllLeds(uint8_t RED,uint8_t GRE,uint8_t BLU,uint8_t WHI)
{
	for (int i=0;i<LED_SIZE;i++)
	{
		rgbwmatrix[i][RED_IDX]=RED;
		rgbwmatrix[i][GRE_IDX]=GRE;
		rgbwmatrix[i][BLU_IDX]=BLU;
		rgbwmatrix[i][WHI_IDX]=WHI;
	}
}
//set color of an individual LED RGB Values
void WSSetRGBColor(uint8_t RED,uint8_t GRE,uint8_t BLU, uint8_t LED)
{
	rgbwmatrix[LED][0]=RED;
	rgbwmatrix[LED][1]=GRE;
	rgbwmatrix[LED][2]=BLU;
	rgbwmatrix[LED][3]=0;
}

//Set the white value
void WSSetWColor(uint8_t WHI, uint8_t LED)
{
	rgbwmatrix[LED][0]=0;
	rgbwmatrix[LED][1]=0;
	rgbwmatrix[LED][2]=0;
	rgbwmatrix[LED][3]=WHI;
}

void WSRand()
{
	uint32_t scratch;
	for (int i=0;i<LED_SIZE;i++)
	{
		scratch = SysTickValueGet();
		srand(0x45);
		scratch = rand();
		rgbwmatrix[i][0]=(uint8_t)(rand()>>15);
		rgbwmatrix[i][1]=(uint8_t)(rand()>>15);
		rgbwmatrix[i][2]=(uint8_t)(rand()>>15);
	}
	
}

//pretty sure this works, need to test
void WSNormalizeLed(uint8_t lednum)
{
		uint32_t thisred,thisblue,thisgreen;
		uint32_t sum;
	
		thisred   = rgbwmatrix[lednum][RED_IDX];
		thisgreen = rgbwmatrix[lednum][BLU_IDX];
		thisblue  = rgbwmatrix[lednum][GRE_IDX];
	
		sum = thisblue  + thisgreen + thisred ;
	
	  thisblue *= 0xFF;
		thisgreen *= 0xFF;
		thisred *= 0xFF;
	
	  thisred /=sum;
		thisblue /=sum;
		thisgreen /=sum;
	
		thisred   = rgbwmatrix[lednum][RED_IDX] = thisred;
		thisgreen = rgbwmatrix[lednum][BLU_IDX] = thisgreen;
		thisblue  = rgbwmatrix[lednum][GRE_IDX] = thisblue;
	
}

void WSNormalizeAll()
{
	for (int i=0;i<LED_SIZE;i++)
	{
		WSNormalizeLed(i);
	}
}

//shifts colors but keeps total value normalized
//to CLR_MAX
void WSShiftColor_static(uint8_t lednum)
{
	//make sure led number is within array
	if(lednum>LED_SIZE)return;
	
	//r+,b-, 	r-,g+, 	g-,b+
	switch (rgbwmatrix[lednum][LED_STATE])
	{
		case 0:
			rgbwmatrix[lednum][RED_IDX]++;
			rgbwmatrix[lednum][BLU_IDX]--;
			rgbwmatrix[lednum][GRE_IDX]=0;
		  if (rgbwmatrix[lednum][RED_IDX]==CLR_MAX)
			{
				rgbwmatrix[lednum][LED_STATE]=1;
			}
		break;
		
		case 1:
			rgbwmatrix[lednum][BLU_IDX]=0;
			rgbwmatrix[lednum][RED_IDX]--;
			rgbwmatrix[lednum][GRE_IDX]++;
			if (rgbwmatrix[lednum][GRE_IDX]==CLR_MAX)
			{
				rgbwmatrix[lednum][LED_STATE]=2;
			}
		break;
		
		case 2:
			rgbwmatrix[lednum][RED_IDX]=0;
			rgbwmatrix[lednum][GRE_IDX]--;
			rgbwmatrix[lednum][BLU_IDX]++;
			if (rgbwmatrix[lednum][BLU_IDX]==CLR_MAX)
			{
				rgbwmatrix[lednum][LED_STATE]=0;
			}
		break;
		default:
				rgbwmatrix[lednum][RED_IDX]=0;
				rgbwmatrix[lednum][GRE_IDX]=0;
				rgbwmatrix[lednum][BLU_IDX]=CLR_MAX;
				rgbwmatrix[lednum][LED_STATE]=0;
			break;
	}
}

//rotates the color of LED.  Call continuously in for loop
void WSShiftColor(uint8_t lednum)
{
	//  r->R, b<-B,	g->G, r<-R,	b->B,	g<-G
	
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


// HAL Related functions at the bottom

// call init to set up pin.  
void WSinitPin()
{
	//Port B Setup
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7|GPIO_PIN_6);
	GPIOPadConfigSet(GPIO_PORTB_BASE,GPIO_PIN_7|GPIO_PIN_6,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD);
}


void WSLatch()
{
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7|GPIO_PIN_6,0x00) ; 
	//delay at least 50us
	for (int j = 0; j<4010; j++)
	{
		__nop();
	}
}

//bit bang out a One.  Works on 80Mhz clock only
void WSSendOne()
{
		GPIO_PORTB_DATA_R |= (GPIO_PIN_7|GPIO_PIN_6); //.8us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		GPIO_PORTB_DATA_R &= ~(GPIO_PIN_7|GPIO_PIN_6); //.45us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();
}

//bit bang out a Zero.  Works on 80Mhz clock only
void WSSendZero()
{
		GPIO_PORTB_DATA_R |= (GPIO_PIN_7|GPIO_PIN_6);
		//.4us
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	
		GPIO_PORTB_DATA_R &= ~(GPIO_PIN_7|GPIO_PIN_6);
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

//sends the color matrix out to the RGBW Leds
//comment out last part if no WHI Led
void WSSendMatrix(uint8_t matrix_type)
{
	uint8_t n,scratch;
	WSLatch();
	for (int i = 0;i<LED_SIZE;i++)
	{
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][GRE_IDX]>>n)&0x01; 
			if (scratch == 1) WSSendOne();
			else WSSendZero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][RED_IDX]>>n)&0x01; 
			if (scratch == 1) WSSendOne();
			else WSSendZero();
		}
		
		for(n=8; n>0; --n)
		{
			scratch = (rgbwmatrix[i][BLU_IDX]>>n)&0x01; 
			if (scratch == 1) WSSendOne();
			else WSSendZero();
		}
		
//		if (matrix_type == RGBW_TYPE)
//		{
//			for(n=8; n>0; --n)
//			{
//				scratch = (rgbwmatrix[i][WHI_IDX]>>n)&0x01; 
//				if (scratch == 1) WSSendOne();
//				else WSSendZero();
//			}
//		}
	}
	WSLatch();
}
