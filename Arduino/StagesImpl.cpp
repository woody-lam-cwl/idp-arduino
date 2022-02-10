#include "Stages.hpp"

IStage::IStage(
    Logger &logger,
    MotorController &motorController,
    LEDController &ledController
) : logger {logger},
    motorController {motorController},
    ledController {ledController} {}

IStage::~IStage()
{
    motorController.goStraight();
    delay(500);
    ledController.stopAmber();
}

ForwardLineTracing::ForwardLineTracing(
    Logger &logger,
    MotorController &motorController,
    LEDController &ledController,
    LineSensor &lineSensor
) : IStage(logger, motorController, ledController),
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
    MotorController &motorController,
    LEDController &ledController,
    bool turnLeft = true
) : IStage(logger, motorController, ledController),
    turnLeft {turnLeft} {}

void Turning::loop()
{
    ledController.flashAmber();
    motorController.rotate(turnLeft);
}

GrabClassifyBlock::GrabClassifyBlock(
    Logger &logger,
    MotorController &motorController,
    LEDController &ledController,
    ServoController &servoController,
    UltrasonicSensor &ultrasonicSensor
) : IStage(logger, motorController, ledController),
    servoController {servoController},
    ultrasonicSensor {ultrasonicSensor} {}

void GrabClassifyBlock::loop()
{
    servoController.grab();
    unsigned long distanceInMM = ultrasonicSensor.getDistanceInMM();
    Color blockTypeColor = (distanceInMM < ULTRASONIC_THRESHOLD)? Color::Red : Color::Green;
    ledController.turnOnBlockLED(blockTypeColor);
}

ReleaseBlock::ReleaseBlock(
    Logger &logger,
    MotorController &motorController,
    LEDController &ledController,
    ServoController &servoController
) : IStage(logger, motorController, ledController),
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
    delay(300);
    motorController.release();
    delay(500);
    ledController.stopAmber();
}

ReverseMotion::ReverseMotion(
    Logger &logger,
    MotorController &motorController,
    LEDController &ledController
) : IStage(logger, motorController, ledController){};

void ReverseMotion::loop()
{
    ledController.flashAmber();
    motorController.goStraight(false);
}
