#ifndef Injection_H
#define Injection_H

#include "Stages.h"

class Injection {
    public:
        Injection(bool bluetoothMode);

        Logger *logger;
        LineTracing *lineTracing;
        MotorController *motorController;

    private:
        ServoController *servoController;
        LEDController *ledController;

        LineSensor *lineSensor;
        UltrasonicSensor *ultrasonicSensor;
        InfraRedDigital *infraRedDigital;
        InfraRedAnalogue *infraRedAnalogue;
};

#endif