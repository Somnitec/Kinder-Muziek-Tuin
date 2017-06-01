int tones[] = {NOTE_C1,NOTE_D1,NOTE_E1,NOTE_G1,NOTE_A1,NOTE_C2,NOTE_D2,NOTE_E2,NOTE_G2,NOTE_A2,NOTE_C3};
int toneAmount = 11;

void handleUpdate() {
  if (handleTimer > handleUpdateTime) {
    handleTimer = 0;
  }

  int freq = tones[constrain(map(analogRead(stickXpin), 100, 1000, 0, toneAmount),0,toneAmount-1)];
  waveform1.frequency(freq);
  //float amp = fmap(analogRead(stickYpin), 100, 800, 1, 0) * fmap(freq, 30, 200, 0.9, 0.1);


  int stickYread = analogRead(stickYpin);
  float wobble = fmap(stickYread, 0 , handleMiddlePoint, 1, 0);
  float bitcrush = fmap(stickYread, handleMiddlePoint, 1023, 0, 1);

  ampli = 1 - wobble - bitcrush;//to turn off the dry signal and avoid

  mixer1.gain(1, wobble*4); //wobble

  mixer1.gain(2, bitcrush / 2); //bitcrusher
  //bitcrusher1.sampleRate(fmap(bitcrush, 0, 1, 44100, 1000));

  float dry = fmap(ampli, 0.2, 1, 0, 1) * fmap(freq, 30, 200, 0.9, 0.1);

  mixer1.gain(0, dry); //dry

  
  //waveform1.amplitude(amp);
}
