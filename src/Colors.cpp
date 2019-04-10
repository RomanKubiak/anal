#include "Colors.h"

uint16_t color_darker(uint16_t color, const uint8_t percent)
{
	uint8_t r,g,b,_r,_g,_b;
	ILI9341_t3::color565toRGB(color, r, g, b);
	_r = r/(100/percent);
	_g = g/(100/percent);
	_b = b/(100/percent);

	return ILI9341_t3::color565(r-_r, g-_g, b-_b);
}

uint16_t color_brighter(uint16_t color, const uint8_t percent)
{
	uint8_t r,g,b,_r,_g,_b;
	ILI9341_t3::color565toRGB(color, r, g, b);
	_r = r/(100/percent);
	_g = g/(100/percent);
	_b = b/(100/percent);

	return ILI9341_t3::color565(r+_r, g+_g, b+_b);
}