# FiniteStateMachine

FiniteStateMachine is a C++ library for processing input with predefined rules. Read more about it here: https://en.wikipedia.org/wiki/Finite-state_machine

## Usage

Basically a finite state machine has 3 input parameters:
1. initial state
2. transition functions (rules)
3. set of final states

The constructor looks like
```C++
FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates);
```
or there is the second constructor
```C++
FiniteStateMachine(int initialState, std::vector<StateTransitionFunction> stateTransitionFunctions, std::set<int> finalStates, std::function<void()> doneFunction);
```
where `doneFunction` is called when the input is accepted.

### Simple example
```C++
#include <iostream>
#include "FiniteStateMachine/FiniteStateMachine.h"

bool testSimpleMachine()
{
	FiniteStateMachine machine(0,
	{
		StateTransitionFunction(0, Terminal('a'), 1, [](Terminal& t) { }),
		StateTransitionFunction(1, Terminal('b'), 2, [](Terminal& t) { }),
		StateTransitionFunction(2, Terminal('a'), 3, [](Terminal& t) { })
	}, { 3 });

	try
	{
		machine.process({ &Terminal('a'), &Terminal('b'), &Terminal('a') });
	}
	catch (InputNotAccepted& error)
	{
		std::cerr << error.message << std::endl;
		return false;
	}

	return true;
}

```
There are 4 states. Initial state is State 0. There is only one final state - that is State 3. This finite state machine accepts only one input: "aba", nothing more.
