#include "Stages.hpp"

IStage::IStage(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController
) : logger {logger},
    stateMonitor {stateMonitor},
    motorController {motorController},
    ledController {ledController} {}

IStage::~IStage()
{
    motorController.goStraight();
    delay(500);
    ledController.stopAmber();
    logger.log("Stage destroyed", LoggerLevel::Info);
}

ForwardLineTracing::ForwardLineTracing(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController,
    LineSensor &lineSensor
) : IStage(logger, stateMonitor, motorController, ledController),
    lineSensor {lineSensor} {}

void ForwardLineTracing::loop()
{
    LineStatus status = getLineStatus();
    bool shouldTurnLeft = false;

    ledController.flashAmber();
    switch (status) {
        case LineStatus::TooRight:
            shouldTurnLeft = true;

        case LineStatus::TooLeft:
            // logger.log("Adjusting heading", LoggerLevel::Debug);
            motorController.adjustHeading(shouldTurnLeft);
            break;

        case LineStatus::OnLine:
        case LineStatus::Unknown:
        default:
            // logger.log("Going straight", LoggerLevel::Debug);
            motorController.goStraight();
            break;
    }
}

LineStatus ForwardLineTracing::getLineStatus()
{
    LineReading reading = lineSensor.getLineReading();
    LineStatus status;

    switch (reading) {
        case L000:
        case L101:
            status = LineStatus::OnLine;
            break;
        
        case L100:
        case L110:
            status = LineStatus::TooLeft;
            break;

        case L001:
        case L011:
            status = LineStatus::TooRight;
            break;

        case L010:
        case L111:
        default:
            status = LineStatus::Unknown;
            break;
    }

    return status;
}

Turning::Turning(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController,
    bool turnLeft = true
) : IStage(logger, stateMonitor, motorController, ledController),
    turnLeft {turnLeft} {}

void Turning::loop()
{
    ledController.flashAmber();
    motorController.rotate(turnLeft);
}

GrabClassifyBlock::GrabClassifyBlock(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController,
    ServoController &servoController,
    UltrasonicSensor &ultrasonicSensor
) : IStage(logger, stateMonitor, motorController, ledController),
    servoController {servoController},
    ultrasonicSensor {ultrasonicSensor} {}

void GrabClassifyBlock::loop()
{
    servoController.grab();
    unsigned long distanceInMM = ultrasonicSensor.getDistanceInMM();
    BlockType blockType = (distanceInMM < ULTRASONIC_THRESHOLD)? BlockType::CoarseBlock : BlockType::FineBlock;
    stateMonitor.blockType.updateState(blockType);
    ledController.turnOnBlockLED((blockType == BlockType::CoarseBlock)? Color::Red : Color::Green);
}

ReleaseBlock::ReleaseBlock(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController,
    ServoController &servoController
) : IStage(logger, stateMonitor, motorController, ledController),
    servoController {servoController} {}

void ReleaseBlock::loop()
{
    bool goForward = true;
    ledController.flashAmber();
    motorController.goStraight(goForward);
    delay(300);
    motorController.release();
    delay(500);
    ledController.stopAmber();

    servoController.release();
    ledController.resetBlockLED();

    goForward = false;
    ledController.flashAmber();
    motorController.goStraight(goForward);
    delay(700);
    motorController.release();
    delay(500);
    ledController.stopAmber();
}

ReverseMotion::ReverseMotion(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController
) : IStage(logger, stateMonitor, motorController, ledController){};

void ReverseMotion::loop()
{
    ledController.flashAmber();
    motorController.goStraight(false);
}
