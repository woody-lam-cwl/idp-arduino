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

    private:
        MotorController motorController;
        ServoController servoController;
        LEDController ledController;

        LineSensor lineSensor;
        UltrasonicSensor ultrasonicSensor;
        InfraRed infraRed;

        ForwardLineTracing* getNewForwardLineTracing();
        Turning* getNewTurning(bool turnLeft);
        GrabBlock* getNewGrabBlock();
        ClassifyBlock* getNewClassifyBlock();
        ReleaseBlock* getNewReleaseBlock();
        ReverseMotion* getNewReverseMotion();

        Once* getNewOnce(unsigned long suppressTime = 0);
        Timed* getNewTimed(unsigned long suppressTime = 0);
        DetectObstruction* getNewDetectObstruction(unsigned long suppressTime = 0);
        DetectLine* getNewDetectLine(unsigned long suppressTime = 0);
        DetectCross* getNewDetectCross(unsigned long suppressTime = 0);
};

#endif
