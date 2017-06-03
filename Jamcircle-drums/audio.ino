int beat = 0;
#define steps 16
int rythms[3][5][16] = {
  //the value represents what are the odds for a note to play at that beat. ie ever 2nd time, or every 1 time (=every time)
  {
    //first
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
    {2, 0, 0, 0, 1, 0, 0, 2, 1, 2, 0, 0, 2, 0, 0, 2},
    { 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2},
    { 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1}
  }, {
    //second
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
    { 1, 0, 0, 0, 1, 0, 4, 0, 1, 0, 0, 0, 1, 0, 2, 0},
    { 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0}
  }, {
    //third
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    { 0, 2, 0, 0, 1, 0, 0, 2, 0, 2, 2, 0, 1, 2, 0, 2},
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 2, 2},
    { 0, 1, 4, 1, 0, 1, 4, 1, 0, 1, 4, 1, 0, 1, 4, 1}
  }
};

void audioStuff() {
  if (audioUpdateTimer > 60000 / BPM / 4) {
    audioUpdateTimer = 0;


    for (int i = 0; i < 3; i++) {
      //mixer1.gain(i, fmap(pinAverage[i] - touchThreshold, pinBaseline[i], pinBaseline[i] + touchRange, 0, 1));
    }
    /*
        mixer1.gain(0, 0.1);
        mixer1.gain(1, 0.1);
        mixer1.gain(2, 0.1);
    */
    drum1.frequency(600 + mod1value[0] * 200 + mod1value[1] * 600 + mod1value[2] * 1000 + mod1value[3] * 1400);
    drum1.length(100 + mod1value[0] * 80 + mod1value[1] * 60 + mod1value[2] * 40 + mod1value[3] * 20);

    drum2.frequency(mod2value);


    drum3.frequency(550 + 275 * mod3value[0]);
    drum3.pitchMod(0.5 + 0.02 * mod3value[1]);

    if (sequence(0))drum1.noteOn();
    if (sequence(1))drum2.noteOn();
    if (sequence(2))drum3.noteOn();

    beat++;
  }
}

boolean sequence(int drum) {
  boolean state = false;
  int value = rythms[drum][faderPos[drum]][beat % steps];
  if (value > 0) {
    if (random(value) == 0)state = true;
  }
  return state;
}

