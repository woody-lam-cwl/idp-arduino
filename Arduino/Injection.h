#ifndef Injection_H
#define Injection_H

#include "StateMonitor.h"
#include "Stages.h"

class Injection {
    public:
        Injection();

        Logger *logger;
        LineTracing *lineTracing;
        Turning *turning;

        
        MotorController *motorController;
        UltrasonicSensor *ultrasonicSensor;

    private:
        StateMonitor *stateMonitor;
        ServoController *servoController;
        LEDController *ledController;

        LineSensor *lineSensor;
        InfraRedDigital *infraRedDigital;
        InfraRedAnalogue *infraRedAnalogue;

        DetectBlock *detectBlock;
};

#endif