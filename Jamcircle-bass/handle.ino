int tones[] = {NOTE_C1, NOTE_D1, NOTE_E1, NOTE_G1, NOTE_A1, NOTE_C2, NOTE_D2, NOTE_E2, NOTE_G2, NOTE_A2, NOTE_C3};
int toneAmount = 11;

void handleUpdate() {
  if (handleTimer > handleUpdateTime) {
    handleTimer = 0;
  }

  int volumeValue = analogRead(volumepot);
  if (volumeValue - volumeThreshold > lastVolume || volumeValue + volumeThreshold < lastVolume) {
    lastVolume = volumeValue;
    overalVolume = fmap(volumeValue, 0, 4096, 0, 1);
    Serial.println("VOLUMECHANGED");
  }



  stickYread = analogRead(stickYpin);
  stickXread = analogRead(stickXpin);

  int freq = tones[constrain(map(stickXread, 100, 4095, 0, toneAmount), 0, toneAmount - 1)];
  waveform1.frequency(speedmod * freq);
  waveform2.frequency(speedmod * freq * 1.62);
  waveform3.frequency(speedmod * freq * 1.1);
  //float amp = fmap(analogRead(stickYpin), 100, 800, 1, 0) * fmap(freq, 30, 200, 0.9, 0.1);



  float stickup = fmap(stickYread, 0 , handleMiddlePoint, 1, 0);
  float stickdown = fmap(stickYread, handleMiddlePoint, 4095, 0, 1);

  float compress =  fmap(freq, 30, 200, 0.9, 0.1);

  mixer1.gain(1,overalVolume* stickup * compress); //fifth
  mixer1.gain(2,overalVolume* stickdown * compress); //detune
  mixer1.gain(0,overalVolume* compress); //dry


  //waveform1.amplitude(amp);
}
