#pragma once
#include <functional>
#include <vector>

#include "Symbol.h"


namespace FSM
{
	struct BasicStateTransitionFunction
	{
	public:
		int state;
		Symbol symbol;
		int destinationState;
		std::function<void(const Symbol& symbol)> userFunction;

		BasicStateTransitionFunction(const int state, const Symbol& symbol, const int destinationState, std::function<void(const Symbol& symbol)> userFunction = [](const Symbol& symbol) {})
			: state(state), symbol(symbol), destinationState(destinationState), userFunction(userFunction) { }
	};
}