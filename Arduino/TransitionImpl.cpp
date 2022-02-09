#include "Transition.h"

ITransition::ITransition(Logger *logger = nullptr)
{
    this->logger = logger;
}

DetectBlock::DetectBlock(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    ServoController *servoController = nullptr,
    LEDController *ledController = nullptr,
    InfraRedAnalogue *infraredAnalogue = nullptr,
    UltrasonicSensor *ultrasonicSensor = nullptr) : ITransition(logger)
{
    this->motorController = motorController;
    this->servoController = servoController;
    this->ledController = ledController;
    this->infraredAnalogue = infraredAnalogue;
    this->ultrasonicSensor = ultrasonicSensor;
    logger->log("Detect Block Transition instantiated", LoggerLevel::Info);
}

bool DetectBlock::shouldStageEnd()
{
    short reading = infraredAnalogue->getInfraRedReading();
    unsigned long ultrasound = ultrasonicSensor->getDistanceInMM();
    logger->log(String(reading), LoggerLevel::Info);
    return reading > 400;
}

void DetectBlock::exitProcedure()
{
    logger->log("Detect Block Transition executing", LoggerLevel::Info);
    motorController->release();
    delay(500);
    ledController->stopAmber();
    servoController->grab();

    unsigned long distanceInMM = ultrasonicSensor->getDistanceInMM();
    Color blockTypeColor = (distanceInMM < 100)? Color::Red : Color::Green;
    ledController->toggleLED(blockTypeColor, true);
}

FinishTurn::FinishTurn(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr,
    LineSensor *lineSensor = nullptr
) : ITransition(logger)
{
    this->motorController = motorController;
    this->ledController = ledController;
    this->lineSensor = lineSensor;
    logger->log("Finish Turn Transition instantiated", LoggerLevel::Info);
}

bool FinishTurn::shouldStageEnd()
{
    logger->log("End Turn Check", LoggerLevel::Debug);
    if (startTime == 0) {
        startTime = millis();
        logger->log("Set Start Time", LoggerLevel::Debug);
    }
    if (millis() - startTime < 1000) {
        logger->log("Too soon", LoggerLevel::Debug);
        return false;
    }
    LineReading reading = lineSensor->getLineReading();
    return reading != L111;
}

void FinishTurn::exitProcedure()
{
    logger->log("Finish Turn Transition executing", LoggerLevel::Info);
    motorController->release();
    delay(500);
    ledController->stopAmber();
    startTime = 0;
}