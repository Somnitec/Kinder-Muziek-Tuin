

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform4;      //xy=439,450
AudioSynthWaveform       waveform2;      //xy=440,373
AudioSynthWaveform       waveform3;      //xy=440,411
AudioSynthWaveform       waveform1;      //xy=442,332
AudioMixer4              mixer1;         //xy=606,390
AudioOutputPWM           pwm1;           //xy=726,390
AudioConnection          patchCord1(waveform4, 0, mixer1, 3);
AudioConnection          patchCord2(waveform2, 0, mixer1, 1);
AudioConnection          patchCord3(waveform3, 0, mixer1, 2);
AudioConnection          patchCord4(waveform1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, pwm1);
// GUItool: end automatically generated code



int toneSet[7][2] = {
  {NOTE_C3, NOTE_E3},
  {NOTE_A3, NOTE_C3},
  {NOTE_B3, NOTE_D3},
  {NOTE_E3, NOTE_G3},
  {NOTE_D3, NOTE_F3},
  {NOTE_F3, NOTE_A3},
  {NOTE_B3, NOTE_G3}
  };


elapsedMicros audioUpdateTimer;
void audioUpdate() {
  if (audioUpdateTimer > audioUpdateTime) {
    audioUpdateTimer = 0;
    setAmplitudes();
  }
}

void setFrequencies() {  
  waveform1.frequency(NOTE_C3);
  waveform2.frequency(NOTE_E3);
  waveform3.frequency(NOTE_G3);
  waveform4.frequency(NOTE_B4);

}

void setAmplitudes() {
waveform1.amplitude(.1);
  waveform2.amplitude(.1);
  waveform3.amplitude(.1);
  waveform4.amplitude(.1);
/*


  mixer1.gain(0, sineMaxAmplitude * ampl[0]);
  mixer1.gain(1, sineMaxAmplitude * ampl[1]);
  mixer1.gain(2, sineMaxAmplitude * ampl[2]);
  mixer1.gain(3, sineMaxAmplitude * ampl[3]);
  mixer2.gain(0, sineMaxAmplitude * ampl[4]);
  mixer2.gain(1, sineMaxAmplitude * ampl[5]);
  mixer2.gain(2, sineMaxAmplitude * ampl[6]);
  mixer2.gain(3, sineMaxAmplitude * ampl[7]);
  mixer3.gain(0, sineMaxAmplitude * ampl[8]);
  mixer3.gain(1, sineMaxAmplitude * ampl[9]);
  mixer3.gain(2, sineMaxAmplitude * ampl[10]);
*/
}

void turnOffAll(){
}


