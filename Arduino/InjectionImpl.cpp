#include "Injection.h"

Injection::Injection() {
    logger = new Logger();
    stateMonitor = new StateMonitor();

    motorController = new MotorController(logger, stateMonitor);
    servoController = new ServoController(logger, stateMonitor);
    ledController = new LEDController(logger, stateMonitor);

    lineSensor = new LineSensor(logger, stateMonitor);
    ultrasonicSensor = new UltrasonicSensor(logger, stateMonitor);
    infraRedDigital = new InfraRedDigital(logger, stateMonitor);
    infraRedAnalogue = new InfraRedAnalogue(logger, stateMonitor);

    lineTracing = new LineTracing(
        logger,
        stateMonitor,
        motorController,
        lineSensor,
        ledController);

    turning = new Turning(
        logger,
        stateMonitor,
        motorController,
        ledController
    );

    detectBlock = new DetectBlock(
        logger,
        stateMonitor,
        turning,
        motorController,
        servoController,
        ledController,
        infraRedDigital,
        ultrasonicSensor);
}