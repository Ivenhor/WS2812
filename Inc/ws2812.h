#ifndef WS2812_H_
#define WS2812_H_
//--------------------------------------------------
#include "stm32f3xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "math.h"
//--------------------------------------------------
#define MAX_LED 256
#define USE_BRIGHTNESS 0

#define DISPLAY_HEIGHT 8
#define DISPLAY_WIDTH 32

#define PI 3.14159265

//--------------------------------------------------

void Set_LED (int LEDnum, int Red, int Green, int Blue);
void Set_Brightness (int brightness);
void WS2812_Send (void);
void Reset_LED (void);
void draw_pixel(uint16_t X,uint16_t Y,int r, int g, int b);
int pixel_solver(uint16_t x, uint16_t y);



//--------------------------------------------------
#endif /* WS2812_H_ */
