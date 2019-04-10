#include "Utils.h"

static Metro loadMetro              = Metro(100);
static uint8_t lastCpu, lastMem;

void _d(const char *data)
{
  extern ILI9341_t3 tft;
  tft.fillRect(0, 120, 320, 12, ILI9341_BLACK);
  tft.setCursor(0, 120);
  tft.print(data);
}

void printSystemLoad(ILI9341_t3 &g, int x, int y, const char *data)
{
  if (!loadMetro.check())
    return;

  uint8_t nowCpu, nowMem;
  nowCpu = (uint8_t)AudioProcessorUsageMax();
  nowMem = (uint8_t)AudioMemoryUsageMax();
  if (nowCpu != lastCpu || nowMem != lastMem)
  {
    char buf[128];
    sprintf(buf, "cpu: %02d mem: %01d %s", nowCpu, nowMem, data);
    g.fillRect(x,y,200,12, ILI9341_BLACK);
    g.setTextColor(ILI9341_WHITE);
    g.setTextSize(1);
    g.setCursor(x,y);
    g.print(buf);
    lastCpu = nowCpu;
    lastMem = nowMem;
  }
  AudioProcessorUsageMaxReset();
}

void displayPeak(ILI9341_t3 &g, int x, int y, int width, int height, AudioAnalyzePeak &peak)
{
  if (peak.available())
  {
    float value = peak.read();
    g.fillRect(x, y, width, height, ILI9341_BLACK);
    g.fillRect(x, y +(height * value), width, height * value, ILI9341_WHITE);
    g.setCursor(x,y);
    g.print(value);
  } 
}