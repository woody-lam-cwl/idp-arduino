#include "UnitTest.h"

void UltrasonicTest::setup(Logger *logger)
{
    this->logger = logger;
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    this->logger->setup("Ultrasonic test initialised");
}

void UltrasonicTest::loop()
{
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    if (distanceInMM < ULTRASONIC_LOWER_BOUND || distanceInMM > ULTRASONIC_UPPER_BOUND) {
        logger->log("Invalid reading from ultrasonic sensor", LoggerLevel::Error);
        return;
    }
    String message = "Ultrasonic sensor measured: " + String(distanceInMM, DEC);
    logger->log(message, LoggerLevel::Info);
    delay(500);
}