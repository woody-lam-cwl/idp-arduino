#include "Sensor.hpp"

LineSensor::LineSensor(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor}
{

    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    logger.log("Line sensor initialised", LoggerLevel::Info);
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
    
    logger.log(message, LoggerLevel::Debug);
    stateMonitor.lineReading = (LineReading) reading;
    return (LineReading) reading;
}

UltrasonicSensor::UltrasonicSensor(Logger &logger) : logger {logger}
{
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    logger.log("Ultrasonic sensor initialised", Info);
}

unsigned long UltrasonicSensor::getDistanceInMM()
{
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    unsigned long pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    unsigned long distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    
    String message = "Ultrasonic sensor measured: " + String(distanceInMM);
    logger.log(message, LoggerLevel::Info);
    return distanceInMM;
}

InfraRed::InfraRed(Logger &logger) : logger {logger}
{
    logger.log("Infrared sensor initialised", Info);
}

short InfraRed::getInfraRedReading()
{
    short reading = analogRead(IR_ANALOG_PIN);
    String message = "Infrared sensor reading: " + String(reading);
    // logger.log(message, LoggerLevel::Debug);
    return reading;
}