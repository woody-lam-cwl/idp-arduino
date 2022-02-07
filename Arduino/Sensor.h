#ifndef Sensor_H
#define Sensor_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "StateMonitor.h"

class LineSensor {
    public:
        LineSensor(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr);
        void updateLineReading();

    private:
        Logger *logger;
        StateMonitor *stateMonitor;
};

class UltrasonicSensor {
    public:
        UltrasonicSensor(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr);
        void updateDistanceInMM();

    private:
        Logger *logger;
        StateMonitor *stateMonitor;
};

class InfraRedDigital {
    public:
        InfraRedDigital(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr);
        void updateIsPathClear();

    private:
        Logger *logger;
        StateMonitor *stateMonitor;
};

class InfraRedAnalogue {
    public:
        InfraRedAnalogue(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr);
        void updateInfraRedReading();

    private:
        Logger *logger;
        StateMonitor *stateMonitor;
};

#endif