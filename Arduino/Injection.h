#ifndef Injection_H
#define Injection_H

#include "Stages.h"

class Injection {
    public:
        Injection();

        Logger *logger;

        LineTracing *lineTracing;
        Turning *turning;

        ServoController *servoController;

    private:
        MotorController *motorController;
        LEDController *ledController;

        LineSensor *lineSensor;
        UltrasonicSensor *ultrasonicSensor;
        InfraRed *infraRed;

        DetectBlock *detectBlock;
        FinishTurn *finishTurn;
};

#endif