#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"

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
        LineSensor(Logger *logger = nullptr);
        LineReading getLineReading();

    private:
        Logger *logger;
};

class UltrasonicSensor {
    public:
        UltrasonicSensor(Logger *logger = nullptr);
        unsigned long getDistanceInMM();

    private:
        Logger *logger;
};

class InfraRedDigital {
    public:
        InfraRedDigital(Logger *logger = nullptr);
        bool getIsPathClear();

    private:
        Logger *logger;
};

class InfraRedAnalogue {
    public:
        InfraRedAnalogue(
            Logger *logger = nullptr);
        short getInfraRedReading();

    private:
        Logger *logger;
};

#endif