#ifndef Stages_H
#define Stages_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "Motion.h"
#include "Sensor.h"
#include "Transition.h"

enum class LineStatus : byte {
    OnLine,
    TooLeft,
    TooRight,
    Unknown,
};

class IStage {
    public:
        virtual IStage* loop();
        ITransition *stageTransition;

    protected:
        Logger *logger;
        IStage *nextLoopStage = this;
};

class LineTracing : public IStage {
    public:
        LineTracing(Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LineSensor *lineSensor = nullptr,
            LEDController *ledController = nullptr);
        IStage* loop();

    private:
        MotorController *motorController;
        LineSensor *lineSensor;
        LEDController *ledController;
        LineStatus getLineStatus();
};

class Turning : public IStage {
    public:
        Turning(Logger *logger = nullptr,
            MotorController *motorController = nullptr);
        IStage* loop();
    
    private:
        MotorController *motorController;
};

class Grab : public IStage {
    public:
        Grab(Logger *logger = nullptr,
            ServoController *servoController = nullptr);
        IStage* loop();

    private:
        ServoController *servoController;
};

class Release : public IStage {
    public:
        Release(Logger *logger = nullptr,
            ServoController *servoController = nullptr);
        IStage* loop();

    private:
        ServoController *servoController;
};


#endif