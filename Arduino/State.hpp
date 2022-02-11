template <typename T>
class State{
    public:
        void updateState(T newState);
        T getState();
        unsigned long getLastUpdatedTime();

    private:
        T state;
        unsigned long lastUpdatedTime;
};

template <typename T>
void State<T>::updateState(T newState)
{
    state = newState;
    lastUpdatedTime = millis();
}

template <typename T>
T State<T>::getState()
{
    return state;
}

template <typename T>
unsigned long State<T>::getLastUpdatedTime()
{
    return lastUpdatedTime;
}