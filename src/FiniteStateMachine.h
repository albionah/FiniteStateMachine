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
	class FiniteStateMachine
	{
	private:
		int initialState;
		std::set<int> finalStates;
		std::vector<StateTransitionFunction> stateTransitionFunctions;
		std::function<void()> doneFunction;

	public:
		FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates);
		FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> userDoneFunction);
		virtual ~FiniteStateMachine() { };

		ProcessResult process(std::vector<Symbol*> symbols);

	private:
		bool containSetOfFinalStatesLastState(int state);
		void executeTransitionFunctions(std::vector<Transition>& transitions);
	};
}