#include "HomeSpan.h"
#include "arduino.h"

#define PIN_ON 20 

struct SwitchAccessory : Service::Switch {
  SpanCharacteristic *power;  // Characteristic for the "On" state

  SwitchAccessory() {
    power = new Characteristic::On();  // Initialize "On" characteristic
  }

  // Method to handle state changes from HomeKit
  boolean update() override {
    if (power->getNewVal()) {
      // Swtich turned ON
      digitalWrite(12, LOW);
      delay(100);
      digitalWrite(12, HIGH);
      Serial.println("Switch turned ON");
    } else {
      // Do nothing
      Serial.println("Switch turned OFF");
    }
    return true;  // Indicate success
  }

  void setState(bool state) {
    if (power->getVal() != state) {  // Only update if the state has changed
      power->setVal(state);  // Update HomeKit with the new state
      if (state) {
        Serial.println("HomeKit state set to ON.");
      } else {
        Serial.println("HomeKit state set to OFF.");
      }
    }
  }
};

SwitchAccessory *switchAccessory;

void setup() {
  Serial.begin(115200);

  pinMode(12, OUTPUT);
  pinMode(13, INPUT);

  digitalWrite(12, HIGH); // Switch to HIGH at beginning to ensure no shorts

  // Initialize HomeSpan
  homeSpan.begin(Category::Switches, "Chonk");
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  switchAccessory = new SwitchAccessory();  // Add the custom light accessory
}

void loop() {
  homeSpan.poll();  // Process HomeSpan events

  // Monitor the state of the input pin - Only write OFF events
  bool state = digitalRead(13);
  switchAccessory->setState(state);  // Write the state back to HomeKit
}
