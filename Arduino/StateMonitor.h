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
        void updateState(T newState)
        {
            this->state = newState;
            this->lastUpdateTime = millis();
        };

        T getState();
        unsigned long getLastUpdateTime();
    
    protected:
        T state;
        unsigned long lastUpdateTime = 0;
};

template <typename T>
T State<T>::getState()
{
    return this->state;
}

template <typename T>
unsigned long State<T>::getLastUpdateTime()
{
    return this->lastUpdateTime;
}

class MotorState {
    public:
        State<byte> speed;
        State<Direction> direction;
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
        MotorState leftMotorState;
        MotorState rightMotorState;
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