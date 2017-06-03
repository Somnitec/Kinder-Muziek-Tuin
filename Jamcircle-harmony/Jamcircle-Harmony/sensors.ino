elapsedMicros sensorUpdateTimer;
void sensorStuff() {
  if (sensorUpdateTimer > sensorUpdateTime) {
    sensorUpdateTimer = 0;

    int total[sensorAmount];

    totalAverage = 0;
    for (int i = 0; i < sensorAmount; i++) {
      readings[i][readIndex] = touchRead(sensor[i]);

      total[i] = 0;
      //maxi[i] = 0;
      //mini[i] = 32000;//it's unlikely to get higher than this in either 16b or 32b

      for (int j = 0; j < numReadings; j++) {
        total[i] +=  readings[i][j];
        //if (readings[i][readIndex] < mini[i])mini[i] = readings[i][j];
        //if (readings[i][readIndex] > maxi[i])maxi[i] = readings[i][j];
      }
      average[i] = total[i] / numReadings;

      //calculating the shorter average
      total[i] = 0;
      for (int j = 0; j < numReadingsImmediate; j++) {
        total[i] +=  readings[i][(j+readIndex)%numReadings];
        //if (readings[i][readIndex] < mini[i])mini[i] = readings[i][j];
        //if (readings[i][readIndex] > maxi[i])maxi[i] = readings[i][j];
      }
      immediateAverage[i] = total[i] / numReadingsImmediate;
      //range[i] = maxi[i] - mini[i];
      ampl[i] = fmap(average[i], lowCal[i], highCal[i], 0, 1); //mapping the value to a 0 - 1 range

      totalAverage += ampl[i];

      theAmpl[i] = fmap(abs(immediateAverage[i]-average[i]),sensorThreshold,sensorMax+sensorThreshold,0,1);
    }
    totalAverage /= sensorAmount;
    readIndex = readIndex + 1;
    if (readIndex >= numReadings) {
      readIndex = 0;
    }
  }
}

