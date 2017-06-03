//todo
//stabalize touch input and calibrate -> to tone on
//rhythm tables with one_in()
//tweaking the tones with the knobs
//volume input with threshold

#include <Audio.h>
#include <Bounce2.h>

#define volumepot A9
#define recalibrateButtonPin 22
Bounce recalibrateButton = Bounce();
int touchPin[] = {17, 18, 19};
int faderPin[] = {A0, A1, A2};
#define mod1_0 12
#define mod1_1 11
#define mod1_2 10
#define mod1_3 9
#define mod2 A7
#define mod3_0 2
#define mod3_1 3


// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum1;          //xy=943,456
AudioSynthSimpleDrum     drum3;          //xy=945,546
AudioSynthSimpleDrum     drum2;          //xy=946,502
AudioMixer4              mixer1;         //xy=1102,505
AudioOutputAnalog        dac1;           //xy=1259,528
AudioConnection          patchCord1(drum1, 0, mixer1, 0);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum2, 0, mixer1, 1);
AudioConnection          patchCord4(mixer1, dac1);
// GUItool: end automatically generated code

elapsedMillis audioUpdateTimer;
#define BPM 120

#define recalibrateButtonPushTime 2000

elapsedMillis debugUpdateTimer;
#define debugUpdateTime 50//in ms

elapsedMillis touchUpdateTimer;
#define touchUpdateTime 3//in ms
#define touchAveraging 25//readings to average over
#define touchRange 100//range
#define touchThreshold 5//threshold value
#define baselineReadings 100//the amount of readings overwhich to take the average
int bufferPos = 0;
int pinBuffer[3][touchAveraging];
int pinAverage[] = {0, 0, 0};
int pinBaseline[] = {0, 0, 0};

elapsedMillis inputUpdateTimer;
#define inputUpdateTime 30//in ms

int faderCalibration[] ={4000,3830,3700,2000};
int faderPos[]={0,0,0};

void setup() {
  analogReadResolution(12);
  Serial.begin(9600);
  AudioMemory(10);

  pinMode(volumepot, INPUT);
  pinMode(recalibrateButtonPin, INPUT_PULLUP);
  recalibrateButton.attach(recalibrateButtonPin);
  recalibrateButton.interval(recalibrateButtonPushTime);
  pinMode(touchPin[0], INPUT);
  pinMode(touchPin[1], INPUT);
  pinMode(touchPin[2], INPUT);
  pinMode(faderPin[0], INPUT);
  pinMode(faderPin[1], INPUT);
  pinMode(faderPin[2], INPUT);
  pinMode(mod1_0, INPUT_PULLUP);
  pinMode(mod1_1, INPUT_PULLUP);
  pinMode(mod1_2, INPUT_PULLUP);
  pinMode(mod1_3, INPUT_PULLUP);
  pinMode(mod2, INPUT);
  pinMode(mod3_0, INPUT_PULLUP);
  pinMode(mod3_1, INPUT_PULLUP);

  //bliep
  drum1.frequency(1200);
  drum1.length(150);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.0);

  //bassdrum
  drum2.frequency(60);
  drum2.length(1500);
  drum2.secondMix(0.0);
  drum2.pitchMod(0.55);

  //bloop
  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);

  //delay(1000);
  setupPads();
}

void loop() {
  
  inputUpdate();
  readTouchpads();
  audioStuff();
  debugUpdate();
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  float val = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return constrain(val, min(out_min, out_max), max(out_min, out_max));
}
