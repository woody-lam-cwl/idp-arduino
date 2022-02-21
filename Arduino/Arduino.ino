#include "Constants.hpp"
#include "Injection.hpp"
#include "UnitTest.hpp"
#include "Sequence.hpp"

Injection *injection;
TaskSequence *sequence;
IUnitTest *testPtr;
volatile bool hasProgramStarted = false;

void start()
{
    hasProgramStarted = true;
}

void setup()
{
    pinMode(START_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(START_BUTTON_PIN), start, CHANGE);

    injection = new Injection();
    sequence = new TaskSequence(*injection);
    
    UltrasonicTest test;
    test.setup(&injection->logger);
    testPtr = &test;
    
    injection->logger.setLevel(LoggerLevel::DebugHardware);
    injection->logger.log("System Initialised", Info);

    while (!hasProgramStarted){};
    injection->logger.log("Program Starting", Info);
}

void loop()
{
    sequence->loop();
    // testPtr->loop();
}