int lastVal = 0;
boolean directio = false;

void speedUpdate() {
  if (speedTimer > speedUpdateTime) {
    speedTimer = 0;
    speedVal = lastVal - newPosition;
    lastVal = newPosition;

    if (speedVal < 0) {
      if (directio == false)waveform1.begin(WAVEFORM_SQUARE);
      directio = true;
    } else if (speedVal > 0) {
      if (directio == true)waveform1.begin(WAVEFORM_SAWTOOTH);
      directio = false;
    }


    int filter = map(abs(speedVal), 0, 200, 100, 1000);
    filter1.frequency(filter);
    amp = fmap(abs(speedVal), 0, 200, 0.001, ampli);
    waveform1.amplitude(amp);
    sine_fm1.amplitude(amp*2);

  }
}
//
//
