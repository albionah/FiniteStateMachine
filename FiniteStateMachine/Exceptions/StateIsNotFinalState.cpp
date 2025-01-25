#pragma once
#include "StateIsNotFinalState.h"



StateIsNotFinalState::StateIsNotFinalState(const char* file, const char* function, unsigned int line, unsigned int transitionCount)
	: InputNotAccepted(file, function, line, THE_MACHINE_DID_NOT_FINISH_IN_FINAL_STATE, transitionCount) { };
