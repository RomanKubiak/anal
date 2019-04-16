#ifndef controller_link_h
#define controller_link_h

#include <Audio.h>

#define MAX_GLOBAL_LINKS 			256
#define MAX_DESTINATIONS_PER_SOURCE 16
class AnalLinkManager;

enum AnalLinkMapMethod
{
	unknownMethod
};

enum SourceValueType
{
	int8bit,
	int10Bit,
	int16Bit,
	int24bit,
	int32bit,
	binary,
	binaryReverse,
	string,
	floatingPoint
};

enum FilterParameters
{
	cutoffFrequency,
	resonance,
	octaveControl,
	numParams
};

enum WaveformParameters
{
	shape,
	frequency,
	amplitude,
	phase,
	offset,
	pulseWidth
};
enum Mixer4Channel
{
	ch0,
	ch1,
	ch2,
	ch3,
	numChannels
};

class AnalValueSource;

class AnalValueDestination
{
	public:
		AnalValueDestination() {}
		virtual void setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method) = 0;
};

class AnalValueSource
{
	public:
		AnalValueSource() {}
		virtual const double getValue() = 0;
		virtual const char *getName() = 0;
		virtual const SourceValueType getType() = 0;
		void changed();
		void setLink(AnalValueDestination *dst, uint8_t idx, AnalLinkMapMethod method=unknownMethod, bool active=true);
		AnalValueDestination *destination;
		uint8_t destinationParameterIndex;
		AnalLinkMapMethod mapMethod;
		bool linkActive;
};

class AnalFilterDestination : public AnalValueDestination
{
	public:
		AnalFilterDestination(AudioFilterStateVariable &_filter) : filter(_filter) {}
		void setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method);

	private:
		AudioFilterStateVariable &filter;
};

class AnalMixer4Destination : public AnalValueDestination
{
	public:
		AnalMixer4Destination(AudioMixer4 &_mixer) : mixer(_mixer) {}
		void setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method)
		{
			mixer.gain(idx, map(src->getValue(), 0.0, 1023.0, 0.0f, 1.0f));
		}

	private:
		AudioMixer4 &mixer;
};

class AnalSynthWaveformDestiation : public AnalValueDestination
{
	public:
		AnalSynthWaveformDestiation(AudioSynthWaveform &_waveform) : waveform(_waveform) {}
		void setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method);

	private:
		AudioSynthWaveform &waveform;
};

/*
class AnalLinkManager
{
	public:
		AnalLinkManager() {}
		AnalLinkManager(AnalLinkManager const&);
        void operator=(AnalLinkManager const&);
		static AnalLinkManager& getInstance()
		{
			static AnalLinkManager instance;
			return instance;
		}

		void sourceChanged(AnalValueSource *sourceThatChanged);
		void setLink(AnalValueSource *src, AnalValueDestination *dst, uint8_t idx, AnalLinkMapMethod method=unknownMethod, bool active=true);
};
*/
#endif
