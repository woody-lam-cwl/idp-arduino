#ifndef Injection_H
#define Injection_H

#include "Stages.h"

class Injection {
    public:
        Injection();
        Logger *logger;

        LineTracing *lineTracing;
        Turning *turning;

        DetectBlock *detectBlock;
        DetectCross *detectCross;
        FinishTurn *finishTurn;
        TimedTurn *timedTurn;

    private:
        MotorController *motorController;
        ServoController *servoController;
        LEDController *ledController;

        LineSensor *lineSensor;
        UltrasonicSensor *ultrasonicSensor;
        InfraRed *infraRed;
};

#endif