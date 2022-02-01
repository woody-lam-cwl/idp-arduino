#include <Arduino.h>

void setup() {
     pinMode(NINA_RESETN, OUTPUT);         
     digitalWrite(NINA_RESETN, LOW);
     
     Serial.begin(115200);
     SerialNina.begin(115200);
}

void loop() {
  if (Serial.available()) {
  SerialNina.write(Serial.read());}
  if (SerialNina.available()) {
  Serial.write(SerialNina.read());}
}
