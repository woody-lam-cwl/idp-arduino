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

class ITransition;

class IStage {
    public:
        IStage(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr
        );
        virtual void loop() = 0;
        IStage *nextStage = nullptr;
        ITransition *stageTransition = nullptr;
        ~IStage();

    protected:
        Logger *logger;
        MotorController *motorController;
        LEDController *ledController;
};

class ForwardLineTracing : public IStage {
    public:
        ForwardLineTracing(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr,
            LineSensor *lineSensor = nullptr
        );
        void loop();

    private:
        LineSensor *lineSensor;
        LineStatus getLineStatus();
};

class Turning : public IStage {
    public:
        Turning(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr,
            bool turnLeft = true
        );
        void loop();

    private:
        bool turnLeft;
};

class GrabClassifyBlock : public IStage {
    public:
        GrabClassifyBlock(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr,
            ServoController *servoController = nullptr,
            UltrasonicSensor *ultrasonicSensor = nullptr
        );
        void loop();

    private:
        ServoController *servoController;
        UltrasonicSensor *ultrasonicSensor;
};

class ReleaseBlock : public IStage {
    public:
        ReleaseBlock(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr,
            ServoController *servoController = nullptr
        );
        void loop();
    
    private:
        ServoController *servoController;
};

class ReverseMotion : public IStage {
    public:
        ReverseMotion(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *LEDController = nullptr
        );
        void loop();
};

#endif