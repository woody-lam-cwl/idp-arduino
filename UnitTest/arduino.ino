bool ledState;
unsigned long lastChangedTime;

void setup()
{
    ledState = false;
    lastChangedTime = 0;
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    unsigned long currentTime = millis();
    if (currentTime - lastChangedTime > 500)
    {
        lastChangedTime = currentTime;
        digitalWrite(LED_BUILTIN, ledState);
        ledState = !ledState;
    }
}