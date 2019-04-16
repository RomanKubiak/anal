#ifndef potentiometers_h_
#define potentiometers_h_

#include <Metro.h>
#include "ResponsiveAnalogRead.h"
#include "Pins.h"
#include "ControllerLink.h"

#define ANAL_POTENTIOMETER_COUNT 4
#define ANAL_POTENTIOMETER_METRO_TIMER 15
#define ANAL_POTENTIOMETER_SNAP 0.9

class AnalPotentiometer : public ResponsiveAnalogRead, public AnalValueSource
{
	public:
		AnalPotentiometer(AnalPin pot, double snap) 
			: ResponsiveAnalogRead(pot.pin, true), name(pot.name)
		{
			enableEdgeSnap();
    		setSnapMultiplier(snap);
		}

		const double getValue()
		{
			return (ResponsiveAnalogRead::getValue());
		}

		const char *getName()
		{
			return (name);
		}

		const SourceValueType getType() { return (int10Bit); }
		const char *name;
};

class AnalPotentiometers
{
	public:
		AnalPotentiometers();
		void update();
		AnalPotentiometer *getPot(const uint8_t potentiometerIndex);
		bool changed() { return (potentiometersChanged); }
		void begin();
	private:
		uint8_t currentPotentiometerToUpdate;
		AnalPotentiometer *potentiometers[ANAL_POTENTIOMETER_COUNT];
		Metro metro;
		bool potentiometersChanged;
};
#endif
