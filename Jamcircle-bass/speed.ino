int lastVal = 0;
boolean directio = false;

void speedUpdate() {
  if (speedTimer > speedUpdateTime) {
    speedTimer = 0;
    realSpeed = lastVal - newPosition ;
    realSpeed*=5;
    lastVal = newPosition;
    float glide = 1.5;
    speedVal = (speedVal * glide + realSpeed * 1) / (1 + glide);


    if (speedVal < 0) {
      if (directio == false) {
        /*
          waveform1.begin(WAVEFORM_SQUARE);
          waveform2.begin(WAVEFORM_SQUARE);
          waveform3.begin(WAVEFORM_SQUARE);
        */
        speedmod = 1 + speedmodifier;
      }
      directio = true;
    } else if (speedVal > 0) {
      if (directio == true) {
        /*
          waveform1.begin(WAVEFORM_SAWTOOTH);
          waveform2.begin(WAVEFORM_SAWTOOTH);
          waveform3.begin(WAVEFORM_SAWTOOTH);
        */
        speedmod = 1 - speedmodifier;
      }
      directio = false;
    }

    speedVal = constrain(speedVal, -20, 0);
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
