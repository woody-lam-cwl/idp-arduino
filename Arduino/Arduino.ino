#include "Constants.h"
#include "Motion.h"
#include "RuntimeTest.h"
#include "Stages.h"

Logger* logger;
IUnitTest* testPtr;
IStage* stagePtr;
MotorController* motorPtr;
LEDController* ledPtr;
LineSensor* lineSensorPtr;

void setup()
{
    bool bluetoothMode = false;
    Logger loggerObj(bluetoothMode);
    logger = &loggerObj;
    logger->setup("System Initialising");

    MotorController motorController(logger);
    LineSensor lineSensor;
    lineSensor.setup(logger);
    LEDController ledController;
    ledController.setup(logger);

    motorPtr = &motorController;
    lineSensorPtr = &lineSensor;
    ledPtr = &ledController;

    // LineTracing lineTracingStage(logger, motorPtr, lineSensorPtr, ledPtr);
    // stagePtr = &lineTracingStage;

    // LineSensorTest test;
    // testPtr = &test;
    // testPtr->setup(logger);

    logger->log("System Initialised", Info);
}

void loop()
{
    // logger->log("In loop", Info);
    // stagePtr->loop();
    // testPtr->loop();
    // motorPtr->goStraight();
    // while(1);

    ledPtr->flashAmber();
}