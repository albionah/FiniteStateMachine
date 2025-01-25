#pragma once
#include <functional>
#include <vector>

#include "Terminal.h"



struct StateTransitionFunction
{
	StateTransitionFunction(int state, Terminal t, int destinationState, std::function<void(Terminal& terminal)> fn = [](Terminal& terminal) {})
	{
		this->state = state;
		this->terminal = t;
		this->destinationState = destinationState;
		this->fn = fn;
	}

	int state;
	Terminal terminal;
	int destinationState;
	std::function<void(Terminal& t)> fn;
};