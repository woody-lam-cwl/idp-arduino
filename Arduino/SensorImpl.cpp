#include "Sensor.h"

LineSensor::LineSensor(Logger *logger = nullptr)
{
    this->logger = logger;

    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    this->logger->log("Line sensor initialised", LoggerLevel::Info);
}

LineReading LineSensor::getLineReading()
{
    bool leftSensorReading = digitalRead(LINE_SENSOR_LEFT_PIN);
    bool centerSensorReading = digitalRead(LINE_SENSOR_CENTER_PIN);
    bool rightSensorReading = digitalRead(LINE_SENSOR_RIGHT_PIN);
    byte reading = 0;
    reading += leftSensorReading;
    reading *= 2;
    reading += centerSensorReading;
    reading *= 2;
    reading += rightSensorReading;

    String message = "Line sensor reading: " + String(reading);
    logger->log(message, LoggerLevel::Info);
    return (LineReading) reading;
}

UltrasonicSensor::UltrasonicSensor(Logger *logger = nullptr)
{
    this->logger = logger;

    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    this->logger->log("Ultrasonic sensor initialised", Info);
}

unsigned long UltrasonicSensor::getDistanceInMM()
{
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    unsigned long pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    unsigned long distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    
    String message = "Ultrasonic sensor measured: " + String(distanceInMM, DEC);
    logger->log(message, LoggerLevel::Info);
    return distanceInMM;
}

InfraRedDigital::InfraRedDigital(Logger *logger = nullptr)
{
    this->logger = logger;

    pinMode(IR_DIGITAL_PIN, INPUT);
    this->logger->log("Infrared digital initialised", LoggerLevel::Info);
}

bool InfraRedDigital::getIsPathClear()
{
    return digitalRead(IR_DIGITAL_PIN);
}

InfraRedAnalogue::InfraRedAnalogue(Logger *logger = nullptr)
{
    this->logger = logger;
    this->logger->log("Infrared analogue initialised", Info);
}

short InfraRedAnalogue::getInfraRedReading()
{
    return analogRead(IR_ANALOG_PIN);
}
