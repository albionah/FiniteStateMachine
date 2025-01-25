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


namespace FSM
{
	class BasicFiniteStateMachine
	{
	private:
		int initialState;
		unsigned int transitionCount;
		std::set<int> finalStates;
		std::vector<BasicStateTransitionFunction> stateTransitionFunctions;
		std::function<void()> userFinalFunction;

	public:
		BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates);
		BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates, std::function<void()> userFinalFunction);
		virtual ~BasicFiniteStateMachine() { };

		void process(std::vector<Symbol> symbols);

	private:
		bool containSetOfFinalStatesLastState(int state);
		void executeTransitionFunctions(std::vector<Transition>& transitions);
	};
}