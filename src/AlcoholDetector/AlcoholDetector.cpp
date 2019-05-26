#include "AlcoholDetector.h"

AlcoholDetector::AlcoholDetector(byte pin)
{
    _pin = pin;
}
void AlcoholDetector::Calibrate()
{
}
void AlcoholDetector::TryRaiseValuesStringChanged(unsigned int value)
{
    auto valueString = GetValuesString(value);
    if (_lastValuesString == valueString || !_valuesStringChangedCallback)
        return;
    _lastValuesString = valueString;
    _valuesStringChangedCallback();
}
void AlcoholDetector::TryRaiseResolutionStringChanged(unsigned int value)
{
    auto currentResolutionString = GetResolutionString(value);
    if (_lastResolutionString == currentResolutionString || !_resolutionStringChangedCallback)
        return;

    _lastResolutionString = currentResolutionString;
    _resolutionStringChangedCallback();
}
void AlcoholDetector::Tick()
{
    unsigned int value = analogRead(_pin);
    _maxValue = max(value, _maxValue);

    TryRaiseValuesStringChanged(value);
    TryRaiseResolutionStringChanged(value);

    _lastValue = value;
}

void AlcoholDetector::Reset()
{
    _lastValue = 0;
    _maxValue = 0;
    _lastResolutionString = "";
    _lastValuesString = "";
}

String AlcoholDetector::GetResolutionString(unsigned int value)
{
    if (value < 200)
        return "You are sober";
    else if (value >= 200 && value < 280)
        return "You had a beer";
    else if (value >= 280 && value < 350)
        return "2 or more beers";
    else if (value >= 350 && value < 450)
        return "I smell vodka!";
    return "You are drunk!";
}

String AlcoholDetector::GetResolutionString()
{
    return _lastResolutionString;
}
String AlcoholDetector::GetValuesString()
{
    return _lastValuesString;
}
String AlcoholDetector::GetValuesString(unsigned int value)
{
    String stringBuilder;
    stringBuilder.concat(String(value));
    stringBuilder.concat(" max:" + String(_maxValue));
    return stringBuilder;
}

void AlcoholDetector::AttachOnResolutionStringChanged(alcoholDetectorCallback callback)
{
    _resolutionStringChangedCallback = callback;
}
void AlcoholDetector::AttachOnValuesStringChanged(alcoholDetectorCallback callback)
{
    _valuesStringChangedCallback = callback;
}