#ifndef _display_h
#define _display_h

#include "ILI9341_t3.h"
#include "Touchscreen.h"

class AnalDisplay
{
	public:
		AnalDisplay();
		ILI9341_t3 device;
		void update();
		void begin();
		AnalTouch &getTouch() { return (touchscreen); }
	private:
		AnalTouch touchscreen;
};

#endif