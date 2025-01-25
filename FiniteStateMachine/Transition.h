#pragma once
#include <functional>
#include <vector>

#include "Symbol.h"


namespace FSM
{
	struct Transition
	{
	public:
		const Symbol& symbol;
		std::function<void(const Symbol& symbol)> function;

		Transition(std::function<void(const Symbol& symbol)>& function, const Symbol& symbol)
			: function(function), symbol(symbol) { }
	};
}
