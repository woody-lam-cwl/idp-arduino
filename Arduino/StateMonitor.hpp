#ifndef StateMonitor_H
#define StateMonitor_H

#include "Logger.hpp"
#include "State.hpp"

enum class Direction : byte {
    Drive,
    Reverse,
    Neutral
};

class MotorConfig {
    public:
        byte speed;
        Direction direction;
};

enum LineReading : byte {
    L000 = 0U,
    L001 = 1U,
    L010 = 2U,
    L011 = 3U,
    L100 = 4U,
    L101 = 5U,
    L110 = 6U,
    L111 = 7U,
};

enum class BlockType : byte {
    NoBlock,
    CoarseBlock,
    FineBlock
};

enum class EnumStage : byte {
    ForwardLineTracing,
    Turning,
    GrabClassifyBlock,
    ReleaseBlock,
    ReverseMotion
};

enum class EnumTransition : byte {
    Once,
    Timed,
    DetectObstruction,
    DetectLine,
    DetectCross
};

class MotorState{
    public:
        State<byte> speed;
        State<Direction> direction;
};

class StateMonitor{
    public:
        MotorState leftMotorState;
        MotorState rightMotorState;
        State<bool> servoGrabbed;
        State<bool> amberFlashing;
        State<bool> redOn;
        State<bool> greenOn;

        State<LineReading> lineReadingState;
        State<unsigned long> ultrasonicDistance;
        State<short> infraRedReading;

        State<BlockType> blockType;
        State<EnumStage> activeStage;
        State<EnumTransition> activeTransition;
};

#endif