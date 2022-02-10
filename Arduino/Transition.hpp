#ifndef Transition_H
#define Transition_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "Motion.hpp"
#include "Sensor.hpp"
#include "Stages.hpp"

enum ObstructionState : byte {
    Unobstructed,
    UpRamp,
    DownRamp,
    Block
};

class ITransition {
    public:
        ITransition(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0
        );
        virtual bool shouldStageEnd() = 0;

    protected:
        Logger *logger;
        unsigned long startTime;
        unsigned long suppressTime;
};

class Once : public ITransition {
    public:
        Once(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0
        );
        bool shouldStageEnd();
};

class Timed : public ITransition {
    public:
        Timed(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0
        );
        bool shouldStageEnd();
};

class DetectBlock : public ITransition {
    public:
        DetectBlock(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0,
            InfraRed *infrared = nullptr
        );
        bool shouldStageEnd();

    private:
        LEDController *ledController;
        InfraRed *infrared;
        ObstructionState currentObstruction;
        unsigned long lastObstructedTime;
};

class DetectLine : public ITransition {
    public:
        DetectLine(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0,
            LineSensor *lineSensor = nullptr
        );
        bool shouldStageEnd();

    private:
        LineSensor *lineSensor = nullptr;
};

class DetectCross : public ITransition {
    public:
        DetectCross(
            Logger *logger = nullptr,
            unsigned long suppressTime = 0,
            LineSensor *lineSensor = nullptr
        );
        bool shouldStageEnd();

    private:
        LineSensor *lineSensor;
};

#endif