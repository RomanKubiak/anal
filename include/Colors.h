#ifndef colors_h__
#define colors_h__
#include <ILI9341_t3.h>
uint16_t color_darker(uint16_t color, const uint8_t percent);
uint16_t color_brighter(uint16_t color, const uint8_t percent);
#endif