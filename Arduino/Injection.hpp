#ifndef Injection_H
#define Injection_H

#include "Stages.hpp"
#include "Transition.hpp"

enum class EnumStage : byte {
    ForwardLineTracing,
    Turning,
    GrabClassifyBlock,
    ReleaseBlock,
    ReverseMotion
};

enum class EnumTransition : byte {
    Once,
    Timed,
    DetectObstruction,
    DetectLine,
    DetectCross
};

class Injection {
    public:
        Injection();
        Logger *logger;
        
        IStage* getNewStage(
            IStage *currentStage,
            EnumStage stage,
            bool turnLeft = true
        );
        ITransition* getNewTransition(
            ITransition *currentTransition,
            EnumTransition transition,
            unsigned long suppressTime = 0
        );

    private:
        MotorController *motorController;
        ServoController *servoController;
        LEDController *ledController;

        LineSensor *lineSensor;
        UltrasonicSensor *ultrasonicSensor;
        InfraRed *infraRed;

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