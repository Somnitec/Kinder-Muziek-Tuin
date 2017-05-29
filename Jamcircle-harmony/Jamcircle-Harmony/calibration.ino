elapsedMillis calibrationUpdateTimer;
elapsedMillis stableTimer;
elapsedMillis stableAudioTimer;
float previousPeak;

void calibrationUpdate() {
  /*
  if (calibrationUpdateTimer > calibrationUpdateTime) {
    calibrationUpdateTimer = 0;
    for (int i = 0; i < sensorAmount; i++) {
      if (range[i] > autoCalibRange)stableTimer = 0;//||peak1.read()<0.01
    }

    float currentPeak = rms1.read();
    if (currentPeak > autoCalibSoundRange)stableAudioTimer = 0;
    //previousPeak = currentPeak;

    if (stableTimer > autoCalibTime || stableAudioTimer > autoCalibTime) {
      Serial.println("RECALIBRATION TIME, AW YIZZ");
      baselineCalibration();
      stableTimer = 0;
      stableAudioTimer = 0;
    }

  }
  */
}

void baselineCalibration() {

  for (int i = 0; i < sensorAmount; i++) {
    int readAverage = 0;
    for (int j = 0; j < calibCycles; j++) {
      readAverage += touchRead(sensor[i]);
    }
    lowCal[i] = readAverage / calibCycles + lowThreshold;
    highCal[i] = lowCal[i] + maxRange;
  }
  Serial.println("CALIBRATION");
}


