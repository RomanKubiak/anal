#include "Touchscreen.h"

#define TS_CS_PIN  29
#define TS_IRQ_PIN 30

AnalTouch::AnalTouch() : 
  touchscreen(TS_CS_PIN, TS_IRQ_PIN),
  bouncedTouch(touchscreen),
  axisX(0,false),
  axisY(0,false)
{
}

void AnalTouch::begin()
{
  touchscreen.begin();
  touchscreen.setRotation(3);
  bouncedTouch.attach(0);
  bouncedTouch.interval(15);
}

void AnalTouch::update()
{
  touchscreenTouched = false;
  touchscreenDragged = false;
  
  bouncedTouch.update();

  if (bouncedTouch.rose() || bouncedTouch.fell())
  {
    touchscreenTouched = true;
  }

  TS_Point currentTouch = touchscreen.getPoint();
  axisX.update(map(currentTouch.x, 200, 3950, 0, 320));
  axisY.update(map(currentTouch.y, 400, 3700, 0, 240));

  if (axisX.hasChanged() || axisY.hasChanged())
  {
    touchscreenDragged = true;
  }
}

int AnalTouch::getX()
{
  return (axisX.getValue());
}

int AnalTouch::getY()
{
  return (axisY.getValue());
}