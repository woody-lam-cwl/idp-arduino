#include "UnitTest.h"

// NINA Component to be setup using SerialToSerialBT programme before use

void BTSerialWriteTest::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(NINA_RESETN, OUTPUT);
    digitalWrite(NINA_RESETN, LOW);
    SerialNina.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!SerialNina);
}

void BTSerialWriteTest::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    SerialNina.println("Serial writing from Arduino");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}