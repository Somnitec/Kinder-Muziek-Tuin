//teensy 3.0 with pwm output

#include <Audio.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=521,377
AudioOutputPWM           pwm1;           //xy=726,390
AudioConnection          patchCord1(waveform1, pwm1);
// GUItool: end automatically generated code


void setup() {
  AudioMemory(2);
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.frequency(20);
  waveform1.amplitude(0.01);
}

void loop() {
  delay(10);
}
