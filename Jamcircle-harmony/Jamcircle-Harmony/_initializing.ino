#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

int sensor[] = {23, 22, 19, 18, 17, 16, 15};
int readings[11][numReadings];
int lowCal[11];
int highCal[11];
int average[11];
int range[11];
float ampl[11];
float totalAverage;

int readIndex = 0;

void initializingStuff() {

  Serial.begin(115200);

  AudioMemory(12);//increase if the are glitches
  setFrequencies();
  turnOffAll();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  baselineCalibration();


}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  float value =  (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  return constrain(value, out_min, out_max);
}

