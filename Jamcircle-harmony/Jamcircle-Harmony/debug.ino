elapsedMillis debugUpdateTimer;

void debugUpdate() {
  if (debugUpdateTimer > debugUpdateTime) {
    debugUpdateTimer = 0;
    if (Serial.available()) {

      int serialInput = Serial.read();
      if (serialInput == '1')baselineCalibration();
    }


    boolean simple = true;
    if (simple == true) {
      //just raw values
      for (int i = 0; i < sensorAmount; i++) {
        Serial.print('\t');
        Serial.print(average[i]);
      }
      Serial.println();
    }
    else {

      Serial.println();
      Serial.println();


      Serial.print("totalAverage: ");
      Serial.print(totalAverage);
      Serial.print('\t');

      int avgRange = 0;
      for (int i = 0; i < sensorAmount; i++) {
        avgRange += range[i];
      }
      avgRange /= sensorAmount;
      Serial.print("avgRange: ");
      Serial.print(avgRange);
      Serial.print('\t');
      Serial.print("stableTimer: ");
      Serial.print(stableTimer);

      Serial.print('\t');
      Serial.print("stableAudioTimer: ");
      Serial.print(stableAudioTimer);

      Serial.print('\t');
      Serial.print("tonesMaxAmplitude: ");
      Serial.print(tonesMaxAmplitude);
      Serial.println();

      //raw values
      Serial.print("RAW values: ");
      for (int i = 0; i < sensorAmount; i++) {
        Serial.print('\t');
        Serial.print(readings[i][readIndex]);

      }

      Serial.println();
      //oscillator amplitudes
      Serial.print("amplitude: ");
      for (int i = 0; i < sensorAmount; i++) {

        Serial.print('\t');
        Serial.print(ampl[i]);
      }
      Serial.println();
      //range of sensor array
      Serial.print("sensorRange ");
      for (int i = 0; i < sensorAmount; i++) {
        Serial.print('\t');
        Serial.print(range[i]);
      }
      Serial.println();
      Serial.print("RMS = ");
      //Serial.print(rms1.read());
      Serial.print('\t');
      Serial.print(" PEAK = ");
      //Serial.print(peak1.read());
      Serial.print('\t');
      Serial.print(" Proc = ");
      //Serial.print(AudioProcessorUsage());
      Serial.print(" (");
      //Serial.print(AudioProcessorUsageMax());
      Serial.print("),  Mem = ");
      //Serial.print(AudioMemoryUsage());
      Serial.print(" (");
      //Serial.print(AudioMemoryUsageMax());
      Serial.print(")");

    }
  }
}
