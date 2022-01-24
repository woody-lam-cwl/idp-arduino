#include "UnitTest.h"
#include <Arduino.h>

void SerialWriteTest::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    digitalWrite(LED_BUILTIN, LOW);
    while (!Serial)
    {
        ;
    }
}

void SerialWriteTest::loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Serial writing from Arduino");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}