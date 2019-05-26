#include "AlcoholDetector.h"

AlcoholDetector::AlcoholDetector(byte pin)
{
    _pin = pin;
}

void AlcoholDetector::Calibrate()
{
}

void AlcoholDetector::Reset()
{
    _maxValue = 0;
}

void AlcoholDetector::Check()
{
    auto value = analogRead(_pin);
    if (value < 200)
    {
        Serial.println("You are sober.");
    }
    if (value >= 200 && value < 280)
    {
        Serial.println("You had a beer.");
    }
    if (value >= 280 && value < 350)
    {
        Serial.println("Two or more beers.");
    }
    if (value >= 350 && value < 450)
    {
        Serial.println("I smell vodka!");
    }
    if (value > 450)
    {
        Serial.println("You are drunk!");
    }
}
