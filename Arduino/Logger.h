#ifndef Logger_H
#define Logger_H

#include <Arduino.h>
#include <String.h>
#include "Constants.h"

enum LoggerLevel {
    Debug,
    Info,
    Error,
    Fatal
};

class Logger {
    public:
        Logger();
        void log(String message, LoggerLevel level);
};

#endif