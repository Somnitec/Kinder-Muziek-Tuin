



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

  sine1.amplitude(theAmpl[0]/14);
  sine2.amplitude(theAmpl[0]/14);
  sine3.amplitude(theAmpl[1]/14);
  sine4.amplitude(theAmpl[1]/14);
  sine5.amplitude(theAmpl[2]/14);
  sine6.amplitude(theAmpl[2]/14);
  sine7.amplitude(theAmpl[3]/14);
  sine8.amplitude(theAmpl[3]/14);
  sine9.amplitude(theAmpl[4]/14);
  sine10.amplitude(theAmpl[4]/14);
  sine11.amplitude(theAmpl[5]/14);
  sine12.amplitude(theAmpl[5]/14);
  sine13.amplitude(theAmpl[6]/14);
  sine14.amplitude(theAmpl[6]/14);
}

void turnOffAll() {
}


