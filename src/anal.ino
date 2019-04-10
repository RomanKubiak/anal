#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=85.0000228881836,305.0000057220459
AudioOutputUSB           usb1;           //xy=724.0039024353027,391.00400829315186
AudioControlSGTL5000     sgtl5000_1;     //xy=83.00389862060547,225.00390875339508
// GUItool: end automatically generated code

#include "Utils.h"
#include "ILI9341_t3.h"
#include "FifteenStep.h"
#include "SequencerUI.h"
#include "wavTrigger.h"
#include "AudioMux.h"
#define GRANULAR_MEMORY_SIZE 12800

#include "AudioChannelInput.h"

#define TS_CS_PIN  29
#define TS_IRQ_PIN 30
XPT2046_Touchscreen ts(TS_CS_PIN, TS_IRQ_PIN);

#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

AnalButtons analButtons;
AnalPotentiometers analPotentiometers;
TouchData touchData;

char wavTriggerVersion[VERSION_STRING_LEN];
wavTrigger wTrig;
BouncedTouch bouncedTouch(ts);

SequencerUI seq1(tft, 0, 16, 128, 8, 16, color_darker(ILI9341_YELLOW, 10));
SequencerUI seq2(tft, 0, 32, 128, 8, 16, ILI9341_WHITE);
SequencerUI seq3(tft, 0, 48, 128, 8, 16, ILI9341_BLUE);
SequencerUI seq4(tft, 0, 64, 128, 8, 16, ILI9341_GREEN);

Metro debug = Metro(25);

void setup()
{
	Serial.begin(9600);
	tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0,0);
    tft.println("init");
	ts.begin();
    ts.setRotation(3);
    delay(150);

    tft.println("audio");
	AudioNoInterrupts();
	AudioMemory(32);
    
    sgtl5000_1.enable();
    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    sgtl5000_1.volume(0.5);

    /*AnalLinkManager::getInstance().setLink(analPotentiometers.getPot(0), &filter1_wrapper, (uint8_t)FilterParameters::cutoffFrequency);
    AnalLinkManager::getInstance().setLink(analPotentiometers.getPot(1), &filter1_wrapper, (uint8_t)FilterParameters::resonance);
    AnalLinkManager::getInstance().setLink(analPotentiometers.getPot(2), &filter1_wrapper, (uint8_t)FilterParameters::octaveControl);
    AnalLinkManager::getInstance().setLink(analPotentiometers.getPot(3), &mixer_filter_wrapper, 1);*/

    delay(250);
    tft.print("wavTrigger: ");
    wTrig.start();
    delay(10);
    wTrig.stopAllTracks();
    wTrig.samplerateOffset(0);
    wTrig.setReporting(true);
    if (wTrig.getVersion(wavTriggerVersion, VERSION_STRING_LEN))
    {
      tft.print(wavTriggerVersion);
      tft.print(" ");
      tft.println(wTrig.getNumTracks());
    }

    delay(150);
    tft.println("touch");
    beginTouch();
    delay(150);
    tft.println("pots");
    delay(150);
    tft.println("buttons");
    delay(150);
    tft.println("leds");
    beginLeds();
    delay(150);
    tft.println("sequencers");

    seq1.begin();
    seq1.setTempo(120);
    seq1.setStep(0,1,1,1);
    seq1.setStep(4,1,1,1);
    seq1.setStep(8,1,1,1);
    seq1.setStep(12,1,1,1);
    seq2.begin();
    seq2.setTempo(120);
    seq3.begin();
    seq3.setTempo(120);
    seq4.begin();
    seq4.setTempo(120);
    

    delay(150);
    tft.fillScreen(ILI9341_BLACK);
    delay(500);
    AudioInterrupts();
}

void loop()
{
	updateTouch(touchData);
	analPotentiometers.update();
	analButtons.update();
    wTrig.update();
    show_debug_screen();
}

void show_debug_screen()
{
	if (analButtons.changed())
    {
        for (int i=0; i<ANAL_BUTTON_COUNT; i++)
        {
            AnalButton *btn = analButtons.getButton(i);
            if (btn)
            {
                tft.setCursor(i*32,0);
                tft.fillRect(i*32,0,32,12, ILI9341_BLACK);
                tft.print(i);
                tft.print("=");
                tft.print(btn->fell() ? "v" : "^");
                tft.print(" ");
            }
        }
    }

    if (analPotentiometers.changed())
    {
        for (int i=0; i<ANAL_POTENTIOMETER_COUNT; i++)
        {
            AnalPotentiometer *pot = analPotentiometers.getPot(i);
            if (pot)
            {
                tft.setCursor(i*64,16);
                tft.fillRect(i*64,16,64,12, ILI9341_BLACK);
                tft.print(i);
                tft.print("=");
                tft.print(pot->getValue());
                tft.print(" ");
            }
        }
    }
	printSystemLoad(tft, 0, 240 - 16, wavTriggerVersion);
}