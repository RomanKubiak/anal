#include "Touchscreen.h"
#include <ResponsiveAnalogRead.h>

static ResponsiveAnalogRead ts_readX(0, false);
static ResponsiveAnalogRead ts_readY(0, false);

void beginTouch()
{
  extern BouncedTouch bouncedTouch;
  bouncedTouch.attach(0);
  bouncedTouch.interval(15);
}

void updateTouch(TouchData &data)
{
  extern BouncedTouch bouncedTouch;
  bouncedTouch.update();
  TS_Point currentTouch = bouncedTouch.getTouchScreen().getPoint();
      ts_readX.update(map(currentTouch.x,200,3950,0,320));
      ts_readY.update(map(currentTouch.y, 200, 3800, 0, 240));
      if (ts_readX.hasChanged() || ts_readY.hasChanged())
      {
        data.y = ts_readX.getValue();
        data.y = ts_readY.getValue();
        data.hasChanged = true;
      }
}