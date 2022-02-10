#include "Transition.hpp"

ITransition::ITransition(
    Logger *logger = nullptr,
    unsigned long suppressTime = 0
)
{
    this->logger = logger;
    this->suppressTime = suppressTime;
    this->startTime = millis();
}

Once::Once(
    Logger *logger = nullptr,
    unsigned long suppressTime = 0
) : ITransition(logger, suppressTime){};

bool Once::shouldStageEnd()
{
    logger->log("Stage executed once. Now ending.", LoggerLevel::Info);
    return true;
}

Timed::Timed(
    Logger *logger = nullptr,
    unsigned long suppresTime = 0
) : ITransition(logger, suppressTime){};

bool Timed::shouldStageEnd()
{
    unsigned long currentTime = millis();
    if (currentTime - startTime < suppressTime) return false;
    logger->log("Stage time limit reached. Now ending.", LoggerLevel::Info);
    return true;
}

DetectBlock::DetectBlock(
    Logger *logger = nullptr,
    unsigned long suppressTime = 0,
    InfraRed *infrared = nullptr
) : ITransition(logger, suppressTime)
{
    this->infrared = infrared;
    lastObstructedTime = startTime;
    currentObstruction = ObstructionState::Unobstructed;
};

bool DetectBlock::shouldStageEnd()
{
    short reading = infrared->getInfraRedReading();
    unsigned long currentTime = millis();
    if (reading > IR_ADC_THRESHOLD & currentTime - lastObstructedTime > suppressTime) {
        logger->log("Obstruction State + 1", LoggerLevel::Debug);
        currentObstruction = (ObstructionState) ((byte) currentObstruction + 1);
        lastObstructedTime = currentTime;
    }
    if (currentObstruction != ObstructionState::Block) return false;
    logger->log("Block detected. Now ending stage.", LoggerLevel::Info);
    return true;
}

DetectLine::DetectLine(
    Logger *logger = nullptr,
    unsigned long suppressTime = 0,
    LineSensor *lineSensor = nullptr
) : ITransition(logger, suppressTime)
{
    this->lineSensor = lineSensor;
}

bool DetectLine::shouldStageEnd()
{
    LineReading reading = lineSensor->getLineReading();
    unsigned long currentTime = millis();
    if (currentTime - startTime > suppressTime 
        && reading != LineReading::L111) {
            logger->log("Line detected. Now ending stage.", LoggerLevel::Info);
            return true;
        }
    return false;
}

DetectCross::DetectCross(
    Logger *logger = nullptr,
    unsigned long suppressTime = 0,
    LineSensor *lineSensor = nullptr
) : ITransition(logger, suppressTime)
{
    this->lineSensor = lineSensor;
}

bool DetectCross::shouldStageEnd()
{
    LineReading reading = lineSensor->getLineReading();
    unsigned long currentTime = millis();
    if (currentTime - startTime > suppressTime 
        && reading == LineReading::L000) {
            logger->log("Line detected. Now ending stage.", LoggerLevel::Info);
            return true;
        }
    return false;
}


// void DetectBlock::exitProcedure()
// {
//     logger->log("Detect Block Transition executing", LoggerLevel::Info);
//     motorController->goStraight();
//     delay(2000);
//     motorController->release();
//     delay(500);
//     ledController->stopAmber();

//     servoController->grab();

//     unsigned long distanceInMM = ultrasonicSensor->getDistanceInMM();
//     Color blockTypeColor = (distanceInMM < ULTRASONIC_THRESHOLD)? Color::Red : Color::Green;
//     ledController->toggleLED(blockTypeColor, true);

//     ledController->flashAmber();
//     motorController->goStraight();
//     delay(1500);
//     motorController->goStraight(false);
//     delay(500);
//     motorController->release();
//     delay(500);
//     ledController->stopAmber();
//     currentState = ObstructionState::Unobstructed;
// }

// void FinishTurn::exitProcedure()
// {
//     logger->log("Finish Turn Transition executing", LoggerLevel::Info);
//     motorController->release();
//     delay(500);
//     ledController->stopAmber();
//     startTime = 0;
// }

// void DetectCross::exitProcedure()
// {
//     motorController->goStraight();
//     delay(1500);
//     motorController->release();
//     delay(500);
//     ledController->stopAmber();
//     ledController->toggleLED(Color::Red, 0);
//     ledController->toggleLED(Color::Green, 0);
//     startTime = 0;
// }

// void Timed::exitProcedure()
// {
//     bool forward = true;
//     motorController->goStraight(forward);
//     delay(500);
//     motorController->release();
//     delay(500);
//     servoController->release();
//     forward = false;
//     motorController->goStraight(forward);
//     delay(500);
//     motorController->release();
//     delay(500);
//     startTime = 0;
// }