#ifndef alcoholicDetectorStateMachineH
#define alcoholicDetectorStateMachineH

#include "enums.h"

extern "C"
{
    typedef void (*alcoholicDetectorStateMachineCallback)(void);
}

class AlcoholicDetectorStateMachine
{
private:
    State _state = Normal;
    alcoholicDetectorStateMachineCallback _stateChangedCallback;
    alcoholicDetectorStateMachineCallback _resetCallback;

    void HandleDoubleClick();
    void SetState(State newState);
    State GetNextState();
    public:
        void Run(Command command);
        State GetState();
        void AttachOnStateChanged(alcoholicDetectorStateMachineCallback callback);
        void AttachOnReset(alcoholicDetectorStateMachineCallback callback);
    };

#endif //alcoholicDetectorStateMachineH
