#include "FiniteStateMachine.h"

#include "Errors/InputNotAccepted.h"
#include "Errors/StateIsNotFinalState.h"
#include "Errors/TransitionFunctionNotFound.h"


FiniteStateMachine::FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates)
{
	this->initialState = initialState;
	this->stateTransitionFunctions = stateTransitionFunctions;
	this->finalStates = finalStates;
	this->doneFunction = []() { };
}


FiniteStateMachine::FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> doneFunction)
{
	this->initialState = initialState;
	this->stateTransitionFunctions = stateTransitionFunctions;
	this->finalStates = finalStates;
	this->doneFunction = doneFunction;
}


FiniteStateMachineProcessResult FiniteStateMachine::process(std::vector<Terminal*> terminals)
{
	int state = this->initialState;
	std::vector<Transition> transitions;

	for (Terminal* terminal : terminals)
	{
		auto iterator = std::find_if(this->stateTransitionFunctions.begin(), this->stateTransitionFunctions.end(), [&state, &terminal](const StateTransitionFunction& fn)
			{return (fn.state == state && fn.terminal.type == terminal->type);});
		if (iterator == this->stateTransitionFunctions.end()) return FiniteStateMachineFailedProcessResult(TransitionFunctionNotFound());
		auto stateTransitionFunction = *iterator;
		transitions.push_back(Transition(stateTransitionFunction.fn, terminal));
		state = stateTransitionFunction.destinationState;
	}

	if (!containSetOfFinalStatesLastState(state))
	{
		return FiniteStateMachineFailedProcessResult(StateIsNotFinalState());
	}
	executeTransitionFunctions(transitions);
	this->doneFunction();
	return FiniteStateMachineSuccessfulProcessResult();
}


bool FiniteStateMachine::containSetOfFinalStatesLastState(int state)
{
	auto iterator = std::find(this->finalStates.begin(), this->finalStates.end(), state);

	return (iterator != this->finalStates.end());
}


void FiniteStateMachine::executeTransitionFunctions(std::vector<Transition>& transitions)
{
	for (auto transition : transitions)
	{
		transition.function(*transition.terminal);
	}
}