#include "Logger.h"

void Logger::setup() {
    if (BLUETOOTH_SERIAL_ENABLED || !SerialNina) {
        pinMode(NINA_RESETN, OUTPUT);
        digitalWrite(NINA_RESETN, LOW);
        SerialNina.begin(BAUD_RATE);
        while (!SerialNina);
    }

    if (WIRED_SERIAL_ENABLED || !Serial) {
        Serial.begin(BAUD_RATE);
        while (!Serial);
    }
    
    log("Logger Initialised", LoggerLevel::Info);
}

void Logger::log(char message[], LoggerLevel level = LoggerLevel::Debug) {
    String messagePrefix = prefix[level];
    if (BLUETOOTH_SERIAL_ENABLED) SerialNina.println(messagePrefix + message);
    if (WIRED_SERIAL_ENABLED) Serial.println(messagePrefix + message);
}