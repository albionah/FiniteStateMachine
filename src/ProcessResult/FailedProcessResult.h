#include "ProcessResult.h"


namespace FSM
{
    class FailedProcessResult: public ProcessResult
    {
    public:
        FailedProcessResult(Error error): ProcessResult(false, error) { }
    };
}