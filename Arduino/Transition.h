#ifndef Transition_H
#define Transition_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "Motion.h"
#include "Sensor.h"
#include "Stages.h"

class ITransition {
    public:
        ITransition(Logger *logger = nullptr);
        virtual bool shouldStageEnd() = 0;
        virtual void exitProcedure() = 0;

    protected:
        Logger *logger;
};

class DetectBlock : public ITransition {
    public:
        DetectBlock(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            ServoController *servoController = nullptr,
            LEDController *ledController = nullptr,
            InfraRedAnalogue *infraredAnalogue = nullptr,
            UltrasonicSensor *ultrasonicSensor = nullptr);
        bool shouldStageEnd();
        void exitProcedure();

    private:
        MotorController *motorController;
        ServoController *servoController;
        LEDController *ledController;
        InfraRedAnalogue *infraredAnalogue;
        UltrasonicSensor *ultrasonicSensor;
};

class FinishTurn : public ITransition {
    public:
        FinishTurn(
            Logger *logger = nullptr,
            MotorController *motorController = nullptr,
            LEDController *ledController = nullptr,
            LineSensor *lineSensor = nullptr
        );
        bool shouldStageEnd();
        void exitProcedure();

    private:
        unsigned long startTime = 0;
        MotorController *motorController = nullptr;
        LEDController *ledController= nullptr;
        LineSensor *lineSensor = nullptr;
};

class Grabbing : public ITransition {
    public:
        bool shouldStageEnd();
        void exitProcedure();
};

#endif