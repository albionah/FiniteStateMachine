#pragma once
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

#include "Terminal.h"
#include "Transition.h"
#include "StateTransitionFunction.h"
#include "Exceptions/TransitionFunctionNotFound.h"
#include "Exceptions/StateIsNotFinalState.h"

using namespace std;



class FiniteStateMachine
{
private:
	int initialState;
	unsigned int transitionCount;
	std::set<int> finalStates;
	std::vector<StateTransitionFunction> stateTransitionFunctions;
	std::function<void()> doneFunction;

public:
	FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates);
	FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> doneFunction);
	virtual ~FiniteStateMachine() { };

	void process(std::vector<Terminal*> terminals);

private:
	StateTransitionFunction& findStateTransitionFunction(int state, Terminal& t);
	void checkFinalStates(int state);
	void executeTransitionFunctions(std::vector<Transition>& transitions);
};

