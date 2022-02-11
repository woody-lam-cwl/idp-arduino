#ifndef Injection_H
#define Injection_H

#include "StateMonitor.hpp"
#include "Stages.hpp"
#include "Transition.hpp"

class Injection {
    public:
        Injection();
        Logger logger;
        StateMonitor stateMonitor;
        
        IStage* getNewStage(
            EnumStage stage,
            bool turnLeft = true
        );
        ITransition* getNewTransition(
            EnumTransition transition,
            unsigned long suppressTime = 0
        );

        LineSensor lineSensor;

    private:
        MotorController motorController;
        ServoController servoController;
        LEDController ledController;

        UltrasonicSensor ultrasonicSensor;
        InfraRed infraRed;

        ForwardLineTracing* getNewForwardLineTracing();
        Turning* getNewTurning(bool turnLeft);
        GrabClassifyBlock* getNewGrabClassifyBlock();
        ReleaseBlock* getNewReleaseBlock();
        ReverseMotion* getNewReverseMotion();

        Once* getNewOnce(unsigned long suppressTime = 0);
        Timed* getNewTimed(unsigned long suppressTime = 0);
        DetectObstruction* getNewDetectObstruction(unsigned long suppressTime = 0);
        DetectLine* getNewDetectLine(unsigned long suppressTime = 0);
        DetectCross* getNewDetectCross(unsigned long suppressTime = 0);
};

#endif