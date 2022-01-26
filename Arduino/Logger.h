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
        Logger(bool bluetoothMode);
        void setup(String initMessage);
        void log(String message, LoggerLevel level);

    private:
        bool bluetoothMode;
        String prefix[4] = {"Debug: ", "Info: ", "Error: ", "Fatal: "};
};

#endif