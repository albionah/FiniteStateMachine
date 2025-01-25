#include "BasicFiniteStateMachine.h"

#include "Exceptions/InputNotAccepted.h"
#include "Exceptions/StateIsNotFinalState.h"
#include "Exceptions/TransitionFunctionNotFound.h"


namespace FSM
{
	BasicFiniteStateMachine::BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates)
		: transitionCount(0)
		, initialState(initialState)
		, stateTransitionFunctions(stateTransitionFunctions)
		, finalStates(finalStates)
	{
		this->userFinalFunction = []() { };
	}


	BasicFiniteStateMachine::BasicFiniteStateMachine(const int initialState, const std::vector<BasicStateTransitionFunction>& stateTransitionFunctions, const std::set<int>& finalStates, std::function<void()> userFinalFunction)
		: BasicFiniteStateMachine(initialState, stateTransitionFunctions, finalStates)
	{
		this->userFinalFunction = userFinalFunction;
	}


	void BasicFiniteStateMachine::process(std::vector<Symbol> symbols)
	{
		int state = this->initialState;
		std::vector<Transition> transitions;

		for (const Symbol& symbol : symbols)
		{
			auto iterator = std::find_if(this->stateTransitionFunctions.begin(), this->stateTransitionFunctions.end(), [&state, &symbol](const BasicStateTransitionFunction& fn)
				{return (fn.state == state && fn.symbol.type == symbol.type);});
			if (iterator == this->stateTransitionFunctions.end())
			{
				throw TransitionFunctionNotFound(__FILE__, __func__, __LINE__, this->transitionCount);
			}
			auto stateTransitionFunction = *iterator;
			transitions.push_back(Transition(stateTransitionFunction.userFunction, symbol));
			state = stateTransitionFunction.destinationState;
		}

		if (!containSetOfFinalStatesLastState(state))
		{
			throw StateIsNotFinalState(__FILE__, __func__, __LINE__, this->transitionCount);
		}
		executeTransitionFunctions(transitions);
		this->userFinalFunction();
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