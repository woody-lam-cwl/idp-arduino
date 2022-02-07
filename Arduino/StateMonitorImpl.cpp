#include "StateMonitor.h"

template <typename T>
void State<T>::updateState(T newState)
{
    this->state = T;
    this->lastUpdateTime = millis();
}

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