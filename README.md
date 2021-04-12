# FiniteStateMachine

FiniteStateMachine is a C++ library for deterministic processing input with predefined rules. Read more about it here: https://en.wikipedia.org/wiki/Finite-state_machine

## Usage

Basically a finite state machine has 3 input parameters:
1. initial state
2. transition functions (rules)
3. set of final states

The constructor looks like
```C++
FSM::FiniteStateMachine<ENUM>(ENUM initialState, std::vector<FSM::StateTransitionFunction<ENUM>> stateTransitionFunctions, std::set<ENUM> finalStates);
```
or there is the second constructor
```C++
FSM::FiniteStateMachine<ENUM>(ENUM initialState, std::vector<FSM::StateTransitionFunction<ENUM>> stateTransitionFunctions, std::set<ENUM> finalStates, std::function<void()> userFinalFunction);
```
where `userFinalFunction` is called only when the input is accepted.

The constructor of StateTransitionFunction looks like
```C++
FSM::StateTransitionFunction<ENUM>(const ENUM state, const Symbol& symbol, const ENUM destinationState);
```
or there is the second constructor
```C++
FSM::StateTransitionFunction<ENUM>(const ENUM state, const Symbol& symbol, const ENUM destinationState, std::function<void(const Symbol& symbol)> userFunction);
```
where `userFunction` is called for every transition but only if the input is accepted. 

### Simple example
```C++
#include <iostream>
#include "FiniteStateMachine/FiniteStateMachine.h"

enum State
{
	ONE,
	TWO,
	THREE,
	FOUR
};

bool testSimpleMachine()
{
	FSM::FiniteStateMachine<State> machine(State::ONE,
	{
		FSM::StateTransitionFunction<State>(State::ONE, FSM::Symbol('a'), State::TWO),
		FSM::StateTransitionFunction<State>(State::TWO, FSM::Symbol('b'), State::THREE),
		FSM::StateTransitionFunction<State>(State::THREE, FSM::Symbol('a'), State::FOUR)
	}, { State::FOUR });

	auto result = machine.process({ FSM::Symbol('a'), FSM::Symbol('b'), FSM::Symbol('a') });
	if (!result.isProcessed)
	{
		std::cerr << result.error.message << std::endl;
		return false;
	}
	else return true;
}

```
There are 4 states. Initial state is State ONE. There is only one final state - that is State FOUR. This finite state machine accepts only one input: "aba", nothing more.

## License
[GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/)