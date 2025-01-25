#pragma once
#include "InputNotAccepted.h"



class StateIsNotFinalState : public InputNotAccepted
{
public:
	StateIsNotFinalState(const char* file, const char* function, unsigned int line, unsigned int transitionCount);
};