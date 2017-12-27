#include <Audio.h>

#include <Encoder.h>



// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine5;          //xy=654,270
AudioSynthWaveformSine   sine1;          //xy=663,105
AudioSynthWaveformSine   sine2;          //xy=665,134
AudioSynthWaveformSine   sine7;          //xy=666,369
AudioSynthWaveformSine   sine6;          //xy=673,310
AudioSynthWaveformSine   sine8;          //xy=676,402
AudioSynthWaveformSine   sine3;          //xy=679,180
AudioSynthWaveformSine   sine4;          //xy=703,201
AudioSynthWaveformSine   sine9;          //xy=706,450
AudioSynthWaveformSine   sine13;         //xy=708,636
AudioSynthWaveformSine   sine10;         //xy=710,474
AudioSynthWaveformSine   sine14;         //xy=710,671
AudioSynthWaveformSine   sine11;         //xy=718,560
AudioSynthWaveformSine   sine12;         //xy=736,577
AudioMixer4              mixer3;         //xy=817,341
AudioMixer4              mixer2;         //xy=846,155
AudioMixer4              mixer5;         //xy=876,647
AudioMixer4              mixer4;         //xy=885,518
AudioMixer4              mixer1;         //xy=1104,345
AudioAnalyzePeak         peak1;          //xy=1261,306
AudioOutputAnalog           pwm1;           //xy=1263,375
AudioAnalyzeRMS          rms1;           //xy=1264,339
AudioConnection          patchCord1(sine5, 0, mixer3, 0);
AudioConnection          patchCord2(sine1, 0, mixer2, 0);
AudioConnection          patchCord3(sine2, 0, mixer2, 1);
AudioConnection          patchCord4(sine7, 0, mixer3, 2);
AudioConnection          patchCord5(sine6, 0, mixer3, 1);
AudioConnection          patchCord6(sine8, 0, mixer3, 3);
AudioConnection          patchCord7(sine3, 0, mixer2, 2);
AudioConnection          patchCord8(sine4, 0, mixer2, 3);
AudioConnection          patchCord9(sine9, 0, mixer4, 0);
AudioConnection          patchCord10(sine13, 0, mixer5, 0);
AudioConnection          patchCord11(sine10, 0, mixer4, 1);
AudioConnection          patchCord12(sine14, 0, mixer5, 1);
AudioConnection          patchCord13(sine11, 0, mixer4, 2);
AudioConnection          patchCord14(sine12, 0, mixer4, 3);
AudioConnection          patchCord15(mixer3, 0, mixer1, 1);
AudioConnection          patchCord16(mixer2, 0, mixer1, 0);
AudioConnection          patchCord17(mixer5, 0, mixer1, 3);
AudioConnection          patchCord18(mixer4, 0, mixer1, 2);
AudioConnection          patchCord19(mixer1, peak1);
AudioConnection          patchCord20(mixer1, rms1);
AudioConnection          patchCord21(mixer1, pwm1);
// GUItool: end automatically generated code

#define sensorAmount 7

#define sensorThreshold 10
#define sensorMax 10

#define ledPin 13
#define calibratePin 2

#define numReadings 100
#define numReadingsImmediate 100

int sensor[] = {18, 19, 22, 23, 15, 16, 17};
int readings[sensorAmount][numReadings];
int lowCal[sensorAmount];
int highCal[sensorAmount];
int average[sensorAmount];
int immediateAverage[sensorAmount];
int range[sensorAmount];
float ampl[sensorAmount];
float totalAverage;

float theAmpl[sensorAmount];
float amplNow[sensorAmount];
float glide = 10;

int readIndex = 0;

#define volumePin1 7
#define volumePin2 8
Encoder volumePot(volumePin1, volumePin2);


float tonesMaxAmplitude = 1.0 / sensorAmount + .03; //about one divided by the amount of tones available (.11 is the safest value)

#define debugUpdateTime 10//in ms
#define audioUpdateTime 10//in us
#define calibrationUpdateTime 5//in ms

#define sensorUpdateTime 100//in us


#define lowThreshold 5 //a value to reach before the thing gets triggered
#define maxRange 250//the maximum range of the sensors



#define autoCalibTime 3000 //ms how long the values should be stable before autoCalib
#define autoCalibRange 10 // how stable the values should be for the timer to start
#define autoCalibSoundRange 0.01 //how much the volume should stay the same for recalibration
#define calibCycles 50 // it will average this amount of cycles when calibrating




int volumeMod  = 0;

void setup() {
  initializingStuff();
}

void loop() {
  volumeStuff();
  sensorStuff();
  calibrationUpdate();
  audioUpdate();
  debugUpdate();
}

void volumeStuff() {
  long newPosition = volumePot.read();
  if (newPosition != volumeMod) {
    if (newPosition > 100) {
      volumePot.write(100);
      newPosition = 100;
    }
    if (newPosition < 0) {
      volumePot.write(0);
      newPosition = 0;
    }
    volumeMod = newPosition;
    mixer1.gain(0, volumeMod / 100.);
    mixer1.gain(1, volumeMod / 100.);
    mixer1.gain(2, volumeMod / 100.);
    mixer1.gain(3, volumeMod / 100.);
  }
}
