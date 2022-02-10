#ifndef Stages_H
#define Stages_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "Motion.hpp"
#include "Sensor.hpp"
#include "Transition.hpp"

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
            InfraRed *infrared = nullptr,
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