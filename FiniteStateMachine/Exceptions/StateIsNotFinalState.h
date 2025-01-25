#pragma once
#include "InputNotAccepted.h"
#include "../Language.h"



class StateIsNotFinalState : public InputNotAccepted
{
public:
	StateIsNotFinalState(const char* file, const char* function, unsigned int line, unsigned int transitionCount);
};