#include "Injection.hpp"

Injection::Injection()
    : logger {},
    stateMonitor {},
    motorController {MotorController(logger, stateMonitor)},
    servoController {ServoController(logger, stateMonitor)},
    ledController {LEDController(logger, stateMonitor)},
    lineSensor {LineSensor(logger, stateMonitor)},
    ultrasonicSensor {UltrasonicSensor(logger, stateMonitor)},
    infraRed {InfraRed{logger, stateMonitor}} {}

IStage* Injection::getNewStage(
    EnumStage stage,
    bool turnLeft = true
)
{
    IStage* newStage;
    switch (stage) {
        case EnumStage::ForwardLineTracing:
            newStage = getNewForwardLineTracing();
            break;

        case EnumStage::Turning:
            newStage = getNewTurning(turnLeft);
            break;

        case EnumStage::GrabClassifyBlock:
            newStage = getNewGrabClassifyBlock();
            break;

        case EnumStage::ReleaseBlock:
            newStage = getNewReleaseBlock();
            break;

        case EnumStage::ReverseMotion:
            newStage = getNewReverseMotion();
            break;


        default:
            newStage = nullptr;
            break;
    }

    return newStage;
}

ITransition* Injection::getNewTransition(
    EnumTransition transition,
    unsigned long suppressTime = 0
)
{
    ITransition* newTransition;
    switch (transition) {
        case EnumTransition::Once:
            newTransition = getNewOnce(suppressTime);
            break;
        
        case EnumTransition::Timed:
            newTransition = getNewTimed(suppressTime);
            break;

        case EnumTransition::DetectObstruction:
            newTransition = getNewDetectObstruction(suppressTime);
            break;

        case EnumTransition::DetectLine:
            newTransition = getNewDetectLine(suppressTime);
            break;

        case EnumTransition::DetectCross:
            newTransition = getNewDetectCross(suppressTime);
            break;

        default:
            newTransition = nullptr;
            break;
    }

    return newTransition;
}

ForwardLineTracing* Injection::getNewForwardLineTracing()
{
    return new ForwardLineTracing(
        logger,
        stateMonitor,
        motorController,
        ledController,
        lineSensor
    );
}

Turning* Injection::getNewTurning(bool turnLeft = true)
{
    return new Turning(
        logger,
        stateMonitor,
        motorController,
        ledController,
        turnLeft
    );
}

GrabClassifyBlock* Injection::getNewGrabClassifyBlock()
{
    return new GrabClassifyBlock(
        logger,
        stateMonitor,
        motorController,
        ledController,
        servoController,
        ultrasonicSensor
    );
}

ReleaseBlock* Injection::getNewReleaseBlock()
{
    return new ReleaseBlock(
        logger,
        stateMonitor,
        motorController,
        ledController,
        servoController
    );
}

ReverseMotion* Injection::getNewReverseMotion()
{
    return new ReverseMotion(
        logger,
        stateMonitor,
        motorController,
        ledController
    );
}

Once* Injection::getNewOnce(unsigned long suppressTime = 0)
{
    return new Once(
        logger,
        suppressTime
    );
}

Timed* Injection::getNewTimed(unsigned long suppressTime = 0)
{
    return new Timed(
        logger,
        suppressTime
    );
}

DetectObstruction* Injection::getNewDetectObstruction(unsigned long suppressTime = 0)
{
    return new DetectObstruction(
        logger,
        suppressTime,
        infraRed
    );
}

DetectLine* Injection::getNewDetectLine(unsigned long suppressTime = 0)
{
    return new DetectLine(
        logger,
        suppressTime,
        lineSensor
    );
}

DetectCross* Injection::getNewDetectCross(unsigned long suppressTime = 0)
{
    return new DetectCross(
        logger,
        suppressTime,
        lineSensor
    );
}
