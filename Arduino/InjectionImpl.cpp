#include "Injection.h"

Injection::Injection() {
    logger = new Logger();

    motorController = new MotorController(logger);
    servoController = new ServoController(logger);
    ledController = new LEDController(logger);

    lineSensor = new LineSensor(logger);
    ultrasonicSensor = new UltrasonicSensor(logger);
    infraRed = new InfraRed(logger);

    lineTracing = new LineTracing(
        logger,
        motorController,
        lineSensor,
        ledController
    );

    turning = new Turning(
        logger,
        motorController,
        ledController
    );

    detectBlock = new DetectBlock(
        logger,
        motorController,
        servoController,
        ledController,
        infraRed,
        ultrasonicSensor
    );

    finishTurn = new FinishTurn(
        logger,
        motorController,
        ledController,
        lineSensor
    );

    lineTracing->stageTransition = detectBlock;
    lineTracing->nextStage = turning;
    turning->stageTransition = finishTurn;
    turning->nextStage = lineTracing;
}