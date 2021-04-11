#pragma once
#include "../Errors/Error.h"


namespace FSM
{
    struct ProcessResult
    {
        bool isProcessed;
        Error error;

    protected:
        ProcessResult(bool isProcessed, Error error): isProcessed(isProcessed), error(error) { }
    };   
}