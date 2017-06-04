



int toneSet[7][2] = {
  {NOTE_C4, NOTE_E6},
  {NOTE_A4, NOTE_C5},
  {NOTE_B4, NOTE_D6},
  {NOTE_E5, NOTE_G4},
  {NOTE_D5, NOTE_F4},
  {NOTE_F5, NOTE_A5},
  {NOTE_B5, NOTE_G5 }
};


elapsedMillis audioUpdateTimer;
void audioUpdate() {
  if (audioUpdateTimer > audioUpdateTime) {
    audioUpdateTimer = 0;
    setAmplitudes();
  }
}

void setFrequencies() {
  sine1.frequency(toneSet[0][0]);
  sine2.frequency(toneSet[0][1]);
  sine3.frequency(toneSet[1][0]);
  sine4.frequency(toneSet[1][1]);
  sine5.frequency(toneSet[2][0]);
  sine6.frequency(toneSet[2][1]);
  sine7.frequency(toneSet[3][0]);
  sine8.frequency(toneSet[3][1]);
  sine9.frequency(toneSet[4][0]);
  sine10.frequency(toneSet[4][1]);
  sine11.frequency(toneSet[5][0]);
  sine12.frequency(toneSet[5][1]);
  sine13.frequency(toneSet[6][0]);
  sine14.frequency(toneSet[6][1]);

}

void setAmplitudes() {
  AudioNoInterrupts();
  for (int i = 0; i < sensorAmount; i++) {
    //amplNow[i] = (amplNow[i] * glide + theAmpl[i] * 2) / (1 + glide);
    amplNow[i]=ampl[i];
  }

  sine1.amplitude(amplNow[0] / 7.);
  sine2.amplitude(amplNow[0] / 7.);
  sine3.amplitude(amplNow[1] / 7.);
  sine4.amplitude(amplNow[1] / 7.);
  sine5.amplitude(amplNow[2] / 7.);
  sine6.amplitude(amplNow[2] / 7.);
  sine7.amplitude(amplNow[3] / 7.);
  sine8.amplitude(amplNow[3] / 7);
  sine9.amplitude(amplNow[4] / 7.);
  sine10.amplitude(amplNow[4] / 7.);
  sine11.amplitude(amplNow[5] / 7.);
  sine12.amplitude(amplNow[5] / 7.);
  sine13.amplitude(amplNow[6] / 7.);
  sine14.amplitude(amplNow[6] / 7.);
  AudioInterrupts();
}

void turnOffAll() {
}


