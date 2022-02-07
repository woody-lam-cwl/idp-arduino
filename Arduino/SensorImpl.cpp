#include "Sensor.h"

LineSensor::LineSensor(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    pinMode(LINE_SENSOR_LEFT_PIN, INPUT);
    pinMode(LINE_SENSOR_CENTER_PIN, INPUT);
    pinMode(LINE_SENSOR_RIGHT_PIN, INPUT);
    this->logger->log("Line sensor initialised", LoggerLevel::Info);
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

    String message = "Line sensor reading: " + String(reading, BIN);
    logger->log(message, LoggerLevel::Info);
    stateMonitor->lineSensorState.updateState((LineReading) reading);
}

UltrasonicSensor::UltrasonicSensor(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    pinMode(ULTRASONIC_TRIGGER_PIN, OUTPUT);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    pinMode(ULTRASONIC_ECHO_PIN, INPUT);
    this->logger->log("Ultrasonic sensor initialised", Info);
}

void UltrasonicSensor::updateDistanceInMM()
{
    digitalWrite(ULTRASONIC_TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(ULTRASONIC_TRIGGER_PIN, LOW);
    unsigned long pulseDuration = pulseIn(ULTRASONIC_ECHO_PIN, HIGH, ULTRASONIC_TIMEOUT_US);
    unsigned long distanceInMM = pulseDuration / ULTRASONIC_MM_CONVERSION;
    if (distanceInMM < ULTRASONIC_LOWER_BOUND || distanceInMM > ULTRASONIC_UPPER_BOUND) {
        logger->log("Invalid reading from ultrasonic sensor", LoggerLevel::Error);
        return;
    }
    String message = "Ultrasonic sensor measured: " + String(distanceInMM, DEC);
    logger->log(message, LoggerLevel::Info);
    stateMonitor->ultrasonicState.updateState(distanceInMM);
}

InfraRedDigital::InfraRedDigital(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    pinMode(IR_DIGITAL_PIN, INPUT);
    this->logger->log("Infrared digital initialised", LoggerLevel::Info);
}

void InfraRedDigital::updateIsPathClear()
{
    this->stateMonitor->infraredDigitalState.updateState(digitalRead(IR_DIGITAL_PIN));
}

InfraRedAnalogue::InfraRedAnalogue(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;

    this->logger->log("Infrared analogue initialised", Info);
}

void InfraRedAnalogue::updateInfraRedReading()
{
    this->stateMonitor->infraredAnalogueState.updateState(analogRead(IR_ANALOG_PIN));
}