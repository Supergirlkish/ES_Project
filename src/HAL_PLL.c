#include "HAL_PLL.h"

#define SYSCTL_RCC_OEN          0x00001000  // PLL Output Enable

#define SYSCTL_RCC_SYSDIV_M     0x07800000  // System Clock Divisor
#define SYSCTL_RCC_SYSDIV_4     0x01800000  // System clock /4
#define SYSCTL_RCC_SYSDIV_5     0x02000000  // System clock /5
#define SYSCTL_RCC_SYSDIV_6     0x02800000  // System clock /6
#define SYSCTL_RCC_SYSDIV_7     0x03000000  // System clock /7
#define SYSCTL_RCC_SYSDIV_8     0x03800000  // System clock /8
#define SYSCTL_RCC_SYSDIV_9     0x04000000  // System clock /9
#define SYSCTL_RCC_SYSDIV_10    0x04800000  // System clock /10
#define SYSCTL_RCC_SYSDIV_11    0x05000000  // System clock /11
#define SYSCTL_RCC_SYSDIV_12    0x05800000  // System clock /12
#define SYSCTL_RCC_SYSDIV_13    0x06000000  // System clock /13
#define SYSCTL_RCC_SYSDIV_14    0x06800000  // System clock /14
#define SYSCTL_RCC_SYSDIV_15    0x07000000  // System clock /15
#define SYSCTL_RCC_SYSDIV_16    0x07800000  // System clock /16

void SetupPLL(void)
{
	//Using library
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	
	
	
	//The two examples below use direct register access, not setup for 80Mhz.
	//pg 113 in book
	//Using Direct Register Access and Bits
//	SYSCTL_RCC2_R |= 0x80000000;  	 
//	SYSCTL_RCC2_R |= 0x00000800;		 
//	SYSCTL_RCC_R  |= (SYSCTL_RCC_R &~0x000007C0)+0x00000540;
//	SYSCTL_RCC2_R &= ~0x00000070;
//	SYSCTL_RCC2_R &= ~0x00002000;
//	SYSCTL_RCC2_R |=  0x40000000;
//	SYSCTL_RCC_R  |= (SYSCTL_RCC2_R &~0x1FC00000)+(4<<22);
//	while((SYSCTL_RIS_R&0x00000040)==0){};
//	SYSCTL_RCC2_R &= ~0x00000800;
		
//	//Using Direct Register Access
//	  // 1) bypass PLL and system clock divider while initializing
//  SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;
//  SYSCTL_RCC_R &= ~SYSCTL_RCC_USESYSDIV;
//  // 2) select the crystal value and oscillator source
//  SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   	// clear XTAL field
//  SYSCTL_RCC_R += SYSCTL_RCC_XTAL_6MHZ; 	// configure for 6 MHz crystal (default setting)
//  SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_M; 	// clear oscillator source field
//  SYSCTL_RCC_R += SYSCTL_RCC_OSCSRC_MAIN;	// configure for main oscillator source (default setting)
//  // 3) activate PLL by clearing PWRDN and OEN
//  SYSCTL_RCC_R &= ~(SYSCTL_RCC_PWRDN|SYSCTL_RCC_OEN);
//  // 4) set the desired system divider and the USESYSDIV bit
//  SYSCTL_RCC_R &= ~SYSCTL_RCC_SYSDIV_M; // system clock divider field
//  SYSCTL_RCC_R += SYSCTL_RCC_SYSDIV_8;  // configure for 25 MHz clock
//  SYSCTL_RCC_R |= SYSCTL_RCC_USESYSDIV;
//  // 5) wait for the PLL to lock by polling PLLLRIS
//  while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
//  // 6) enable use of PLL by clearing BYPASS
//  SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS;
//	
}



