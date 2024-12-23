#include "HomeSpan.h"
#include <IRremote.h>
#define IR_SEND_PIN 42  // Define the IR sending pin

// Define a custom accessory with IR functionality
struct IRLightAccessory : Service::LightBulb {
  SpanCharacteristic *power;  // Characteristic for the "On" state

  IRLightAccessory() {
    power = new Characteristic::On();  // Initialize "On" characteristic
  }

  // Method to handle state changes from HomeKit
  boolean update() override {
    if (power->getNewVal()) {
      // Light turned ON
      Serial.println("Light turned ON. Sending IR signal...");
      IrSender.sendNECRaw(0xBA45FF00);  // Send IR signal
    } else {
      // Light turned OFF
      Serial.println("Light turned OFF.");
      IrSender.sendNECRaw(0xB847FF00);  
    }

    return true;  // Indicate success
  }
};

void setup() {
  Serial.begin(115200);

  // Built-in RGB
  pinMode(48, OUTPUT);
  digitalWrite(48, LOW); // Disable RGB

  // Initialize IR sender
  IrSender.begin(IR_SEND_PIN);

  // Initialize HomeSpan
  homeSpan.begin(Category::Lighting, "Fairy Lights");
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new IRLightAccessory();  // Add the custom light accessory
}

void loop() {
  homeSpan.poll();  // Process HomeSpan events
}
