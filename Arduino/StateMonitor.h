#ifndef StateMonitor_H
#define StateMonitor_H

#include <Arduino.h>
#include "Constants.h"

enum class Direction : byte {
    Drive,
    Reverse,
    Neutral
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
    Coarse,
    Fine,
    NoBlock
};

template <typename T>
class State {
    public:
        void updateState(T newState);
        T getState();
        unsigned long getLastUpdateTime();
    
    protected:
        T state;
        unsigned long lastUpdateTime;
};

class MotorConfig {
    public:
        byte speed = 0;
        Direction direction = Direction::Neutral;
};

class ServoAngle : public State<byte>{};

class LEDAmberFlashState : public State<bool>{};

class LEDRedState : public State<bool>{};

class LEDGreenState : public State<bool>{};

class UltrasonicDistanceInMM : public State<unsigned long>{};

class InfraredDigitalIsPathClear : public State<bool>{};

class InfraredAnalogueReading : public State<bool>{};

class StateMonitor {
    public:
        State<MotorConfig> leftMotorState;
        State<MotorConfig> rightMotorState;
        ServoAngle servoState;

        LEDAmberFlashState ledAmberFlashState;
        LEDRedState ledRedState;
        LEDGreenState ledGreenState;

        State<LineReading> lineSensorState;
        UltrasonicDistanceInMM ultrasonicState;
        InfraredDigitalIsPathClear infraredDigitalState;
        InfraredAnalogueReading infraredAnalogueState;

        State<BlockType> blockState;
};

#endif