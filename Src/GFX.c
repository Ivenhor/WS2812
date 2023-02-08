#include "ws2812.h"
#include "GFX.h"
#include "5x5_font.h"

uint16_t effStep = 0;
//--------------------------------------------------
void draw_char(char Character, uint16_t x, uint16_t y, uint16_t r, uint16_t g, uint16_t b)
{
		uint8_t 	function_char;
		uint8_t 	i,j;

		function_char = Character;

    if (function_char < ' ') {
        Character = 0;
    } else {
        function_char -= 32;
		}

		char temp[CHAR_WIDTH];
		for(uint8_t k = 0; k<CHAR_WIDTH; k++)
		{
		temp[k] = font[function_char][k];
		}



    // Draw pixels

    for (j=0; j<CHAR_WIDTH; j++) {
        for (i=0; i<CHAR_HEIGHT; i++) {
            if (temp[j] & (1<<i)) {

              draw_pixel(x+j, y+i, r, g, b);

            }
        }
    }

    WS2812_Send();

}
//--------------------------------------------------
void shift_char(const char* Text)
{
	for (int x = DISPLAY_WIDTH; x!=0; x--)
	{
		draw_char(*Text, x, 0, 0, 0, 255);
		HAL_Delay(10);
		Reset_LED ();
	}

}
//--------------------------------------------------
void draw_text(const char* Text, uint16_t x, uint16_t y, uint16_t r, uint16_t g, uint16_t b)
{
    while (*Text) {
    	draw_char(*Text++, x, y, r, g, b);
        x += CHAR_WIDTH;
    }
    //WS2812_Send();
}
//--------------------------------------------------

int random_number(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}
//--------------------------------------------------
void test ()
{
	for (uint8_t i=0; i<DISPLAY_HEIGHT; i++)
		  {
			for(uint16_t j=0, x=1;j<DISPLAY_WIDTH||x<DISPLAY_WIDTH;j++,x++)
			{
				draw_pixel(j, i, random_number(0,255), random_number(0,255), random_number(0,255));
				WS2812_Send();
			}
		  }
}
//--------------------------------------------------
uint8_t rainbow_effect_right() {

  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<DISPLAY_WIDTH;j++) {
    ind = 14 - (int16_t)(effStep - j * 1.75) % 14;
    switch((int)((ind % 14) / 4.666666666666667)) {
      case 0: factor1 = 1.0 - ((float)(ind % 14 - 0 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 0) % 14) / 4.666666666666667;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
            	  draw_pixel(j, i, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              }
              break;

      case 1: factor1 = 1.0 - ((float)(ind % 14 - 1 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 4.666666666666667) % 14) / 4.666666666666667;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
            	  draw_pixel(j, i, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              }
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 14 - 2 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 9.333333333333334) % 14) / 4.666666666666667;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
            	  draw_pixel(j, i, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              }
              break;

    }
  }
  WS2812_Send();
  if(effStep >= 14) {effStep = 0; return 0x03; }
  else effStep++;
  return 0x01;
}
//--------------------------------------------------
uint8_t rainbow_effect_left()
{
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<DISPLAY_WIDTH;j++) {
    ind = effStep + j * 1.625;
    switch((int)((ind % 13) / 4.333333333333333)) {
      case 0: factor1 = 1.0 - ((float)(ind % 13 - 0 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 0) % 13) / 4.333333333333333;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
            	  draw_pixel(j, i, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
              }
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 13 - 1 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 4.333333333333333) % 13) / 4.333333333333333;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
              	draw_pixel(j, i, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
              }
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 13 - 2 * 4.333333333333333) / 4.333333333333333);
              factor2 = (float)((int)(ind - 8.666666666666666) % 13) / 4.333333333333333;
              for(uint8_t i=0;i<DISPLAY_HEIGHT;i++)
              {
            	  draw_pixel(j, i, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
              }
              break;
    }
  }
  WS2812_Send();
  if(effStep >= 13) {effStep=0; return 0x03; }
  else effStep++;
  return 0x01;
}
//--------------------------------------------------
uint8_t rainbow_text(const char* Text, uint16_t x, uint16_t y)
{
  float factor1, factor2;
  uint16_t ind;
  while (*Text) {
    ind = 14 - (int16_t)(effStep - x * 1.75) % 14;
    switch((int)((ind % 14) / 4.666666666666667)) {
      case 0: factor1 = 1.0 - ((float)(ind % 14 - 0 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 0) % 14) / 4.666666666666667;
           	  draw_char(*Text++, x, y, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
           	  x += CHAR_WIDTH;
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 14 - 1 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 4.666666666666667) % 14) / 4.666666666666667;
           	  draw_char(*Text++, x, y, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
           	  x += CHAR_WIDTH;
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 14 - 2 * 4.666666666666667) / 4.666666666666667);
              factor2 = (float)((int)(ind - 9.333333333333334) % 14) / 4.666666666666667;
           	  draw_char(*Text++, x, y, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
           	  x += CHAR_WIDTH;
              break;

    }
  }
  WS2812_Send();
  if(effStep >= 14) {effStep = 0; return 0x03; }
  else effStep++;
  return 0x01;
}
