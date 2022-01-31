#ifndef Stages_H
#define Stages_H

#include <Arduino.h>
#include "Constants.h"
#include "Logger.h"
#include "Motion.h"
#include "Sensor.h"

enum class LineStatus : byte {
    OnLine,
    TooLeft,
    TooRight,
    Unknown,
};

class IStage {
    public:
        virtual void loop() = 0;
};

class LineTracing : public IStage {
    public:
        LineTracing(MotorController *motorController, LineSensor *LineSensor);
        void loop();

    private:
        MotorController *motorController;
        LineSensor *lineSensor;
        LineStatus getLineStatus();
};

class Turning : public IStage {
    public:
        void loop();
    
    private:
        MotorController *motorController;
        LineSensor *lineSensor;
};

#endif