#include "ControllerLink.h"

void AnalValueSource::changed()
{
	if (linkActive)
	{
		destination->setValueByIndex(this, destinationParameterIndex, mapMethod);
	}
}

void AnalValueSource::setLink(AnalValueDestination *dst, uint8_t idx, AnalLinkMapMethod method, bool active)
{
	destination = dst;
	destinationParameterIndex = idx;
	mapMethod = method;
	linkActive = active;
}

void AnalFilterDestination::setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method)
{
	const double cutoff = (src->getType() == binary) ? (src->getValue() ? 5000 : 20) : map(src->getValue(), 0, 1023, 20, 5000);
	const double reso = (src->getType() == binary) ? (src->getValue() ? 128.0 : 0) : map(src->getValue(), 0, 1023, 0, 128.0);
	const double octave = (src->getType() == binary) ? (src->getValue() ? 5.0 : 0) : map(src->getValue(), 0, 1023, 0, 5.0);
	switch (idx)
	{
		case FilterParameters::cutoffFrequency:
			filter.frequency(cutoff);
			break;
		case FilterParameters::resonance:
			filter.resonance(reso);
			break;
		case FilterParameters::octaveControl:
			filter.octaveControl(octave);
			break;
		default:
			break;
	}
}

void AnalSynthWaveformDestiation::setValueByIndex(AnalValueSource *src, const uint8_t idx, const AnalLinkMapMethod method)
{
	switch(idx)
	{
		case WaveformParameters::shape:
			waveform.begin(map(src->getValue(), 0, 1023, 0, 8));
			break;
		case WaveformParameters::frequency:
			waveform.frequency(map(src->getValue(), 0, 1023, 0, AUDIO_SAMPLE_RATE_EXACT/2));
			break;
		case WaveformParameters::amplitude:
			waveform.amplitude(map(src->getValue(), 0, 1023, 0.0, 1.0));
			break;
		case WaveformParameters::phase:
			waveform.phase(map(src->getValue(), 0, 1023, 0.0, 360.0));
			break;
		case WaveformParameters::offset:
			waveform.offset(map(src->getValue(), 0, 1023, -1.0, 1.0));
			break;
		case WaveformParameters::pulseWidth:
			waveform.pulseWidth(map(src->getValue(), 0, 1023, 0.0, 1.0));
			break;
		default:
			break;
	}
}