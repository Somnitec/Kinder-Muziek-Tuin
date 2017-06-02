#include <Audio.h>

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



void setup() {
  AudioMemory(10);

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);
  
  drum2.frequency(1200);
  drum2.length(150);
  drum2.secondMix(0.0);
  drum2.pitchMod(0.0);
  
  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);
}

void loop() {
  // put your main code here, to run repeatedly:

}
