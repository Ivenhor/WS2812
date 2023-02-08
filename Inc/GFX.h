#ifndef GFX_H
#define GFX_H

#include "stm32f3xx_hal.h"

void draw_char(char Character, uint16_t X, uint16_t Y, uint16_t r, uint16_t g, uint16_t b);
void draw_text(const char* Text, uint16_t X, uint16_t Y, uint16_t r, uint16_t g, uint16_t b);
void draw_scroll_text(const char* Text, uint16_t r, uint16_t g, uint16_t b);
void test ();
uint8_t rainbow_effect_right();
uint8_t rainbow_effect_left();
uint8_t rainbow_text(const char* Text, uint16_t x, uint16_t y);

#endif
