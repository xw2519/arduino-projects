#include <IRremote.h>
#define IR_RECEIVE_PIN 42

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.println("Ready and scanning");
}
void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();


    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial); 
    Serial.println();
  }
}

