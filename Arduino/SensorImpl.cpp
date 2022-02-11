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

void LineSensor::updateLineReading()
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
    stateMonitor.lineReadingState.updateState((LineReading) reading);
    String message = "Line sensor reading: " + String(reading, BIN);
    logger.log(message, LoggerLevel::DebugHardware);
}

LineReading LineSensor::getLineReading()
{
    updateLineReading();
    return stateMonitor.lineReadingState.getState();
}

UltrasonicSensor::UltrasonicSensor(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor}
{
    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    logger.log("Ultrasonic sensor initialised", LoggerLevel::Info);
}

void UltrasonicSensor::updateDistanceInMM()
{
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    unsigned long pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    unsigned long distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    stateMonitor.ultrasonicDistance.updateState(distanceInMM);
    String message = "Ultrasonic sensor measured: " + String(distanceInMM);
    logger.log(message, LoggerLevel::DebugHardware);
}

unsigned long UltrasonicSensor::getDistanceInMM()
{
    updateDistanceInMM();
    return stateMonitor.ultrasonicDistance.getState();
}

InfraRed::InfraRed(
    Logger &logger,
    StateMonitor &stateMonitor
) : logger {logger},
    stateMonitor {stateMonitor}
{
    logger.log("Infrared sensor initialised", Info);
}

void InfraRed::updateInfraRedReading()
{
    short reading = analogRead(IR_ANALOG_PIN);
    stateMonitor.infraRedReading.updateState(reading);
    String message = "Infrared sensor reading: " + String(reading);
    logger.log(message, LoggerLevel::DebugHardware);
}

short InfraRed::getInfraRedReading()
{
    updateInfraRedReading();
    return stateMonitor.infraRedReading.getState();
}
