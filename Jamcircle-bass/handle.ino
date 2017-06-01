void handleUpdate() {
  if (handleTimer > handleUpdateTime) {
    handleTimer = 0;
  }

  int freq = map(analogRead(stickXpin), 100, 1000, 20, 100);
  //float amp = fmap(analogRead(stickYpin), 100, 800, 1, 0) * fmap(freq, 30, 200, 0.9, 0.1);


  int stickYread = analogRead(stickYpin);
  float flange = fmap(stickYread, 0 , handleMiddlePoint, 1, 0);
  float bitcrush = fmap(stickYread, handleMiddlePoint, 1023, 0, 1);

  ampli = 1 - flange - bitcrush;//to turn off the dry signal and avoid

  mixer1.gain(1, flange); //flanger

  mixer1.gain(2, bitcrush / 2); //bitcrusher
  bitcrusher1.sampleRate(fmap(bitcrush, 0, 1, 44100, 1000));

  float dry = fmap(ampli, 0.2, 1, 0, 1) * fmap(freq, 30, 200, 0.9, 0.1);

  mixer1.gain(0, dry); //dry

  waveform1.frequency(freq);
  //waveform1.amplitude(amp);
}
