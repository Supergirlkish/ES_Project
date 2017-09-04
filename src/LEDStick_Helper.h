#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "hw_gpio.h"
#include "hw_types.h"
#include "systick.h"


													//ring has 60 leds
													//string has 8
#define LED_SIZE 	40				//num of leds in matrix, strip, etc

#define RED_IDX 0					//array index for red
#define GRE_IDX 1					//green
#define BLU_IDX 2					//blue
#define WHI_IDX 3					//white
#define LED_STATE 4				//array index for what rotation state its in 
#define CLR_MAX 120				//the max brigthness the LEDS can go (255 max)
#define CLR_MIN 0					//the min

#define RGB_TYPE 0				//if LED is RGB
#define RGBW_TYPE 1				//if LED is RGBW

//rgbw rotation position
extern uint8_t rgbwmatrix[LED_SIZE][5];
void WSShiftColor(uint8_t LED_NUM);
void WSSendMatrix(uint8_t MATRIX_TYPE);
void WSinitPin(void);
void WSSetAllLeds(uint8_t RED,uint8_t GRE,uint8_t BLU,uint8_t WHI);
void WSShiftColor_static(uint8_t lednum);
void WSNormalizeAll(void);
void WSRand(void);
void WSSetRGBColor(uint8_t RED,uint8_t GRE,uint8_t BLU, uint8_t LED);
void WSSetChar(uint8_t thischar, uint8_t RED,uint8_t GRE,uint8_t BLU);
void SetPixel(uint8_t row,uint8_t col);


#define WS_C {0xf8,0x80,0x80,0x80,0xf8}
#define WS_G {0xf8,0x88,0x98,0x80,0xf8}
#define WS_E {0xf8,0x80,0xe0,0x80,0xf8}
#define WS_T
#define WS_SP
#define WS_S
#define WS_C
#define WS_H
#define WS_W
#define WS_I
#define WS_F
#define WS_T
#define WS_Y
