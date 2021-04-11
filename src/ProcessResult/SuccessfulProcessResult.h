#include "ProcessResult.h"
#include "../Language.h"


namespace FSM
{
    struct SuccessfulProcessResult: public ProcessResult
    {
    public:
        SuccessfulProcessResult(): ProcessResult(true, Error(NO_ERROR)) { }
    };
}