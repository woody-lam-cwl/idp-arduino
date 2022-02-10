#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"

enum LineReading : byte {
    L000 = 0U,
    L001 = 1U,
    L010 = 2U,
    L011 = 3U,
    L100 = 4U,
    L101 = 5U,
    L110 = 6U,
    L111 = 7U,
};

class LineSensor {
    public:
        LineSensor(Logger &logger);
        LineReading getLineReading();

    private:
        Logger &logger;
};

class UltrasonicSensor {
    public:
        UltrasonicSensor(Logger &logger);
        unsigned long getDistanceInMM();

    private:
        Logger &logger;
};

class InfraRed {
    public:
        InfraRed(
            Logger &logger);
        short getInfraRedReading();

    private:
        Logger &logger;
};

#endif