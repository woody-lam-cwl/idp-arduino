#include "UnitTest.h"

void InfraRedTest::setup()
{
    Logger logger;
    this->logger = &logger;
    this->logger->setup("Infrared test initialised");
}

void InfraRedTest::loop()
{
    sensorReading = analogRead(IR_ANALOG_PIN);
    String message = "IR sensor ADC output: " + String(sensorReading, DEC);
    logger->log(message, LoggerLevel::Info);
    delay(500);
}