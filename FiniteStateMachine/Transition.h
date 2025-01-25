#pragma once
#include <functional>
#include <vector>

#include "Terminal.h"



struct Transition
{
	Transition(std::function<void(Terminal& t)>& function, Terminal* terminal)
	{
		this->function = function;
		this->terminal = terminal;
	}

	std::function<void(Terminal& t)> function;
	Terminal* terminal;
};