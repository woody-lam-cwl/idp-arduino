#ifndef Sequence_H
#define Sequence_H

#include <Arduino.h>
#include "Injection.hpp"

enum class TurnState : byte {
    Default,
    OnBlockType,
    ReverseOnBlockType
};

class Mode {
    public:
        Mode(
            EnumStage stage,
            EnumTransition transition,
            unsigned long suppressTime = 0,
            TurnState turnState = TurnState::Default
        );
        EnumStage stage;
        EnumTransition transition;
        unsigned long suppressTime = 0;
        TurnState turnState = TurnState::Default;
        Mode* nextMode = nullptr;
};

class TaskSequence {
    public:
        TaskSequence(Injection &injection);
        void loop();

    private:
        Injection &injection;
        Mode *activeMode;
        IStage *currentStage;
        ITransition *currentTransition;
        void setNextMode(Mode *nextMode);
        bool shouldTurnLeft(TurnState turnState);
};

#endif
