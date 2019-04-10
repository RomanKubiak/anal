#ifndef utils_h_
#define utils_h_

#include <Metro.h>
#include <Audio.h>
#include "Bounce2.h"
#include "Pins.h"
#include "Potentiometers.h"
#include "Buttons.h"
#include "Touchscreen.h"
#include "Leds.h"
#include "Colors.h"

void _d(const char *data);
void printSystemLoad(ILI9341_t3 &g, int x, int y, const char *data);
void displayPeak(ILI9341_t3 &g, int x, int y, int width, int height, AudioAnalyzePeak &peak);
/*
      int x,y;
      if (potIndex < 4)
      {
        x = 32 * potIndex;
        y = 60;
      }
      else
      {
        x = 32 * (potIndex-4);
        y = 120;
      }
      //tft.fillRect(32 * potIndex, 32, 32, 32, ILI9341_BLACK);
      //tft.setCursor(32 * potIndex, 32);
      //tft.setTextSize(1);
      //tft.setTextColor(ILI9341_WHITE);
      //tft.print(pots[potIndex].getValue());

      tft.fillRect(x, y, 32, 32, ILI9341_BLACK);
      tft.fillArc(x + 16, y+16, 16, 4, 0, map(pots[potIndex].getValue(), 0, 1023, 0, 360), ILI9341_WHITE);
      tft.setCursor(x+10, y+14);

      tft.setTextColor(ILI9341_WHITE);
      tft.print(map(pots[potIndex].getValue(), 0, 1023, 0, 100));
      //tft.fillRect((32*potIndex) + 4, 240 - map(pots[potIndex].getValue(), 0, 1024, 0, 120), 24, map(pots[potIndex].getValue(), 0, 1024, 0, 120), ILI9341_RED);
    }
    if (++potIndex == 8)
      potIndex = 0;
  }*/


#endif