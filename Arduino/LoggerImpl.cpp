#include "Logger.hpp"

Logger::Logger()
{
    Serial.begin(BAUD_RATE);
    while (!Serial);
    log("Logger Initialised", LoggerLevel::Info);
}

void Logger::log(String message, LoggerLevel level = LoggerLevel::Info)
{
    if (logLevel > level) return;
    String prefix[5] = {"Debug: ", "Debug: ", "Info: ", "Error: ", "Fatal: "};
    String messagePrefix = prefix[level];
    Serial.println(messagePrefix + message);
}

void Logger::setLevel(LoggerLevel level)
{
    logLevel = level;
}