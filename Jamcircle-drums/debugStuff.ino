

void debugUpdate() {
  if (debugUpdateTimer > debugUpdateTime) {
    debugUpdateTimer = 0;


    Serial.print(analogRead(volumepot));
    Serial.print('\t');
    Serial.print(recalibrateButton.read());
    Serial.print('\t');

    int maxval = 1023;
    for (int i = 0; i < 3; i++) {
      Serial.print(pinAverage[i]);
      Serial.print('\t');
      Serial.print(pinBaseline[i]);
      Serial.print('\t');
      Serial.print(constrain(map(pinAverage[i] - touchThreshold, pinBaseline[i], pinBaseline[i] + touchRange, 0, maxval), 0, maxval));
      Serial.print('\t');
    }
    for (int i = 0; i < 3; i++) {
      Serial.print(analogRead(faderPin[i]));
      Serial.print('\t');
      Serial.print(faderPos[i]);
      Serial.print('\t');
    }
    Serial.print(digitalRead(mod1_0) );
    Serial.print('\t');
    Serial.print(digitalRead(mod1_1) );
    Serial.print('\t');
    Serial.print(digitalRead(mod1_2) );
    Serial.print('\t');
    Serial.print(digitalRead(mod1_3 ));
    Serial.print('\t');
    Serial.print(analogRead(mod2 ));
    Serial.print('\t');
    Serial.print(digitalRead(mod3_0) );
    Serial.print('\t');
    Serial.print(digitalRead(mod3_1) );

    Serial.print("\t");
    Serial.print("RMS = ");
    //Serial.print(rms1.read());
    Serial.print('\t');
    Serial.print(" PEAK = ");
    //Serial.print(peak1.read());
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
    Serial.println("");
  }
}
