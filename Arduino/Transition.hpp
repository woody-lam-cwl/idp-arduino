#ifndef Transition_H
#define Transition_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "Motion.hpp"
#include "Sensor.hpp"
#include "Stages.hpp"

class ITransition {
    public:
        ITransition(
            Logger &logger,
            unsigned long suppressTime
        );
        virtual bool shouldStageEnd() = 0;

    protected:
        Logger &logger;
        unsigned long startTime;
        unsigned long suppressTime;
};

class Once : public ITransition {
    public:
        Once(
            Logger &logger,
            unsigned long suppressTime = 0
        );
        bool shouldStageEnd();
};

class Timed : public ITransition {
    public:
        Timed(
            Logger &logger,
            unsigned long suppressTime
        );
        bool shouldStageEnd();
};

class DetectObstruction : public ITransition {
    public:
        DetectObstruction(
            Logger &logger,
            unsigned long suppressTime,
            InfraRed &infrared
        );
        bool shouldStageEnd();

    private:
        InfraRed &infrared;
};

class DetectLine : public ITransition {
    public:
        DetectLine(
            Logger &logger,
            unsigned long suppressTime,
            LineSensor &lineSensor
        );
        bool shouldStageEnd();

    private:
        LineSensor &lineSensor;
};

class DetectCross : public ITransition {
    public:
        DetectCross(
            Logger &logger,
            unsigned long suppressTime,
            LineSensor &lineSensor
        );
        bool shouldStageEnd();

    private:
        LineSensor &lineSensor;
};

#endif