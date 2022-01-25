#include "UnitTest.h"

void LEDTest::setup()
{
    pinMode(AMBER_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    digitalWrite(AMBER_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
}

void LEDTest::loop()
{
    digitalWrite(AMBER_LED_PIN, HIGH);
    delay(500);
    digitalWrite(AMBER_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    delay(500);
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    delay(500);
    digitalWrite(BLUE_LED_PIN, LOW);
}