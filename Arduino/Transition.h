#ifndef Transition_H
#define Transition_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "Motion.h"
#include "Sensor.h"
#include "Stages.h"

class IStage;

class ITransition {
    public:
        ITransition(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr,
            IStage *nextSequentialStage = nullptr);
        virtual bool shouldStageEnd() = 0;
        virtual void exitProcedure() = 0;

    protected:
        Logger *logger;
        StateMonitor *stateMonitor;
        IStage *nextSequentialStage;
};

class DetectBlock : public ITransition {
    public:
        DetectBlock(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr,
            IStage *nextSequentialStage = nullptr,
            MotorController *motorController = nullptr,
            ServoController *servoController = nullptr,
            LEDController *ledController = nullptr,
            InfraRedDigital *infraredDigital = nullptr,
            UltrasonicSensor *ultrasonicSensor = nullptr);
        bool shouldStageEnd();
        void exitProcedure();

    private:
        MotorController *motorController;
        ServoController *servoController;
        LEDController *ledController;
        InfraRedDigital *infraredDigital;
        UltrasonicSensor *ultrasonicSensor;
};

class FinishTurn : public ITransition {
    public:
        FinishTurn(
            Logger *logger = nullptr,
            StateMonitor *stateMonitor = nullptr,
            IStage *nextSequentialStage = nullptr,
            LEDController *ledController = nullptr,
            LineSensor *lineSensor = nullptr
        );
        bool shouldStageEnd();
        void exitProcedure();
};

class Grabbing : public ITransition {
    public:
        bool shouldStageEnd();
        void exitProcedure();
};

#endif