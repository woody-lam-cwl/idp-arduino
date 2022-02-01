#include "Stages.h"

LineTracing::LineTracing(Logger *logger, MotorController *motorController, LineSensor *lineSensor, LEDController *ledController)
{
    this->logger = logger;
    this->motorController = motorController;
    this->lineSensor = lineSensor;
    this->ledController = ledController;
    logger->log("Line tracing stage instantiated", LoggerLevel::Info);
}

void LineTracing::loop()
{
    LineStatus status = getLineStatus();
    bool shouldTurnLeft = false;

    ledController->flashAmber();
    switch (status) {
        case LineStatus::TooRight:
            shouldTurnLeft = true;

        case LineStatus::TooLeft:
            motorController->adjustHeading(shouldTurnLeft);
            break;

        case LineStatus::OnLine:
        case LineStatus::Unknown:
        default:
            motorController->goStraight();
            break;
    }
}

LineStatus LineTracing::getLineStatus()
{
    LineReading reading = lineSensor->getLineReading();
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

