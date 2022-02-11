#include "Transition.hpp"

ITransition::ITransition(
    Logger &logger,
    unsigned long suppressTime
) : logger {logger},
    startTime {millis()},
    suppressTime {suppressTime},
    isSuppressed {true} {}

bool ITransition::shouldStageEnd()
{
    if (isSuppressed && !isAfterSuppressTime()) return false;
    return true;
}

bool ITransition::isAfterSuppressTime()
{
    unsigned long currentTime = millis();
    if (currentTime - startTime < suppressTime) return false;
    isSuppressed = false;
    return true;
}

Once::Once(
    Logger &logger,
    unsigned long suppressTime = 0
) : ITransition(logger, suppressTime) {}

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
    if (!ITransition::shouldStageEnd()) return false;
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
    if (!ITransition::shouldStageEnd()) return false;
    short reading = infrared.getInfraRedReading();
    if (reading > IR_ADC_THRESHOLD) {
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
    if (!ITransition::shouldStageEnd()) return false;
    LineReading reading = lineSensor.getLineReading();
    if (reading != LineReading::L111) {
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
    if (!ITransition::shouldStageEnd()) return false;
    LineReading reading = lineSensor.getLineReading();
    if (reading == LineReading::L000) {
        logger.log("Cross detected. Now ending stage.", LoggerLevel::Info);
        return true;
    }
    return false;
}
