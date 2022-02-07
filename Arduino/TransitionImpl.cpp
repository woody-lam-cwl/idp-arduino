#include "Transition.h"

ITransition::ITransition(
    Logger *logger = nullptr,
    StateMonitor *stateMonitor = nullptr,
    IStage *nextSequentialStage = nullptr)
{
    this->logger = logger;
    this->stateMonitor = stateMonitor;
    this->nextSequentialStage = nextSequentialStage;
}

DetectBlock::DetectBlock(
    Logger *logger = nullptr,
    StateMonitor *StateMonitor = nullptr,
    IStage *nextSequentialStage = nullptr,
    MotorController *motorController = nullptr,
    ServoController *servoController = nullptr,
    LEDController *ledController = nullptr,
    InfraRedDigital *infraredDigital = nullptr,
    UltrasonicSensor *ultrasonicSensor = nullptr) : ITransition(logger, stateMonitor, nextSequentialStage)
{
    this->motorController = motorController;
    this->servoController = servoController;
    this->ledController = ledController;
    this->infraredDigital = infraredDigital;
    this->ultrasonicSensor = ultrasonicSensor;
}

bool DetectBlock::shouldStageEnd()
{
    infraredDigital->updateIsPathClear();
    return !stateMonitor->infraredDigitalState.getState();
}

void DetectBlock::exitProcedure()
{
    motorController->goStraight();
    delay(500);
    motorController->release();
    delay(500);
    ledController->stopAmber();
    servoController->grab();

    ultrasonicSensor->updateDistanceInMM();
    unsigned long distanceInMM = stateMonitor->ultrasonicState.getState();
    Color blockTypeColor = (distanceInMM < 100)? Color::Red : Color::Green;
    ledController->toggleLED(blockTypeColor, true);
}