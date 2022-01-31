#include "Constants.h"
#include "Motion.h"
#include "RuntimeTest.h"
#include "Stages.h"

Logger* logger;
IUnitTest* testPtr;
IStage* stagePtr;
MotorController* motorPtr;
LineSensor* lineSensorPtr;

void setup()
{
    bool bluetoothMode = false;
    Logger loggerObj(bluetoothMode);
    logger = &loggerObj;
    logger->setup("System Initialised");

    MotorController motorController;
    motorController.setup(logger);
    LineSensor lineSensor;
    lineSensor.setup(logger);

    motorPtr = &motorController;
    lineSensorPtr = &lineSensor;

    LineTracing lineTracingStage(motorPtr, lineSensorPtr);
    stagePtr = &lineTracingStage;

    // InfraRedTest test;
    // testPtr = &test;
    // testPtr->setup(logger);
}

void loop()
{
    stagePtr->loop();

    // testPtr->loop();
}