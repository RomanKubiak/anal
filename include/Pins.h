#ifndef pins_h_
#define pins_h_

struct AnalPin
{
  AnalPin(const char *_name, const uint8_t _pin)
  : name(_name), pin(_pin) {}
  const char *name;
  uint8_t pin;
};

#endif