#ifndef StateMonitor_H
#define StateMonitor_H

#include "Logger.hpp"
#include "StateImpl.hpp"

enum LineReading : byte {
    L000 = 0U,
    L001 = 1U,
    L010 = 2U,
    L011 = 3U,
    L100 = 4U,
    L101 = 5U,
    L110 = 6U,
    L111 = 7U,
};

class StateMonitor{
    public:
        StateMonitor(Logger &logger);
        LineReading lineReading = LineReading::L000;

    private:
        Logger &logger;
};

#endif