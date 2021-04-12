#pragma once
#include <type_traits>

#include "BasicStateTransitionFunction.h"


namespace FSM
{
    template<typename STATE, typename = std::enable_if<std::is_enum<STATE>::value>>
	struct StateTransitionFunction: public BasicStateTransitionFunction
	{
    public:
		StateTransitionFunction(const STATE state, const Symbol& symbol, const STATE destinationState, std::function<void(const Symbol& symbol)> userFunction = [](const Symbol& symbol) {})
			: BasicStateTransitionFunction(state, symbol, destinationState, userFunction) { }
	};
}