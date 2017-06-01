int lastVal = 0;

void speedUpdate() {
  if (speedTimer > speedUpdateTime) {
    speedTimer = 0;
    speedVal = lastVal - newPosition;
    lastVal = newPosition;

    int filter = map(abs(speedVal), 0, 200, 0, 400);
    filter1.frequency(filter);
    waveform1.amplitude(fmap(abs(speedVal), 0, 100, 0, ampli));
  }
}
//
//
