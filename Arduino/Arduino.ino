#include "Constants.hpp"
#include "Injection.hpp"
#include "UnitTest.hpp"
#include "Sequence.hpp"

Injection *injection;
TaskSequence *sequence;
IUnitTest *testPtr;

void setup()
{
    injection = new Injection();
    sequence = new TaskSequence(*injection);
    
    LineSensorTest test;
    test.setup(&injection->logger);
    testPtr = &test;
    
    injection->logger.setLevel(LoggerLevel::DebugStage);
    injection->logger.log("System Initialised", Info);
}

void loop()
{
    sequence->loop();
    // testPtr->loop();
}