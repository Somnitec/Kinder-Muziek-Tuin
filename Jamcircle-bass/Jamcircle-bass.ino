//teensy 3.0 with pwm output

//todo
//wheel to speed to filter
//latch to specific notes
//glide between notes
//handle up-> flanger, handle down -> bitcrusher
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
AudioSynthWaveform       waveform1;      //xy=450,383
AudioEffectFlange        flange1;        //xy=646,355
AudioEffectBitcrusher    bitcrusher1;    //xy=648,438
AudioMixer4              mixer1;         //xy=807,410
AudioFilterStateVariable filter1;        //xy=962,422
AudioOutputPWM           pwm1;           //xy=1100,408
AudioConnection          patchCord1(waveform1, flange1);
AudioConnection          patchCord2(waveform1, bitcrusher1);
AudioConnection          patchCord3(waveform1, 0, mixer1, 0);
AudioConnection          patchCord4(flange1, 0, mixer1, 1);
AudioConnection          patchCord5(bitcrusher1, 0, mixer1, 2);
AudioConnection          patchCord6(mixer1, 0, filter1, 0);
AudioConnection          patchCord7(filter1, 0, pwm1, 0);
// GUItool: end automatically generated code
Encoder myEnc(wheelpin1, wheelpin2);
long oldPosition  = -999;

float ampli = 1; 

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.frequency(20);
  waveform1.amplitude(0.01);
  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);

  mixer1.gain(0, 1); //dry
  mixer1.gain(1, 0); //flanger
  mixer1.gain(2, 0); //bitcrusher

  filter1.frequency(100);
  filter1.resonance(5.0);
}

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  //Serial.printf(analogRead(stickXpin),analogRead(stickYpin));

  int freq = map(analogRead(stickXpin), 100, 1000, 20, 100);
  //float amp = fmap(analogRead(stickYpin), 100, 800, 1, 0) * fmap(freq, 30, 200, 0.9, 0.1);
  float amp = ampli * fmap(freq, 30, 200, 0.9, 0.1);
  int filter = map(analogRead(stickYpin), 100, 1000, 20, 400);
  Serial.print(filter);
  Serial.print("\t");
  Serial.print(freq);
  Serial.print("\t");
  Serial.println(amp);
  delay(10);
  waveform1.frequency(freq);
  filter1.frequency(filter);
  //waveform1.amplitude(amp);
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  float value =  (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return value;//constrain(value, out_min, out_max);
}

