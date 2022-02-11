#include "Stages.hpp"

IStage::IStage(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController
) : logger {logger},
    stateMonitor {stateMonitor},
    motorController {motorController},
    ledController {ledController},
    loopTimes {0},
    startTime {millis()} {}

void IStage::loop()
{
    loopTimes++;
}

IStage::~IStage()
{
    motorController.release();
    delay(500);
    ledController.stopAmber();
    logger.log("Stage loop times: " + String(loopTimes), LoggerLevel::DebugStage);
    unsigned long stageDuration = millis() - startTime;
    logger.log("Stage duration: " + String(stageDuration), LoggerLevel::DebugStage);
    logger.log("Stage destroyed", LoggerLevel::Info);
}

ForwardLineTracing::ForwardLineTracing(
    Logger &logger,
    StateMonitor &stateMonitor,
    MotorController &motorController,
    LEDController &ledController,
    LineSensor &lineSensor
) : IStage(logger, stateMonitor, motorController, ledController),
    lineSensor {lineSensor}
{
    logger.log("Starting forward line tracing stage", LoggerLevel::Info);
}

void ForwardLineTracing::loop()
{
    IStage::loop();
    LineStatus status = getLineStatus();
    bool shouldTurnLeft = false;

    ledController.flashAmber();
    switch (status) {
        case LineStatus::TooRight:
            shouldTurnLeft = true;

        case LineStatus::TooLeft:
            motorController.adjustHeading(shouldTurnLeft);
            break;

        case LineStatus::OnLine:
        case LineStatus::Unknown:
        default:
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
            logger.log("Robot on line", LoggerLevel::DebugHardware);
            status = LineStatus::OnLine;
            break;
        
        case L100:
        case L110:
            logger.log("Robot too left", LoggerLevel::DebugHardware);
            status = LineStatus::TooLeft;
            break;

        case L001:
        case L011:
            logger.log("Robot too right", LoggerLevel::DebugHardware);
            status = LineStatus::TooRight;
            break;

        case L010:
        case L111:
        default:
            logger.log("Line status unknown", LoggerLevel::DebugHardware);
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
    turnLeft {turnLeft}
{
    logger.log("Starting turning stage", LoggerLevel::Info);
}

void Turning::loop()
{
    IStage::loop();
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
    ultrasonicSensor {ultrasonicSensor}
{
    logger.log("Starting grabbing and classifying block stage", LoggerLevel::Info);
}

void GrabClassifyBlock::loop()
{
    IStage::loop();
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
    servoController {servoController}
{
    logger.log("Starting releasing block stage", LoggerLevel::Info);
}

void ReleaseBlock::loop()
{
    IStage::loop();
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
) : IStage(logger, stateMonitor, motorController, ledController)
{
    logger.log("Starting reversing stage", LoggerLevel::Info);
}

void ReverseMotion::loop()
{
    IStage::loop();
    ledController.flashAmber();
    motorController.goStraight(false);
}
