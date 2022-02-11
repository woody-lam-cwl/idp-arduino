#ifndef Logger_H
#define Logger_H

#include <Arduino.h>
#include <String.h>
#include "Constants.hpp"

enum LoggerLevel {
    DebugHardware,
    DebugStage,
    Info,
    Error,
    Fatal
};

class Logger {
    public:
        Logger();
        void log(String message, LoggerLevel level = LoggerLevel::Info);
        void setLevel(LoggerLevel level);

    private:
        LoggerLevel logLevel = LoggerLevel::Info;
};

#endif
