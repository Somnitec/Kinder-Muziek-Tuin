#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;          //xy=432,350
AudioOutputPWM        dac1;           //xy=647,348
AudioConnection          patchCord1(waveform1, dac1);
// GUItool: end automatically generated code



const int ledPin =  13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  AudioMemory(10);
//  dac1.analogReference(INTERNAL);
  waveform1.begin(WAVEFORM_TRIANGLE);
  waveform1.amplitude(0.001);
}

void loop() {
  Serial.print(touchRead(0));
  Serial.print('\t');
  Serial.println("ahoi");

  digitalWrite(ledPin, HIGH);
  waveform1.frequency(400);
  delay(500);

  Serial.print(touchRead(0));
  Serial.print('\t');
  Serial.println("hiho");

  digitalWrite(ledPin, LOW);
  waveform1.frequency(800);
  delay(500);
}
