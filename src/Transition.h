#pragma once
#include <functional>
#include <vector>

#include "Symbol.h"


namespace FSM
{
	struct Transition
	{
	public:
		Symbol* symbol;
		std::function<void(Symbol& symbol)> function;

		Transition(std::function<void(Symbol& symbol)>& function, Symbol* symbol)
			: function(function), symbol(symbol) { }
	};
}