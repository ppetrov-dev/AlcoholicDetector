#ifndef alcoholDetectorH
#define alcoholDetectorH

#include "Arduino.h"

extern "C"
{
    typedef void (*alcoholDetectorCallback)(void);
}

class AlcoholDetector
{
private:
    byte _pin;
    unsigned int _maxValue = 0;
    unsigned int _lastValue = 0;
    String _lastResolutionString;
    String _lastValuesString;

    alcoholDetectorCallback _resolutionStringChangedCallback;
    alcoholDetectorCallback _valuesStringChangedCallback;

    String GetResolutionString(unsigned int value);
    String GetValuesString(unsigned int value);

    void TryRaiseValuesStringChanged(unsigned int value);
    void TryRaiseResolutionStringChanged(unsigned int value);
public:
    AlcoholDetector(byte pin);
    void Tick();
    void Calibrate();

    void AttachOnResolutionStringChanged(alcoholDetectorCallback callback);
    void AttachOnValuesStringChanged(alcoholDetectorCallback callback);
    String GetResolutionString();
    String GetValuesString();
    
    void Reset();
};

#endif //alcoholDetectorH