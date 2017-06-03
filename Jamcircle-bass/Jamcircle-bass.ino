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

#define volumepot A8

#define stickXpin A5
#define stickYpin A4
#define wheelpin1 14
#define wheelpin2 15


#define ledpin 13

#include <Audio.h>
#include <Encoder.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=614,334
AudioSynthWaveform       waveform2;      //xy=625,369
AudioSynthWaveform       waveform3;      //xy=645,399
AudioMixer4              mixer1;         //xy=949,344
AudioFilterStateVariable filter1;        //xy=1081,351
AudioAnalyzePeak         peak1;          //xy=1261,306
AudioOutputPWM           pwm1;           //xy=1263,375
AudioAnalyzeRMS          rms1;           //xy=1264,339
AudioConnection          patchCord1(waveform1, 0, mixer1, 0);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(waveform3, 0, mixer1, 2);
AudioConnection          patchCord4(mixer1, 0, filter1, 0);
AudioConnection          patchCord5(filter1, 0, pwm1, 0);
AudioConnection          patchCord6(filter1, 0, rms1, 0);
AudioConnection          patchCord7(filter1, 0, peak1, 0);
// GUItool: end automatically generated code
float amp = 0;

Encoder myEnc(wheelpin1, wheelpin2);
long oldPosition  = -999;
int speedVal = 0;
long newPosition = 0;

//settings
float ampli = 2; // general amplitude modifier
int handleMiddlePoint = 4096 / 2;

elapsedMillis speedTimer;
#define speedUpdateTime 10

elapsedMillis handleTimer;
#define handleUpdateTime 30

elapsedMillis debugUpdateTimer;
#define debugUpdateTime 50//in ms

int stickYread = 0;
int stickXread = 0;
float stickup = 0;
float stickdown = 0;

#define speedmodifier 0.01
float speedmod=0;

#define volumeThreshold 100 // if the volume button is not not changed by more then this, don't change the volume
int lastVolume=0;
float overalVolume =0;

void setup() {
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, HIGH);

  analogReadResolution(12);

  Serial.begin(9600);
  AudioMemory(20);
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.amplitude(ampli);

  waveform2.begin(WAVEFORM_SQUARE);
  waveform2.amplitude(ampli);

  waveform3.begin(WAVEFORM_SQUARE);
  waveform3.amplitude(ampli);



  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);

  mixer1.gain(0, 1); //basic note
  mixer1.gain(1, 0); //harmonic 1
  mixer1.gain(2, 0); //harmonic 2

  filter1.frequency(200);
  filter1.resonance(2.0);

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


