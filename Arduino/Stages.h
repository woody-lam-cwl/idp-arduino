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

class ITransition;

class IStage {
    public:
        IStage(Logger *logger = nullptr);
        virtual IStage* loop();
        IStage *nextStage = nullptr;
        ITransition *stageTransition = nullptr;

    protected:
        Logger *logger;
};

class LineTracing : public IStage {
    public:
        LineTracing(
            Logger *logger = nullptr,
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
        Turning(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr);
        IStage* loop();
    
    private:
        MotorController *motorController;
        LEDController *ledController;
};

class Searching : public IStage {
    public:
        Searching(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            InfraRedAnalogue *infraredAnalogue = nullptr,
            UltrasonicSensor *ultrasonicSensor = nullptr);
};

class Placing : public IStage {
    public:
        Placing(
            Logger *logger = nullptr,
            MotorController * motorController = nullptr
        );
};

#endif