#ifndef seq_ui_h_
#define seq_ui_h_

#include "Arduino.h"
#include <Audio.h>
#include <ILI9341_t3.h>
#include <SD.h>
#include "FifteenStep.h"

void stepHandler(int now, int prev, void *user);
void midiHandler(byte channel, byte command, byte arg1, byte arg2, void *user);

class SequencerUI
{
	public:
		SequencerUI(
			ILI9341_t3 &_g,
			uint16_t _x = 0,
			uint16_t _y = 0,
			uint16_t _width = 320,
			uint16_t _height = 16,
			uint8_t _steps = 16,
			uint16_t _stepBaseColor = 0xF800);

		void repaint();
		bool isValid() { return (!invalid); }
		void handleStepEvent(int _currentStep, int _previousStep);
		void handleMidiEvent(byte channel, byte command, byte arg1, byte arg2);
		void update();
		void setStep(int step, int channel, int pitch, int velocity);
		void begin()
		{
			core.begin(120, steps);
			core.setStepHandler(stepHandler, this);
			core.setMidiHandler(midiHandler, this);
		}

		void setTempo(int tempo)
		{
			core.setTempo(tempo);
		}

		void setSteps(int _steps)
		{ 
			steps = _steps;
			core.setSteps(steps);
			stepWidth = width / steps;
		}
	private:
		ILI9341_t3 &g;
		FifteenStep core;
		uint16_t x,y,width, height, stepWidth;
		uint8_t steps;
		uint16_t stepBaseColor;
		uint16_t stepBaseColorDaker;
		uint16_t stepBaseColorBrighter;
		uint16_t currentStep, previousStep;
		bool invalid;
		bool dead;
};

#endif