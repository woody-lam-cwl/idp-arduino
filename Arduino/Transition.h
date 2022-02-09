#ifndef Transition_H
#define Transition_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "Motion.h"
#include "Sensor.h"
#include "Stages.h"

enum ObstructionState : byte {
    Unobstructed,
    UpRamp,
    DownRamp,
    Block
};

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
            InfraRed *infrared = nullptr,
            UltrasonicSensor *ultrasonicSensor = nullptr);
        bool shouldStageEnd();
        void exitProcedure();

    private:
        MotorController *motorController;
        ServoController *servoController;
        LEDController *ledController;
        InfraRed *infrared;
        UltrasonicSensor *ultrasonicSensor;
        ObstructionState currentState = ObstructionState::Unobstructed;
        unsigned long lastObstructedTime = 0;
        unsigned long triggerTime = 0;
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