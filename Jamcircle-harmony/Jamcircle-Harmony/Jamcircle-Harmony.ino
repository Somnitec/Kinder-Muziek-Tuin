#define sensorAmount 7

float tonesMaxAmplitude = 1.0 / sensorAmount + .03; //about one divided by the amount of tones available (.11 is the safest value)

#define debugUpdateTime 10//in ms
#define audioUpdateTime 100//in us
#define calibrationUpdateTime 5//in ms

#define sensorUpdateTime 100//in us


#define lowThreshold 5 //a value to reach before the thing gets triggered
#define maxRange 250//the maximum range of the sensors

#define numReadings 250

#define autoCalibTime 3000 //ms how long the values should be stable before autoCalib
#define autoCalibRange 10 // how stable the values should be for the timer to start
#define autoCalibSoundRange 0.01 //how much the volume should stay the same for recalibration
#define calibCycles 50 // it will average this amount of cycles when calibrating

#include <Encoder.h>
#define volumePin1 7
#define volumePin2 20
Encoder myEnc(7, 20);

long oldPosition  = -999;
//long newPosition = 0;

void setup() {
  initializingStuff();
}

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }

  sensorStuff();

  calibrationUpdate();

  audioUpdate();

  debugUpdate();
}
