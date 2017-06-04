void readTouchpads() {
  if (touchUpdateTimer > touchUpdateTime) {
    touchUpdateTimer = 0;

    for (int i = 0; i < 3; i++) {
      pinBuffer[i][bufferPos % touchAveraging] = touchRead(touchPin[i]);

      int total = 0;
      for (int j = 0; j < touchAveraging; j++) {
        total += pinBuffer[i][j];
      }
      pinAverage[i] = total / touchAveraging;
    }
    bufferPos++;


  }
}

void setupPads() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < touchAveraging; j++) {
      pinBuffer[i][j] = 0;
    }
  }
  calibrateBaseline();
}

void calibrateBaseline() {
  for (int i = 0; i < 3; i++) {
    long total = 0;
    for (int j = 0; j < baselineReadings; j++) {
      total += touchRead(touchPin[i]);
      delay(touchUpdateTime);
    }
    pinBaseline[i] = total / baselineReadings;
    //pinBaseline[i] = total;
  }
}

