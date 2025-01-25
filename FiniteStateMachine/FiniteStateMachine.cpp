#include "FiniteStateMachine.h"



FiniteStateMachine::FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates)
{
	this->transitionCount = 0;
	this->initialState = initialState;
	this->stateTransitionFunctions = stateTransitionFunctions;
	this->finalStates = finalStates;
	this->doneFunction = []() { };
}



FiniteStateMachine::FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> doneFunction)
{
	this->transitionCount = 0;
	this->initialState = initialState;
	this->stateTransitionFunctions = stateTransitionFunctions;
	this->finalStates = finalStates;
	this->doneFunction = doneFunction;
}



void FiniteStateMachine::process(std::vector<Terminal*> terminals)
{
	int state = this->initialState;
	std::vector<Transition> transitions;

	for (Terminal* terminal : terminals)
	{
		StateTransitionFunction& stateTransitionFunction = findStateTransitionFunction(state, *terminal);
		transitions.push_back(Transition(stateTransitionFunction.fn, terminal));
		state = stateTransitionFunction.destinationState;
		this->transitionCount++;
	}

	checkFinalStates(state);
	executeTransitionFunctions(transitions);
	this->doneFunction();
}



StateTransitionFunction& FiniteStateMachine::findStateTransitionFunction(int state, Terminal& terminal)
{
	for (StateTransitionFunction& stateTransitionFunction : this->stateTransitionFunctions)
	{
		if (stateTransitionFunction.state == state && stateTransitionFunction.terminal.type == terminal.type)
		{
			return stateTransitionFunction;
		}
	}

	throw TransitionFunctionNotFound(__FILE__, __func__, __LINE__, this->transitionCount);
}



void FiniteStateMachine::checkFinalStates(int state)
{
	auto iterator = std::find(this->finalStates.begin(), this->finalStates.end(), state);

	if (iterator == this->finalStates.end())
	{
		throw StateIsNotFinalState(__FILE__, __func__, __LINE__, this->transitionCount);
	}
}



void FiniteStateMachine::executeTransitionFunctions(std::vector<Transition>& transitions)
{
	for (auto transition : transitions)
	{
		transition.function(*transition.terminal);
	}
}