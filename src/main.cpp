#include <Arduino.h>

#include "Timer/Timer.h"
#include "AlcoholDetector/AlcoholDetector.h"
#include "AlcoholicDetectorStateMachine/AlcoholicDetectorStateMachine.h"
#include "settings.h"
#include "OneButton.h"

Timer _getSensorValueTimer;
AlcoholDetector _alcoholDetector(PIN_AlcoholDetector);
OneButton _button(PIN_Button, true, true);
AlcoholicDetectorStateMachine _alcoholicDetectorStateMachine;

void OnGetSensorValueTimerTick()
{
  auto state = _alcoholicDetectorStateMachine.GetState();
  switch (state)
  {
  case Normal:
    _alcoholDetector.Check(); 
    break;
  case Calibration:
    _alcoholDetector.Calibrate(); 
  break;
  }
}

void OnButtonDoubleClick()
{
  _alcoholicDetectorStateMachine.Run(DoubleClickCommand);
}

void OnButtonLongPressStart()
{
  _alcoholicDetectorStateMachine.Run(LongPressStartCommand);
}

void OnStateChanged()
{
  _alcoholDetector.Reset();
}
void OnReset()
{
  _alcoholDetector.Reset();
}
void setup()
{
  if (DEBUG)
    Serial.begin(9600);
    
  pinMode(PIN_Button, INPUT_PULLUP);
  _button.attachDoubleClick(&OnButtonDoubleClick);
  _button.attachLongPressStart(&OnButtonLongPressStart);

  _getSensorValueTimer.SetInterval(100);
  _getSensorValueTimer.AttachOnTick(&OnGetSensorValueTimerTick);
  _getSensorValueTimer.Start();

  _alcoholicDetectorStateMachine.AttachOnStateChanged(&OnStateChanged);
  _alcoholicDetectorStateMachine.AttachOnReset(&OnReset);
}

void loop()
{
  _getSensorValueTimer.Tick();
  _button.tick();
}
