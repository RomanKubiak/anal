#ifndef mux_h_
#define mux_h_

#include "Arduino.h"
#include "AudioStream.h"

#define CHANNELS 16
class AudioMux : public AudioStream
{
	public:
		AudioMux(void);
		void update(void);
		void setConnection (int8_t inp, int8_t outp, bool connect);
		void printRouteMap();
        int8_t* getRouteMap() { return (routeMap); }
        void reset();
	private:
		audio_block_t *inputQueueArray[CHANNELS];
		int8_t routeMap[CHANNELS];
};

#endif
