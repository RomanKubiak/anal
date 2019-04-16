#ifndef touchscreen_h_
#define touchscreen_h_
#include <XPT2046_Touchscreen.h>
#include <Bounce2.h>
#include <ResponsiveAnalogRead.h>

class BouncedTouch : public Bounce
{
  public:
    BouncedTouch(XPT2046_Touchscreen &_ts) : ts(_ts) {}
    void setPinMode(int pin, int mode){
    }
    bool readCurrentState(){
      return (ts.touched()); 
    }

  private:
    XPT2046_Touchscreen &ts;
};


class AnalTouch
{
  public:
    AnalTouch();
    void update();
    bool changed() { return (touchscreenTouched || touchscreenDragged); }
    bool dragged() { return (touchscreenDragged); }
    bool touched() { return (touchscreenTouched); }
    void begin();
    int getX();
    int getY();
  private:
    XPT2046_Touchscreen touchscreen;
    BouncedTouch bouncedTouch;
    ResponsiveAnalogRead axisX;
    ResponsiveAnalogRead axisY;
    bool touchscreenTouched;
    bool touchscreenDragged;
};

#endif