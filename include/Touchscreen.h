#ifndef touchscreen_h_
#define touchscreen_h_
#include <XPT2046_Touchscreen.h>
#include <Bounce2.h>
class BouncedTouch : public Bounce
{
  public:
    BouncedTouch(XPT2046_Touchscreen &_ts) : ts(_ts) {}
    void setPinMode(int pin, int mode){
    }
    bool readCurrentState(){
      return (ts.touched()); 
    }
    XPT2046_Touchscreen &getTouchScreen() { return (ts); }

  private:
    XPT2046_Touchscreen &ts;
};


struct TouchData
{
  uint16_t x;
  uint16_t y;
  bool hasChanged;
};

void beginTouch();
void updateTouch(TouchData &data);

#endif