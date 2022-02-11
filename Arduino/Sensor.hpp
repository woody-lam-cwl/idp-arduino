#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "StateMonitor.hpp"

class LineSensor {
    public:
        LineSensor(Logger &logger, StateMonitor &stateMonitor);
        LineReading getLineReading();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
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