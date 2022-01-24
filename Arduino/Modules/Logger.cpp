#include "Logger.h"

void Logger::setup() {
    if (Serial) return;
    Serial.begin(BAUD_RATE);
    while (!Serial)
    {
        ;
    }
    log("Logger Initialised", LoggerLevel::Info);
}

void Logger::log(char message[], LoggerLevel level = LoggerLevel::Debug) {
    String messagePrefix = prefix[level];
    Serial.println(messagePrefix + message);
}