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
AudioSynthWaveform       waveform1;      //xy=505.50000762939453,500.00000762939453
AudioSynthWaveformSineModulated sine_fm1;       //xy=669.5000114440918,513.2500057220459
AudioEffectBitcrusher    bitcrusher1;    //xy=672.0000076293945,562.5000076293945
AudioMixer4              mixer1;         //xy=825.0000114440918,501.25000762939453
AudioFilterStateVariable filter1;        //xy=956.0000152587891,498.50000953674316
AudioAnalyzePeak         peak1;          //xy=1097.250015258789,427.5000047683716
AudioOutputPWM           pwm1;           //xy=1099.750015258789,496.25000762939453
AudioAnalyzeRMS          rms1;           //xy=1100.000015258789,460.7500057220459
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform1, sine_fm1);
AudioConnection          patchCord3(waveform1, bitcrusher1);
AudioConnection          patchCord4(sine_fm1, 0, mixer1, 1);
AudioConnection          patchCord5(bitcrusher1, 0, mixer1, 2);
AudioConnection          patchCord6(mixer1, 0, filter1, 0);
AudioConnection          patchCord7(filter1, 0, pwm1, 0);
AudioConnection          patchCord8(filter1, 0, rms1, 0);
AudioConnection          patchCord9(filter1, 0, peak1, 0);
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



  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);

  mixer1.gain(0, 1); //dry
  mixer1.gain(1, 0); //delay1
  mixer1.gain(2, 0); //bitcrusher

  filter1.frequency(200);
  filter1.resonance(5.0);

  bitcrusher1.bits(8);
  
  bitcrusher1.sampleRate(1000);
  
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


