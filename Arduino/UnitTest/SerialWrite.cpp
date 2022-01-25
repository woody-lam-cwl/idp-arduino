#include "UnitTest.h"

void SerialWriteTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!Serial);
}

void SerialWriteTest::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Serial writing from Arduino");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}