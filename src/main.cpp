#include <Arduino.h>

#include "Timer/Timer.h"
#include "AlcoholDetector/AlcoholDetector.h"
#include "AlcoholicDetectorStateMachine/AlcoholicDetectorStateMachine.h"
#include "AlcoholicDetectorLcd/AlcoholicDetectorLcd.h"
#include "settings.h"
#include "OneButton.h"

Timer _getSensorValueTimer;
AlcoholDetector _alcoholDetector(PIN_AlcoholDetector);
OneButton _button(PIN_Button, true, true);
AlcoholicDetectorStateMachine _alcoholicDetectorStateMachine;
AlcoholicDetectorLcd _lcd;

void OnStateChanged()
{
  _alcoholDetector.Reset();
}
void OnReset()
{
  _alcoholDetector.Reset();
}
void OnValuesStringChanged()
{
  auto string = _alcoholDetector.GetValuesString();
  auto constrainedString = _lcd.ConstrainInputedText(string);
  _lcd.PrintOnRow(0, constrainedString);

  Serial.println(string);
}
void OnResolutionStringChanged()
{
  auto string = _alcoholDetector.GetResolutionString();
  _lcd.PrintOnRow(1, string);

  Serial.println(string);
}
void setup()
{
  if (DEBUG)
    Serial.begin(9600);

  pinMode(PIN_Button, INPUT_PULLUP);
  _button.attachDoubleClick([]() { _alcoholicDetectorStateMachine.Run(DoubleClickCommand); });
  _button.attachLongPressStart([]() { _alcoholicDetectorStateMachine.Run(LongPressStartCommand); });

  _getSensorValueTimer.SetInterval(100);
  _getSensorValueTimer.AttachOnTick([]() { _alcoholDetector.Tick(); });
  _getSensorValueTimer.Start();

  _alcoholicDetectorStateMachine.AttachOnStateChanged(&OnStateChanged);
  _alcoholicDetectorStateMachine.AttachOnReset(&OnReset);

  _lcd.Init();

  _alcoholDetector.AttachOnValuesStringChanged(&OnValuesStringChanged);
  _alcoholDetector.AttachOnResolutionStringChanged(&OnResolutionStringChanged);
}

void loop()
{
  _getSensorValueTimer.Tick();
  _button.tick();
}
