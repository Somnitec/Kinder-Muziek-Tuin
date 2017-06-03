

void debugUpdate() {
  if (debugUpdateTimer > debugUpdateTime) {
    debugUpdateTimer = 0;

    Serial.print(analogRead(volumepot));
    Serial.print("\t");
    Serial.print(speedVal);
    Serial.print("\t");


    Serial.print(stickXread);
    Serial.print("\t");
    Serial.print(stickYread);
    Serial.print("\t");

    Serial.print(stickup);
    Serial.print("\t");
    Serial.print(stickdown);
    Serial.print("\t");

    Serial.print(amp);
    Serial.print("\t");
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
    Serial.println("");
  }
}
