#ifndef alcoholDetectorH
#define alcoholDetectorH

#include "Arduino.h"

class AlcoholDetector
{
private:
    byte _pin;
    unsigned int _maxValue = 0;
public:
    AlcoholDetector(byte pin);
    void Calibrate();
    void Check();
    void Reset();
};

#endif //alcoholDetectorH