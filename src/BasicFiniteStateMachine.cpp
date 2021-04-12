#include "BasicFiniteStateMachine.h"

#include "Errors/InputNotAccepted.h"
#include "Errors/StateIsNotFinalState.h"
#include "Errors/TransitionFunctionNotFound.h"
#include "ProcessResult/SuccessfulProcessResult.h"
#include "ProcessResult/FailedProcessResult.h"


namespace FSM
{
	BasicFiniteStateMachine::BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates)
	{
		this->initialState = initialState;
		this->stateTransitionFunctions = stateTransitionFunctions;
		this->finalStates = finalStates;
		this->userFinalFunction = []() { };
	}


	BasicFiniteStateMachine::BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates, std::function<void()> userFinalFunction)
		: BasicFiniteStateMachine(initialState, stateTransitionFunctions, finalStates)
	{
		this->userFinalFunction = userFinalFunction;
	}


	ProcessResult BasicFiniteStateMachine::process(std::vector<Symbol> symbols)
	{
		int state = this->initialState;
		std::vector<Transition> transitions;

		for (const Symbol& symbol : symbols)
		{
			auto iterator = std::find_if(this->stateTransitionFunctions.begin(), this->stateTransitionFunctions.end(), [&state, &symbol](const BasicStateTransitionFunction& fn)
				{return (fn.state == state && fn.symbol.type == symbol.type);});
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
		this->userFinalFunction();
		return SuccessfulProcessResult();
	}


	bool BasicFiniteStateMachine::containSetOfFinalStatesLastState(int state)
	{
		auto iterator = std::find(this->finalStates.begin(), this->finalStates.end(), state);

		return (iterator != this->finalStates.end());
	}


	void BasicFiniteStateMachine::executeTransitionFunctions(std::vector<Transition>& transitions)
	{
		for (const Transition& transition : transitions)
		{
			transition.function(transition.symbol);
		}
	}
}