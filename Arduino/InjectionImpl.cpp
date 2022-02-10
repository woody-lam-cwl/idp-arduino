#include "Injection.hpp"

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

    detectCross = new DetectCross(
        logger,
        motorController,
        servoController,
        ledController,
        lineSensor
    );

    finishTurn = new FinishTurn(
        logger,
        motorController,
        ledController,
        lineSensor
    );

    timedTurn = new TimedTurn(
        logger,
        motorController,
        servoController,
        ledController
    );

    IStage* lineTracingBack = new LineTracing(
        logger,
        motorController,
        lineSensor,
        ledController
    );

    IStage* firstTurningTimed = new Turning(
        logger,
        motorController,
        ledController
    );

    IStage* secondTurningTimed = new Turning(
        logger,
        motorController,
        ledController
    );

    IStage* turningBack = new Turning(
        logger,
        motorController,
        ledController
    );

    lineTracing->stageTransition = detectBlock;
    lineTracing->nextStage = turning;
    turning->stageTransition = finishTurn;
    turning->nextStage = lineTracingBack;
    lineTracingBack->stageTransition = detectCross;
    lineTracingBack->nextStage = firstTurningTimed;
    firstTurningTimed->stageTransition = timedTurn;
    firstTurningTimed->nextStage = turningBack;
    turningBack->stageTransition = finishTurn;
    turningBack->nextStage = lineTracing;
}