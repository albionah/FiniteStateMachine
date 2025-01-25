#pragma once
#include "TransitionFunctionNotFound.h"



TransitionFunctionNotFound::TransitionFunctionNotFound(const char* file, const char* function, unsigned int line, unsigned int transitionCount)
	:InputNotAccepted(file, function, line, THERE_ARE_TERMINALS_ON_THE_INPUT_BUT_NO_APPROPRIATE_TRASITION_FUNCTION_WAS_NOT_FOUND, transitionCount) { };