#include "Injection.h"

Injection::Injection(bool bluetoothMode) {
    logger = new Logger(bluetoothMode);
    stateMonitor = new StateMonitor();

    motorController = new MotorController(logger);
    servoController = new ServoController(logger);
    ledController = new LEDController(logger);

    lineSensor = new LineSensor(logger);
    ultrasonicSensor = new UltrasonicSensor(logger);
    infraRedDigital = new InfraRedDigital(logger);
    infraRedAnalogue = new InfraRedAnalogue(logger);

    lineTracing = new LineTracing(logger,
        motorController,
        lineSensor,
        ledController);
}