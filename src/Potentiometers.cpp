#include "Potentiometers.h"
#include "Utils.h"

const AnalPin analPotentiometerPins[ANAL_POTENTIOMETER_COUNT] =
{
  { "yellow", 36},
  { "white", 38},
  { "blue", 39},
  { "green", 33}
};

AnalPotentiometers::AnalPotentiometers() : metro(Metro(ANAL_POTENTIOMETER_METRO_TIMER))
{
  for (int i=0; i<ANAL_POTENTIOMETER_COUNT; i++)
  {
    potentiometers[i] = new AnalPotentiometer(analPotentiometerPins[i], ANAL_POTENTIOMETER_SNAP);
  }
}

AnalPotentiometer *AnalPotentiometers::getPot(const uint8_t potentiometerIndex)
{
  return (potentiometers[potentiometerIndex]);
}

void AnalPotentiometers::update()
{
  if (metro.check())
  {
    metro.reset();
    potentiometers[currentPotentiometerToUpdate]->update();
    if (potentiometers[currentPotentiometerToUpdate]->hasChanged())
    {
      _d(potentiometers[currentPotentiometerToUpdate]->name);
      potentiometersChanged = true;
      potentiometers[currentPotentiometerToUpdate]->changed();
    }
    else
    {
      potentiometersChanged = false;
    }

    currentPotentiometerToUpdate++;

    if (currentPotentiometerToUpdate == ANAL_POTENTIOMETER_COUNT)
      currentPotentiometerToUpdate = 0;
  }
}