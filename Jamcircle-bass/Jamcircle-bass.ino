//teensy 3.0 with pwm output

//todo
//latch to specific notes
//glide between notes
//remove high pitched peep -> hardware

//amp at freq
// 30  0.9
// 70  0.7
// 100 0.4
// 200 0.1

#define stickXpin A5
#define stickYpin A4
#define wheelpin1 14
#define wheelpin2 15

#include <Audio.h>
#include <Encoder.h>
#include "effect_waveshaper.h"
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=393,485
AudioSynthWaveform       waveform2;      //xy=501,342
AudioFilterStateVariable filter1;        //xy=531,481
AudioEffectWaveshaper    waveshape1;     //xy=681,526
AudioEffectMultiply      multiply1;      //xy=717,391
AudioMixer4              mixer1;         //xy=860,505
AudioAnalyzePeak         peak1;          //xy=1101,355
AudioOutputPWM           pwm1;           //xy=1121,555
AudioAnalyzeRMS          rms1;           //xy=1125,392
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform2, 0, multiply1, 1);
AudioConnection          patchCord3(filter1, 0, mixer1, 0);
AudioConnection          patchCord4(filter1, 0, multiply1, 0);
AudioConnection          patchCord5(filter1, 0, waveshape1, 0);
AudioConnection          patchCord6(waveshape1, 0, mixer1, 2);
AudioConnection          patchCord7(multiply1, 0, mixer1, 1);
AudioConnection          patchCord8(mixer1, pwm1);
AudioConnection          patchCord9(mixer1, peak1);
AudioConnection          patchCord10(mixer1, rms1);
// GUItool: end automatically generated code
float amp = 0;

float WAVESHAPE_EXAMPLE[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.488,
  -0.396,
  -0.320,
  -0.228,
  -0.122,
  0,
  0.122,
  0.228,
  0.320,
  0.396,
  0.488,
  0.549,
  0.579,
  0.588
};

Encoder myEnc(wheelpin1, wheelpin2);
long oldPosition  = -999;
int speedVal = 0;
long newPosition = 0;

//settings
float ampli = 1; // general amplitude modifier
int handleMiddlePoint = 600;
int BPM = 100;

elapsedMillis speedTimer;
#define speedUpdateTime 10

elapsedMillis handleTimer;
#define handleUpdateTime 30

elapsedMillis debugUpdateTimer;
#define debugUpdateTime 50//in ms



void setup() {
  Serial.begin(9600);
  AudioMemory(20);
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.amplitude(ampli);


  waveform2.begin(WAVEFORM_SINE);
  waveform2.frequency(4 * BPM / 60);
  waveform2.amplitude(1);

  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);

  mixer1.gain(0, 1); //dry
  mixer1.gain(1, 0); //delay1
  mixer1.gain(2, 0); //bitcrusher

  filter1.frequency(200);
  filter1.resonance(5.0);

  //bitcrusher1.bits(6);
  //waveshape1.shape(WAVESHAPE_EXAMPLE, 17);
  //delay1.delay(0, 150);

  //delay1.delay(0, 300);
}


void loop() {
  speedUpdate();
  handleUpdate();
  encoderUpdate();
  debugUpdate();
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  float val = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return constrain(val, min(out_min, out_max), max(out_min, out_max));
}

void encoderUpdate() {
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    //Serial.println(newPosition);
  }
}


