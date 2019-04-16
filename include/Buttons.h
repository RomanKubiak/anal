#ifndef buttons_h_
#define buttons_h_
#include <XPT2046_Touchscreen.h>
#include <Metro.h>
#include "Bounce2.h"
#include "Pins.h"

// BUTTONS
#define ANAL_BUTTON_COUNT 7
#define DEBOUNCE_TIME 15
#define ANAL_BUTTON_METRO_TIMER 15

class AnalButton : public Bounce
{
  public:
    AnalButton(AnalPin pin, int time): name(pin.name)
    { 
      attach(pin.pin, INPUT_PULLUP);
      interval(time); 
    }
    bool readCurrentState() { return (digitalReadFast(pin)); }
    const char *name;
};

class AnalButtons
{
  public:
    AnalButtons();
    void update();
    void begin();
    AnalButton *getButton(const uint8_t button_index);
    bool isDown(const char *name);
    bool changed() { return (buttonsChanged); }
  private:
    AnalButton *buttons[ANAL_BUTTON_COUNT];
    uint8_t currentButtonToUpdate;
    Metro metro;
    bool buttonsChanged;
};

#endif