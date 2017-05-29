#define sensorAmount 7
int sensor[] = {23, 22, 19, 18, 17, 16, 15};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < sensorAmount; i++) {
    Serial.print(touchRead(sensor[i]));
    Serial.print('\t');
  }
  Serial.println();
  delay(100);
}
