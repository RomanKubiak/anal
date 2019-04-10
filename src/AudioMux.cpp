#include "AudioMux.h"

AudioMux::AudioMux(void) : AudioStream(CHANNELS, inputQueueArray)
{
	reset();
}

void AudioMux::update(void)
{
	audio_block_t *block;

	for (int8_t inputChannel=0; inputChannel<CHANNELS; inputChannel++)
	{
        if (routeMap[inputChannel] >= 0)
        {
			block = receiveReadOnly(inputChannel);
			if (block)
			{
                transmit(block, routeMap[inputChannel]);
                release(block);
			}
		}
	}
}

void AudioMux::setConnection (int8_t inp, int8_t outp, bool connect)
{
	routeMap[inp] = connect ? outp : -1;
}

void AudioMux::printRouteMap()
{
	for (int8_t i=0; i<CHANNELS; i++)
	{
		Serial.print(i);
		Serial.print("->");
		Serial.println(routeMap[i]);
	}
}

void AudioMux::reset()
{
    for (int8_t i=0; i<CHANNELS; i++)
        routeMap[i] = -1;
}
