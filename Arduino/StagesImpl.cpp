#include "Stages.hpp"

IStage::IStage(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr
)
{
    this->logger = logger;
    this->motorController = motorController;
    this->ledController = ledController;
}

IStage::~IStage()
{
    motorController->release();
    delay(500);
    ledController->stopAmber();
}

ForwardLineTracing::ForwardLineTracing(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr,
    LineSensor *lineSensor = nullptr
) : IStage(logger, motorController, ledController)
{
    this->motorController = motorController;
    this->lineSensor = lineSensor;
}

void ForwardLineTracing::loop()
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
}

LineStatus ForwardLineTracing::getLineStatus()
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
    LEDController *ledController = nullptr,
    bool turnLeft = true) : IStage(logger, motorController, ledController)
{
    this->turnLeft= turnLeft;
};

void Turning::loop()
{
    ledController->flashAmber();
    motorController->rotate(turnLeft);
}

GrabClassifyBlock::GrabClassifyBlock(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr,
    ServoController *servoController = nullptr,
    UltrasonicSensor *ultrasonicSensor = nullptr
) : IStage(logger, motorController, ledController)
{
    this->servoController = servoController;
    this->ultrasonicSensor = ultrasonicSensor;
}

void GrabClassifyBlock::loop()
{
    servoController->grab();
    unsigned long distanceInMM = ultrasonicSensor->getDistanceInMM();
    Color blockTypeColor = (distanceInMM < ULTRASONIC_THRESHOLD)? Color::Red : Color::Green;
    ledController->turnOnBlockLED(blockTypeColor);
}

ReleaseBlock::ReleaseBlock(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr,
    ServoController *servoController = nullptr
) : IStage(logger, motorController, ledController)
{
    this->servoController = servoController;
}

void ReleaseBlock::loop()
{
    bool goForward = true;
    ledController->flashAmber();
    motorController->goStraight(goForward);
    delay(300);
    motorController->release();
    delay(500);
    ledController->stopAmber();

    servoController->release();
    ledController->resetBlockLED();

    goForward = false;
    ledController->flashAmber();
    motorController->goStraight(goForward);
    delay(300);
    motorController->release();
    delay(500);
    ledController->stopAmber();
}

ReverseMotion::ReverseMotion(
    Logger *logger = nullptr,
    MotorController *motorController = nullptr,
    LEDController *ledController = nullptr
) : IStage(logger, motorController, ledController){};

void ReverseMotion::loop()
{
    ledController->flashAmber();
    motorController->goStraight(false);
}
