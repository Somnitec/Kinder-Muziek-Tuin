elapsedMillis debugUpdateTimer;

void debugUpdate() {
  if (debugUpdateTimer > debugUpdateTime) {
    debugUpdateTimer = 0;
    if (Serial.available()) {

      int serialInput = Serial.read();
      if (serialInput == '1')baselineCalibration();
    }



    Serial.print(volumeMod);
    Serial.print('\t');
    Serial.print(digitalRead(calibratePin));
    //just raw values
    for (int i = 0; i < sensorAmount; i++) {
      Serial.print('\t');
      Serial.print(average[i]);
      Serial.print('\t');
      Serial.print(immediateAverage[i]);
      Serial.print('\t');
      Serial.print(abs(immediateAverage[i]-average[i]));
    }
    
 
      Serial.print("RMS = ");
      Serial.print(rms1.read());
      Serial.print('\t');
      Serial.print(" PEAK = ");
      Serial.print(peak1.read());
      Serial.print('\t');
      Serial.print(" Proc = ");
      Serial.print(AudioProcessorUsage());
      Serial.print(" (");
      Serial.print(AudioProcessorUsageMax());
      Serial.print("),  Mem = ");
      Serial.print(AudioMemoryUsage());
      Serial.print(" (");
      Serial.print(AudioMemoryUsageMax());
      Serial.print(")");
    
    Serial.println();
  }

}
