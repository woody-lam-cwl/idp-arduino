#include "Transition.hpp"

ITransition::ITransition(
    Logger &logger,
    unsigned long suppressTime
) : logger {logger},
    startTime {millis()},
    suppressTime {suppressTime}{}

Once::Once(
    Logger &logger,
    unsigned long suppressTime = 0
) : ITransition(logger, suppressTime){};

bool Once::shouldStageEnd()
{
    logger.log("Stage executed once. Now ending.", LoggerLevel::Info);
    return true;
}

Timed::Timed(
    Logger &logger,
    unsigned long suppressTime
) : ITransition(logger, suppressTime) {}

bool Timed::shouldStageEnd()
{
    unsigned long currentTime = millis();

    if (currentTime - startTime < suppressTime) return false;
    logger.log("Stage time limit reached. Now ending.", LoggerLevel::Info);
    return true;
}

DetectObstruction::DetectObstruction(
    Logger &logger,
    unsigned long suppressTime,
    InfraRed &infrared
) : ITransition(logger, suppressTime),
    infrared {infrared} {}

bool DetectObstruction::shouldStageEnd()
{
    short reading = infrared.getInfraRedReading();
    unsigned long currentTime = millis();

    if (reading > IR_ADC_THRESHOLD & currentTime - startTime > suppressTime) {
        logger.log("Obstruction detected. Now ending stage.", LoggerLevel::Info);
        return true;
    }
    return false;
}

DetectLine::DetectLine(
    Logger &logger,
    unsigned long suppressTime,
    LineSensor &lineSensor
) : ITransition(logger, suppressTime),
    lineSensor {lineSensor} {}

bool DetectLine::shouldStageEnd()
{
    LineReading reading = lineSensor.getLineReading();
    unsigned long currentTime = millis();
    if (reading != LineReading::L111 && currentTime - startTime > suppressTime) {
        logger.log("Line detected. Now ending stage.", LoggerLevel::Info);
        return true;
    }
    return false;
}

DetectCross::DetectCross(
    Logger &logger,
    unsigned long suppressTime,
    LineSensor &lineSensor
) : ITransition(logger, suppressTime),
    lineSensor {lineSensor} {}

bool DetectCross::shouldStageEnd()
{
    LineReading reading = lineSensor.getLineReading();
    unsigned long currentTime = millis();
    if (reading == LineReading::L000 && currentTime - startTime > suppressTime) {
        logger.log("Cross detected. Now ending stage.", LoggerLevel::Info);
        return true;
    }
    return false;
}
