#include "FiniteStateMachine.h"

#include "Errors/InputNotAccepted.h"
#include "Errors/StateIsNotFinalState.h"
#include "Errors/TransitionFunctionNotFound.h"
#include "ProcessResult/SuccessfulProcessResult.h"
#include "ProcessResult/FailedProcessResult.h"


namespace FSM
{
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


	ProcessResult FiniteStateMachine::process(std::vector<Symbol*> symbols)
	{
		int state = this->initialState;
		std::vector<Transition> transitions;

		for (Symbol* symbol : symbols)
		{
			auto iterator = std::find_if(this->stateTransitionFunctions.begin(), this->stateTransitionFunctions.end(), [&state, &symbol](const StateTransitionFunction& fn)
				{return (fn.state == state && fn.symbol.type == symbol->type);});
			if (iterator == this->stateTransitionFunctions.end()) return FailedProcessResult(TransitionFunctionNotFound());
			auto stateTransitionFunction = *iterator;
			transitions.push_back(Transition(stateTransitionFunction.userFunction, symbol));
			state = stateTransitionFunction.destinationState;
		}

		if (!containSetOfFinalStatesLastState(state))
		{
			return FailedProcessResult(StateIsNotFinalState());
		}
		executeTransitionFunctions(transitions);
		this->doneFunction();
		return SuccessfulProcessResult();
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
			transition.function(*transition.symbol);
		}
	}
}