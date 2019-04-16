#include "Buttons.h"
#include "Utils.h"

const AnalPin analButtonPins[ANAL_BUTTON_COUNT] =
{
  { "yellow", 35},
  { "white", 37},
  { "blue", 28},
  { "green", 27},
  { "down", 34},
  { "up", 4},
  { "ok", 2}
};

AnalButtons::AnalButtons() : 
  currentButtonToUpdate(0), metro(Metro(ANAL_BUTTON_METRO_TIMER)), buttonsChanged(false){}

void AnalButtons::begin()
{
  for (int i=0; i<ANAL_BUTTON_COUNT; i++)
  {
    buttons[i] = new AnalButton(analButtonPins[i], DEBOUNCE_TIME);
  }
}

AnalButton *AnalButtons::getButton(const uint8_t button_index)
{
  return buttons[button_index];
}

bool AnalButtons::isDown(const char *name)
{
  for (int i=0; i<ANAL_BUTTON_COUNT; i++)
  {
    if (strcmp(buttons[i]->name, name) == 0)
    {
      return (buttons[i]->readCurrentState() == false);
    }
  }

  return (false);
}

void AnalButtons::update()
{
  if (metro.check())
  {
    metro.reset();
    buttons[currentButtonToUpdate]->update();

    if (buttons[currentButtonToUpdate]->fell() || buttons[currentButtonToUpdate]->rose())
    {
      buttonsChanged = true;
    }
    else
      buttonsChanged = false;

    currentButtonToUpdate++;

    if (currentButtonToUpdate == ANAL_BUTTON_COUNT)
      currentButtonToUpdate = 0;
  }
}