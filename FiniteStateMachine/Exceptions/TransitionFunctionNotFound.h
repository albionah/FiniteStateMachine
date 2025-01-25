#pragma once
#include "InputNotAccepted.h"



class TransitionFunctionNotFound : public InputNotAccepted
{
public:
	TransitionFunctionNotFound(const char* file, const char* function, unsigned int line, unsigned int transitionCount);
};