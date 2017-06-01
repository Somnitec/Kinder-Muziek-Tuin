//teensy 3.0 with pwm output

#define stickXpin A5
#define stickYpin A4
#define wheelpin1 14
#define wheelpin2 15

#include <Audio.h>
#include <Encoder.h>
// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=521,377
AudioOutputPWM           pwm1;           //xy=726,390
AudioConnection          patchCord1(waveform1, pwm1);
// GUItool: end automatically generated code
Encoder myEnc(wheelpin1, wheelpin2);
long oldPosition  = -999;



void setup() {
  Serial.begin(9600);
  AudioMemory(2);
  waveform1.begin(WAVEFORM_SQUARE);
  waveform1.frequency(20);
  waveform1.amplitude(0.01);
  pinMode(stickXpin, INPUT);
  pinMode(stickYpin, INPUT);
}

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
  //Serial.printf(analogRead(stickXpin),analogRead(stickYpin));

  Serial.print(analogRead(stickXpin));
  Serial.print("\t");
  Serial.println(analogRead(stickYpin));
  delay(10);
}
