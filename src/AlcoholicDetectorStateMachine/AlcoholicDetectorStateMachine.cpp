#include "AlcoholicDetectorStateMachine.h"

void AlcoholicDetectorStateMachine::Run(Command command)
{
    switch (command)
    {
    case DoubleClickCommand:
        HandleDoubleClick();
        break;
    case LongPressStartCommand:
        SetState(GetNextState());
        break;
    default:
        break;
    }
}
void AlcoholicDetectorStateMachine::HandleDoubleClick()
{
    if (_state != Normal || !_resetCallback)
        return;
    _resetCallback();
}

State AlcoholicDetectorStateMachine::GetNextState()
{
    switch (_state)
    {
    case Normal:
        return Calibration;
    case Calibration:
        return Normal;
    }
}
void AlcoholicDetectorStateMachine::SetState(State newState)
{
    if (_state == newState)
        return;
    _state = newState;

    if (_stateChangedCallback)
        _stateChangedCallback();
}

State AlcoholicDetectorStateMachine::GetState()
{
    return _state;
}
void AlcoholicDetectorStateMachine::AttachOnStateChanged(alcoholicDetectorStateMachineCallback callback)
{
    _stateChangedCallback = callback;
}
void AlcoholicDetectorStateMachine::AttachOnReset(alcoholicDetectorStateMachineCallback callback)
{
    _resetCallback = callback;
}
