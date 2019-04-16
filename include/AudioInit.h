#ifndef _audio_init_h
#define _audio_init_h

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=85.0000228881836,305.0000057220459
//AudioOutputUSB           usb1;           //xy=724.0039024353027,391.00400829315186
AudioControlSGTL5000     sgtl5000_1;     //xy=83.00389862060547,225.00390875339508
// GUItool: end automatically generated code

static void beginAudio()
{
	AudioNoInterrupts();
	AudioMemory(32);
    sgtl5000_1.enable();
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000_1.volume(0.5);
    AudioInterrupts();
}

#endif