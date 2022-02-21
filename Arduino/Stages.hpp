#ifndef Stages_H
#define Stages_H

#include <Arduino.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "Motion.hpp"
#include "Sensor.hpp"

enum class LineStatus : byte {
    OnLine,
    TooLeft,
    TooRight,
    Unknown,
};

class IStage {
    public:
        IStage(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &ledController
        );
        virtual void loop();
        IStage *nextStage;
        virtual ~IStage();

    protected:
        Logger &logger;
        StateMonitor &stateMonitor;
        MotorController &motorController;
        LEDController &ledController;
        unsigned long loopTimes;
        unsigned long startTime;
};

class ForwardLineTracing : public IStage {
    public:
        ForwardLineTracing(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &ledController,
            LineSensor &lineSensor
        );
        void loop();

    private:
        LineSensor &lineSensor;
        LineStatus getLineStatus();
};

class Turning : public IStage {
    public:
        Turning(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &ledController,
            bool turnLeft = true
        );
        void loop();

    private:
        bool turnLeft;
};

class GrabBlock : public IStage {
    public:
        GrabBlock(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &ledController,
            ServoController &servoController
        );
        void loop();

    private:
        ServoController &servoController;
};

class ClassifyBlock : public IStage {
    public:
        ClassifyBlock(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            ServoController &servoController,
            LEDController &ledController,
            UltrasonicSensor &ultrasonicSensor
        );
        void loop();
        ~ClassifyBlock();

    private:
        ServoController &servoController;
        UltrasonicSensor &ultrasonicSensor;
        int acceptedCoarseCount;
        int invalidCount;
};

class ReleaseBlock : public IStage {
    public:
        ReleaseBlock(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &ledController,
            ServoController &servoController
        );
        void loop();
    
    private:
        ServoController &servoController;
};

class ReverseMotion : public IStage {
    public:
        ReverseMotion(
            Logger &logger,
            StateMonitor &stateMonitor,
            MotorController &motorController,
            LEDController &LEDController
        );
        void loop();
};

#endif
