#include "UnitTest.h"

// NINA Component to be setup using SerialToSerialBT programme before use

void BTSerialReadTest::setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(NINA_RESETN, OUTPUT);
    digitalWrite(NINA_RESETN, LOW);
    SerialNina.begin(BAUD_RATE);
    digitalWrite(LED_BUILTIN, LOW);
    while (!SerialNina);
    digitalWrite(LED_BUILTIN, HIGH);
    SerialNina.println("Arduino ready to receive serial message");
}

void BTSerialReadTest::loop()
{
    if (SerialNina.available() > 0) {
        digitalWrite(LED_BUILTIN, LOW);
        char data = SerialNina.read();
        SerialNina.print("Data received: ");
        SerialNina.println(data);
        delay(500);
        digitalWrite(LED_BUILTIN, HIGH);
    }
}