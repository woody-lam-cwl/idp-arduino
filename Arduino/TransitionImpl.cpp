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
    InfraRed *infrared = nullptr,
    UltrasonicSensor *ultrasonicSensor = nullptr) : ITransition(logger)
{
    this->motorController = motorController;
    this->servoController = servoController;
    this->ledController = ledController;
    this->infrared = infrared;
    this->ultrasonicSensor = ultrasonicSensor;
    logger->log("Detect Block Transition instantiated", LoggerLevel::Info);
}

bool DetectBlock::shouldStageEnd()
{
    short reading = infrared->getInfraRedReading();
    unsigned long ultrasound = ultrasonicSensor->getDistanceInMM();

    unsigned long currentTime = millis();
    if (reading > IR_ADC_THRESHOLD & currentTime - lastObstructedTime > REBOUNCE_TIME_MS) {
        logger->log("Obstruction State + 1", LoggerLevel::Debug);
        currentState = (ObstructionState) ((byte) currentState + 1);
        lastObstructedTime = currentTime;
    }
    
    return currentState == ObstructionState::Block;
}

void DetectBlock::exitProcedure()
{
    logger->log("Detect Block Transition executing", LoggerLevel::Info);
    motorController->goStraight();
    delay(2000);
    motorController->release();
    delay(500);
    ledController->stopAmber();

    servoController->grab();

    unsigned long distanceInMM = ultrasonicSensor->getDistanceInMM();
    Color blockTypeColor = (distanceInMM < 100)? Color::Red : Color::Green;
    ledController->toggleLED(blockTypeColor, true);

    motorController->goStraight();
    delay(2000);
    motorController->goStraight(false);
    delay(1000);
    motorController->release();
    delay(500);
    ledController->stopAmber();
    currentState = ObstructionState::Unobstructed;
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
    if (millis() - startTime < TURN_SUPPRESS_LINE_TIME_MS) {
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