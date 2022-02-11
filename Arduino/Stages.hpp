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
            MotorController &motorController,
            LEDController &ledController
        );
        virtual void loop() = 0;
        IStage *nextStage;
        ~IStage();

    protected:
        Logger &logger;
        MotorController &motorController;
        LEDController &ledController;
};

class ForwardLineTracing : public IStage {
    public:
        ForwardLineTracing(
            Logger &logger,
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
            MotorController &motorController,
            LEDController &ledController,
            bool turnLeft = true
        );
        void loop();

    private:
        bool turnLeft;
};

class GrabClassifyBlock : public IStage {
    public:
        GrabClassifyBlock(
            Logger &logger,
            MotorController &motorController,
            LEDController &ledController,
            ServoController &servoController,
            UltrasonicSensor &ultrasonicSensor
        );
        void loop();

    private:
        ServoController &servoController;
        UltrasonicSensor &ultrasonicSensor;
};

class ReleaseBlock : public IStage {
    public:
        ReleaseBlock(
            Logger &logger,
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
            MotorController &motorController,
            LEDController &LEDController
        );
        void loop();
};

#endif