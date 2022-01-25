#include "UnitTest.h"

void ArduinoTest::setup()
{
    ledState = false;
    lastChangedTime = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void ArduinoTest::loop()
{
    unsigned long currentTime = millis();
    if (currentTime - lastChangedTime > 500)
    {
        lastChangedTime = currentTime;
        digitalWrite(LED_BUILTIN, (ledState ? HIGH : LOW));
        ledState = !ledState;
    }
}