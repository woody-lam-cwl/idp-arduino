#include <Arduino.h>
#include <Servo.h>

Servo servo;


void setup() {
  servo.attach(9);
}

void loop() {
  servo.write(20);
}
