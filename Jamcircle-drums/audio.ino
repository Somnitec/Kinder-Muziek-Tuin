int beat = 0;
#define steps 16
int rythms[3][5][16] = {
  //the value represents what are the odds for a note to play at that beat. ie ever 2nd time, or every 1 time (=every time)
  {
    //first
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
    {2, 0, 0, 0, 1, 0, 0, 2, 1, 2, 0, 0, 2, 0, 0, 2},
    { 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 0, 2},
    { 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1, 1, 1, 3, 1}
  }, {
    //second
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    { 1, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
    { 1, 0, 0, 0, 1, 0, 4, 0, 1, 0, 0, 0, 1, 0, 2, 0},
    { 1, 0, 4, 0, 1, 0, 2, 0, 1, 0, 4, 0, 1, 0, 2, 0}
  }, {
    //third
    //1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    { 0, 2, 0, 0, 1, 0, 0, 2, 0, 2, 2, 0, 1, 2, 0, 2},
    { 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 2, 2},
    { 0, 1, 4, 1, 0, 1, 4, 1, 0, 1, 4, 1, 0, 1, 4, 1}
  }
};

void audioStuff() {
  if (audioUpdateTimer > 60000 / BPM / 4) {
    audioUpdateTimer = 0;

    float touchGain[3];
    for (int i = 0; i < 3; i++) {
      touchGain[i] = fmap(pinAverage[i] - touchThreshold, pinBaseline[i], pinBaseline[i] + touchRange, 0, 1);
    }
    
    AudioNoInterrupts();

    mixer1.gain(0, overalVolume * volumeMod1);
    mixer1.gain(1, overalVolume * volumeMod2);
    mixer1.gain(2, overalVolume * volumeMod3);
    /*
        mixer1.gain(0, 0.1);
        mixer1.gain(1, 0.1);
        mixer1.gain(2, 0.1);
    */
    drum1.frequency(map(pinAverage[0] , 500, 1000, 1000, 3000)); //default 1200
    drum1.length(20 + mod1value[3] * 418 + mod1value[2] * 204 + mod1value[1] * 102 + mod1value[0] * 20);//default 150
    drum1.secondMix(0.0);//default 0.
    drum1.pitchMod(0.0);//default 0.

    drum2.frequency(map(pinAverage[1], 600, 1000, 50, 100)); //default 60
    drum2.length(mod2value);//default 1500
    drum2.secondMix(0.0);//default 0.0
    drum2.pitchMod(0.55);//default 0.55


    drum3.frequency(map(pinAverage[2], 900, 1000, 400, 700)); //default 550
    drum3.length(50 + 200 * mod3value[0]); //default 400
    drum3.secondMix(1.0);//default 1.0
    drum3.pitchMod(0.5 + 0.1 * mod3value[1]);//default 0.5

    if (sequence(0)) {
      drum1.noteOn();
    }

    if (sequence(1)) {
      drum2.noteOn();
    }

    if (sequence(2)) {
      drum3.noteOn();
    }

    AudioInterrupts();

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

