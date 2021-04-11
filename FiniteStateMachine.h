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
#include "Errors/Error.h"


struct FiniteStateMachineProcessResult
{
	bool isProcessed;
	Error error;

protected:
	FiniteStateMachineProcessResult(bool isProcessed, Error error): isProcessed(isProcessed), error(error) { }
};

struct FiniteStateMachineSuccessfulProcessResult: public FiniteStateMachineProcessResult
{
public:
	FiniteStateMachineSuccessfulProcessResult(): FiniteStateMachineProcessResult(true, Error("No error")) { }
};

class FiniteStateMachineFailedProcessResult: public FiniteStateMachineProcessResult
{
public:
	FiniteStateMachineFailedProcessResult(Error error): FiniteStateMachineProcessResult(false, error) { }
};

class FiniteStateMachine
{
private:
	int initialState;
	std::set<int> finalStates;
	std::vector<StateTransitionFunction> stateTransitionFunctions;
	std::function<void()> doneFunction;

public:
	FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates);
	FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> doneFunction);
	virtual ~FiniteStateMachine() { };

	FiniteStateMachineProcessResult process(std::vector<Terminal*> terminals);

private:
	bool containSetOfFinalStatesLastState(int state);
	void executeTransitionFunctions(std::vector<Transition>& transitions);
};