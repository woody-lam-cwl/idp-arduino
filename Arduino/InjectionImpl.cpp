#include "Injection.hpp"

Injection::Injection()
{
    logger = new Logger();

    motorController = new MotorController(logger);
    servoController = new ServoController(logger);
    ledController = new LEDController(logger);

    lineSensor = new LineSensor(logger);
    ultrasonicSensor = new UltrasonicSensor(logger);
    infraRed = new InfraRed(logger);
}

IStage* Injection::getNewStage(
    IStage *currentStage,
    EnumStage stage,
    bool turnLeft = true
)
{
    delete currentStage;
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
    ITransition *currentTransition,
    EnumTransition transition,
    unsigned long suppressTime = 0
)
{
    delete currentTransition;
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
        motorController,
        ledController,
        lineSensor
    );
}

Turning* Injection::getNewTurning(bool turnLeft = true)
{
    return new Turning(
        logger,
        motorController,
        ledController,
        turnLeft
    );
}

GrabClassifyBlock* Injection::getNewGrabClassifyBlock()
{
    return new GrabClassifyBlock(
        logger,
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
        motorController,
        ledController,
        servoController
    );
}

ReverseMotion* Injection::getNewReverseMotion()
{
    return new ReverseMotion(
        logger,
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
        suppressTime
    );
}

DetectLine* Injection::getNewDetectLine(unsigned long suppressTime = 0)
{
    return new DetectLine(
        logger,
        suppressTime
    );
}

DetectCross* Injection::getNewDetectCross(unsigned long suppressTime = 0)
{
    return new DetectCross(
        logger,
        suppressTime
    );
}
