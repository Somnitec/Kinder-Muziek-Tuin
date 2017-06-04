

void initializingStuff() {

  for (int i = 0; i < sensorAmount; i++) {
    amplNow[i] = 0;
  }

  Serial.begin(115200);

  AudioMemory(12);//increase if the are glitches
  setFrequencies();
  turnOffAll();

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  pinMode(calibratePin, INPUT_PULLUP);

  baselineCalibration();

  volumePot.write(80);

}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  float val = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return constrain(val, min(out_min, out_max), max(out_min, out_max));
}

