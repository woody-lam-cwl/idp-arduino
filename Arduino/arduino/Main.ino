#include "../UnitTest/UnitTest.h"

TestCollection tests;

void setup() {
    tests.arduinoTest.setup();
}

void loop() {
    tests.arduinoTest.loop();
}