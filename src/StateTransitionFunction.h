#pragma once
#include <functional>
#include <vector>

#include "Symbol.h"


namespace FSM
{
	struct StateTransitionFunction
	{
	public:
		int state;
		Symbol symbol;
		int destinationState;
		std::function<void(Symbol& symbol)> userFunction;

		StateTransitionFunction(int state, Symbol symbol, int destinationState, std::function<void(Symbol& symbol)> userFunction = [](Symbol& symbol) {})
			: state(state), symbol(symbol), destinationState(destinationState), userFunction(userFunction) { }
	};
}