#include "Stages.hpp"

IStage::IStage(Logger *logger = nullptr)
{
    this->logger = logger;
}

IStage* IStage::loop()
{
    if (stageTransition == nullptr) return this;
    if (stageTransition->shouldStageEnd()) {
        stageTransition->exitProcedure();
        return this->nextStage;
    }
    return this;
}

LineTracing::LineTracing(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LineSensor *lineSensor = nullptr,
    LEDController *ledController = nullptr) : IStage(logger)
{
    this->motorController = motorController;
    this->lineSensor = lineSensor;
    this->ledController = ledController;
    logger->log("Line tracing stage instantiated", LoggerLevel::Info);
}

IStage* LineTracing::loop()
{
    LineStatus status = getLineStatus();
    bool shouldTurnLeft = false;

    ledController->flashAmber();
    switch (status) {
        case LineStatus::TooRight:
            shouldTurnLeft = true;

        case LineStatus::TooLeft:
            // logger->log("Adjusting heading", LoggerLevel::Debug);
            motorController->adjustHeading(shouldTurnLeft);
            break;

        case LineStatus::OnLine:
        case LineStatus::Unknown:
        default:
            // logger->log("Going straight", LoggerLevel::Debug);
            motorController->goStraight();
            break;
    }

    return IStage::loop();
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

Turning::Turning(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr) : IStage(logger)
{
    this->motorController = motorController;
    this->ledController = ledController;
    logger->log("Turning stage instantiated", LoggerLevel::Info);
}

IStage* Turning::loop()
{
    ledController->flashAmber();
    motorController->rotate();
    return IStage::loop();
}
