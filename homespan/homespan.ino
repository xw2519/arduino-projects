#include "HomeSpan.h" 

void setup() {
  Serial.begin(115200);

  // HomePod setup
  homeSpan.begin(Category::Lighting,"Fairy lights");
  new SpanAccessory(); 
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Service::LightBulb();
  new Characteristic::On();
}

void loop() {
  homeSpan.poll(); 
}
