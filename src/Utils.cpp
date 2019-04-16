#include "Utils.h"
static Metro debugMetro = Metro(50);
void printHelper(const char *str)
{
  extern AnalDisplay analDisplay;
  analDisplay.device.fillRect(0,228,64,12,ILI9341_BLACK);
  analDisplay.device.setCursor(0,228);
  analDisplay.device.print(str);
}

void showDebugPage()
{
  extern AnalButtons analButtons;
  extern AnalPotentiometers analPotentiometers;
  extern AnalDisplay analDisplay;
  ILI9341_t3 &device = analDisplay.device;

  if (analButtons.changed())
    {
        for (int i=0; i<ANAL_BUTTON_COUNT; i++)
        {
            AnalButton *btn = analButtons.getButton(i);
            if (btn)
            {
                device.setCursor(i*32,0);
                device.fillRect(i*32,0,32,12, ILI9341_BLACK);
                device.print(i);
                device.print("=");
                device.print(btn->fell() ? "v" : "^");
                device.print(" ");
            }
        }
    }
    
    if (analPotentiometers.changed())
    {
        for (int i=0; i<ANAL_POTENTIOMETER_COUNT; i++)
        {
            AnalPotentiometer *pot = analPotentiometers.getPot(i);
            if (pot)
            {
                device.setCursor(i*64,16);
                device.fillRect(i*64,16,64,12, ILI9341_BLACK);
                device.print(i);
                device.print("=");
                device.print(pot->getValue());
                device.print(" ");
            }
        }
    }
    if (debugMetro.check())
    {
        printHelper(String(millis()).c_str());
        device.fillRect(0,32,128,32, ILI9341_BLACK);
        device.setCursor(0,32);
        device.print("x=");
        device.print(analDisplay.getTouch().getX());
        device.print(" y=");
        device.print(analDisplay.getTouch().getY());
    }
}