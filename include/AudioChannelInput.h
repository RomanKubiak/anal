#ifndef _audio_input_channel_h
#define _audio_input_channel_h

AudioMux inMuxL;
AudioFilterStateVariable inFilterL;
AudioMixer4              inMixerFilterL;
AudioEffectGranular      inGranularL;
AudioSynthWaveform       inWaveformL;
AudioEffectMultiply      inMultiplyL;

AnalFilterDestination inFilterLWrapper(inFilterL);
AnalMixer4Destination inMixerFilterLWrapper(inMixerFilterL);
AnalSynthWaveformDestiation inWaveformLWrapper(inWaveformL);

int16_t granularMemoryL[GRANULAR_MEMORY_SIZE];

void beginInputL()
{
	inGranularL.begin(granularMemoryL, GRANULAR_MEMORY_SIZE);
	inWaveformL.begin(1.0, 50.0, WAVEFORM_SINE);
}
#endif