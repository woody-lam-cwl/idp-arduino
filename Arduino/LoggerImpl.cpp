#include "Logger.hpp"

Logger::Logger()
{
    Serial.begin(BAUD_RATE);
    while (!Serial);
    log("Logger Initialised", LoggerLevel::Info);
}

void Logger::log(String message, LoggerLevel level = LoggerLevel::Debug)
{
    String prefix[4] = {"Debug: ", "Info: ", "Error: ", "Fatal: "};
    String messagePrefix = prefix[level];
    Serial.println(messagePrefix + message);
}
