int lastVal = 0;
boolean directio = false;

void speedUpdate() {
  if (speedTimer > speedUpdateTime) {
    speedTimer = 0;
    speedVal = lastVal - newPosition;
    lastVal = newPosition;

    if (speedVal < 0) {
      if (directio == false) {
        /*
          waveform1.begin(WAVEFORM_SQUARE);
          waveform2.begin(WAVEFORM_SQUARE);
          waveform3.begin(WAVEFORM_SQUARE);
        */
        speedmod = 1+speedmodifier;
      }
      directio = true;
    } else if (speedVal > 0) {
      if (directio == true) {
        /*
          waveform1.begin(WAVEFORM_SAWTOOTH);
          waveform2.begin(WAVEFORM_SAWTOOTH);
          waveform3.begin(WAVEFORM_SAWTOOTH);
        */
        speedmod = 1-speedmodifier;
      }
      directio = false;
    }


    int filter = fmap(abs(speedVal), 0, 200, 100, 6000);
    filter1.frequency(filter);
    amp = fmap(abs(speedVal), 0, 200, 0.00, ampli);
    waveform1.amplitude(amp);
    waveform2.amplitude(amp);
    waveform3.amplitude(amp);

  }
}
//
//
