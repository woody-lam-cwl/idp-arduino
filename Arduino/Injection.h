#ifndef Injection_H
#define Injection_H

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
        ServoController *servoController;
        LEDController *ledController;

        LineSensor *lineSensor;
        InfraRed *infraRed;

        DetectBlock *detectBlock;
        FinishTurn *finishTurn;
};

#endif