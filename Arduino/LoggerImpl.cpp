#include "Logger.h"

Logger::Logger(bool bluetoothMode = false) {
    this->bluetoothMode = bluetoothMode && !WIRED_SERIAL_OVERRIDE;
    if (bluetoothMode) {
        pinMode(NINA_RESETN, OUTPUT);
        digitalWrite(NINA_RESETN, LOW);
        SerialNina.begin(BAUD_RATE);
        while (!SerialNina);
    }
    else {
        Serial.begin(BAUD_RATE);
        while (!Serial);
    }
    
    log("Logger Initialised", LoggerLevel::Info);
}

void Logger::log(String message, LoggerLevel level = LoggerLevel::Debug) {
    String prefix[4] = {"Debug: ", "Info: ", "Error: ", "Fatal: "};
    String messagePrefix = prefix[level];
    if (bluetoothMode) SerialNina.println(messagePrefix + message);
    else Serial.println(messagePrefix + message);
}