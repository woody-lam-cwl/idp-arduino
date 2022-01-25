#include "UnitTest.h"

void LineSensorTest::setup(Logger *logger)
{
    this->logger = logger;
    pinMode(LINE_SENSOR_1_PIN, INPUT);
    pinMode(LINE_SENSOR_2_PIN, INPUT);
    pinMode(LINE_SENSOR_3_PIN, INPUT);
    this->logger->setup("Line sensor test initialised");
}

void LineSensorTest::loop()
{
    sensor1Reading = digitalRead(LINE_SENSOR_1_PIN);
    sensor2Reading = digitalRead(LINE_SENSOR_2_PIN);
    sensor3Reading = digitalRead(LINE_SENSOR_3_PIN);
    String message = "Line sensor reading: " + String(sensor1Reading, DEC) + " " + String(sensor2Reading, DEC) + " " + String(sensor3Reading, DEC);
    logger->log(message, LoggerLevel::Info);
    delay(500);
}