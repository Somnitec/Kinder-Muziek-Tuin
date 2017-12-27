#define wheelpin1 15//interrupt
#define wheelpin2 14//vcc
long newPosition = 0;

void setup() {
  pinMode(wheelpin2, OUTPUT);
  digitalWrite(wheelpin2, HIGH);
  pinMode(wheelpin1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(wheelpin1), count, RISING);

  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(wheelpin1));
    Serial.print("\t");
    Serial.println(newPosition);
  delay(10);
}


void count() {
  newPosition++;
}
