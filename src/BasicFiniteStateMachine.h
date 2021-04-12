#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

#include "Symbol.h"
#include "Transition.h"
#include "StateTransitionFunction.h"
#include "Errors/Error.h"
#include "ProcessResult/ProcessResult.h"


namespace FSM
{
	class BasicFiniteStateMachine
	{
	private:
		int initialState;
		std::set<int> finalStates;
		std::vector<BasicStateTransitionFunction> stateTransitionFunctions;
		std::function<void()> userFinalFunction;

	public:
		BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates);
		BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates, std::function<void()> userFinalFunction);
		virtual ~BasicFiniteStateMachine() { };

		ProcessResult process(std::vector<Symbol> symbols);

	private:
		bool containSetOfFinalStatesLastState(int state);
		void executeTransitionFunctions(std::vector<Transition>& transitions);
	};
}