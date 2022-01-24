#include "../Constants.h"
#include "../Modules/Motor.h"
#include "../UnitTest/UnitTest.h"

TestCollection tests;

void setup() {
    tests.arduinoTest.setup();
}

void loop() {
    tests.arduinoTest.loop();
}