#include "Display.h"

#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12

AnalDisplay::AnalDisplay() 
	: device(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO)
{}

void AnalDisplay::begin()
{
	device.begin();
    device.setRotation(3);
    device.fillScreen(ILI9341_BLACK);
    device.setCursor(0,0);
    device.println("display begin");
    delay(250);
    device.println("touchscreen begin");
    touchscreen.begin();
    delay(250);
    device.fillScreen(ILI9341_BLACK);
}

void AnalDisplay::update()
{
	touchscreen.update();
}