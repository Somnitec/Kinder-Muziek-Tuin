//teensy 3.0 with pwm output

//todo
//latch to specific notes
//glide between notes
//remove high pitched peep

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
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=340,390
AudioSynthWaveform       waveform2;      //xy=448,247
AudioFilterStateVariable filter1;        //xy=478,386
AudioEffectBitcrusher    bitcrusher1;    //xy=648,438
AudioEffectMultiply      multiply1;      //xy=664,296
AudioMixer4              mixer1;         //xy=807,410
AudioAnalyzePeak         peak1;          //xy=1048,260
AudioAnalyzeRMS          rms1;           //xy=1072,297
AudioOutputPWM           pwm1;           //xy=1100,408
AudioConnection          patchCord1(waveform1, 0, filter1, 0);
AudioConnection          patchCord2(waveform2, 0, multiply1, 1);
AudioConnection          patchCord3(filter1, 0, bitcrusher1, 0);
AudioConnection          patchCord4(filter1, 0, mixer1, 0);
AudioConnection          patchCord5(filter1, 0, multiply1, 0);
AudioConnection          patchCord6(bitcrusher1, 0, mixer1, 2);
AudioConnection          patchCord7(multiply1, 0, mixer1, 1);
AudioConnection          patchCord8(mixer1, pwm1);
AudioConnection          patchCord9(mixer1, peak1);
AudioConnection          patchCord10(mixer1, rms1);
// GUItool: end automatically generated code


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
  waveform2.frequency(2 * BPM / 60);
  waveform2.amplitude(1);

  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);

  mixer1.gain(0, 1); //dry
  mixer1.gain(1, 0); //delay1
  mixer1.gain(2, 0); //bitcrusher

  filter1.frequency(200);
  filter1.resonance(5.0);

  bitcrusher1.bits(6);

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

void encoderUpdate(){
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    //Serial.println(newPosition);
  }
}


