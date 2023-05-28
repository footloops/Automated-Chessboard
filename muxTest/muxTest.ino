#include "mux.h"

#define MUX1_SIG 6
#define MUX1_S0 2
#define MUX1_S1 3
#define MUX1_S2 4
#define MUX1_S3 5

mux Mux1 = mux(MUX1_SIG, MUX1_S0, MUX1_S1, MUX1_S2, MUX1_S3);
void setup() {
  Serial.begin(9600);
  pinMode(MUX1_SIG, INPUT);
  pinMode(MUX1_S0, OUTPUT);
  pinMode(MUX1_S1, OUTPUT);
  pinMode(MUX1_S2, OUTPUT);
  pinMode(MUX1_S3, OUTPUT);
}

void loop() {
  Serial.print(Mux1.readMux(15));
  Serial.println(Mux1.readMux(14));

  delay(1000);
}
