#include <type_traits>

#include "BasicFiniteStateMachine.h"
#include "StateTransitionFunction.h"


namespace FSM
{
    template<typename STATE, typename = std::enable_if<std::is_enum<STATE>::value>>
    class FiniteStateMachine: public BasicFiniteStateMachine
    {
    public:
        FiniteStateMachine(const STATE initialState, const std::vector<StateTransitionFunction<STATE>>& stateTransitionFunctions, const std::set<STATE>& finalStates)
            : BasicFiniteStateMachine((const int) initialState, (const std::vector<BasicStateTransitionFunction>&) stateTransitionFunctions, (const std::set<int>&) finalStates) { }
		FiniteStateMachine(const STATE initialState, const std::vector<StateTransitionFunction<STATE>>& stateTransitionFunctions, const std::set<STATE>& finalStates, std::function<void()> userFinalFunction)
            : BasicFiniteStateMachine((const int) initialState, (const std::vector<BasicStateTransitionFunction>&) stateTransitionFunctions, (const std::set<int>&) finalStates, userFinalFunction) { }
		virtual ~FiniteStateMachine() { };
    };
}