#include "Sensor.h"

void LineSensor::setup(Logger *logger)
{
    this->logger = logger;
    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    this->logger->log("Line follower initialised", LoggerLevel::Info);
}

LineReading LineSensor::getLineReading()
{
    bool leftSensorReading = digitalRead(LINE_SENSOR_LEFT_PIN);
    bool centerSensorReading = digitalRead(LINE_SENSOR_CENTER_PIN);
    bool rightSensorReading = digitalRead(LINE_SENSOR_RIGHT_PIN);
    byte reading = 0;
    reading += leftSensorReading;
    reading << 1;
    reading += centerSensorReading;
    reading << 1;
    reading += rightSensorReading;

    return (LineReading) reading;
}