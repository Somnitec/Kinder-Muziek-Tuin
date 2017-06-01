

void debugUpdate() {
  if (debugUpdateTimer > debugUpdateTime) {
    debugUpdateTimer = 0;


    Serial.print(speedVal);
    Serial.print("\t");
    /*
      Serial.print(stickYread);
      Serial.print("\t");
      Serial.print(flange);
      Serial.print("\t");
      Serial.print(bitcrush);
      
      Serial.print("\t");
      Serial.print(dry);
      Serial.print("\t");
      Serial.print(freq);
      Serial.print("\t");
      */
      
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
