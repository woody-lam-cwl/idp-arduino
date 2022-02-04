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
        bool shouldStageEnd();
        void exitProcedure();
};

class DetectBlock : public ITransition {
    public:
        bool shouldStageEnd();
        void exitProcedure();
};

class Grabbing : public ITransition {
    public:
        bool shouldStageEnd();
        void exitProcedure();
};

#endif