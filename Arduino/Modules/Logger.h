#ifndef Logger_H
#define Logger_H

#include <Arduino.h>
#include "../Constants.h"

enum LoggerLevel {
    Debug,
    Info,
    Error,
    Fatal
};

class Logger {
    private:
        String prefix[4] = {"Debug: ", "Info: ", "Error: ", "Fatal: "};
    public:
        void setup();
        void log(char message[], LoggerLevel level);
};

#endif