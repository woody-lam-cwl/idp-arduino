#include "UnitTest.h"

void SerialReadTest::setup(Logger *logger = nullptr)
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!Serial);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Arduino ready to receive serial message");
}

void SerialReadTest::loop()
{
    if (Serial.available() > 0) {
        digitalWrite(LED_BUILTIN, LOW);
        char data = Serial.read();
        Serial.print("Data received: ");
        Serial.println(data);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
    }
}