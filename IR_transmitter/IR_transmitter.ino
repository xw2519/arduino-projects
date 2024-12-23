#include <IRremote.h>

#define IR_RECEIVE_PIN 42

void setup() {
  Serial.begin(115200);
  IrSender.begin(IR_RECEIVE_PIN);
}

void loop() {
  IrSender.sendNECRaw(0xBA45FF00);
  Serial.println("Code sent!");
  delay(1500);
}