#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "StateMonitor.hpp"

class LineSensor {
    public:
        LineSensor(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        LineReading getLineReading();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        void updateLineReading();
};

class UltrasonicSensor {
    public:
        UltrasonicSensor(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        unsigned long getDistanceInMM();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        void updateDistanceInMM();
};

class InfraRed {
    public:
        InfraRed(
            Logger &logger,
            StateMonitor &stateMonitor
        );
        short getInfraRedReading();

    private:
        Logger &logger;
        StateMonitor &stateMonitor;
        void updateInfraRedReading();
};

#endif