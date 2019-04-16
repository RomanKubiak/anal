#include "AudioInit.h"
#include "PageManager.h"
#include "Utils.h"
AnalDisplay analDisplay;
AnalPotentiometers analPotentiometers;
AnalButtons analButtons;
AnalPageManager analPageManager(analDisplay.device);

bool debug = true;
void setup()
{
	Serial.begin(9600);
    beginAudio();
    analDisplay.begin();
    analPotentiometers.begin();
    analButtons.begin();
    analPageManager.begin();
    if (analButtons.isDown("ok"))
        debug = true;
}

void loop()
{   
    analPotentiometers.update();
    analButtons.update();
    analDisplay.update();

    if (debug)
        showDebugPage();
}