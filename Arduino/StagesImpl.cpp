#include "Stages.h"

LineTracing::LineTracing(MotorController *motorController, LineSensor *lineSensor)
{
    this->motorController = motorController;
    this->lineSensor = lineSensor;
}

void LineTracing::loop()
{
    LineStatus status = getLineStatus();
    bool shouldTurnLeft = false;

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

