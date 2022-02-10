#ifndef Sequence_H
#define Sequence_H

#include <Arduino.h>
#include "Injection.hpp"

class TaskSequence {
    public:
        TaskSequence(Injection *injection);
        IStage* setCurrentStage();

    private:
        Injection *injection;
};

#endif