#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "uart.h"
#include "../inc/tm4c123gh6pm.h"
#include "hw_gpio.h"
#include "hw_types.h"

#define LED_SIZE  8

#define RED_IDX 0
#define GRE_IDX 1
#define BLU_IDX 2
#define WHI_IDX 3
#define LED_STATE 4
#define CLR_MAX 255
#define CLR_MIN 0

//rgbw rotation position
extern uint8_t rgbwmatrix[LED_SIZE][5];
void ShiftColor(uint8_t);
void test_one(void);
void test_zero(void);
void test_stick(uint8_t ,uint8_t ,uint8_t ,uint8_t );

