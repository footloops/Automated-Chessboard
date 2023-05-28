void setup() {
  Serial.begin(9600);
  pinMode(8, INPUT);
  //pinMode(13, INPUT_PULLUP);
}

void loop() {
  //Serial.print(digitalRead(2));
  //Serial.print(" ");
  Serial.println(digitalRead(8));
  delay(1000);
}
