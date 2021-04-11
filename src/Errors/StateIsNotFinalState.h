#include "Error.h"
#include "../Language.h"


namespace FSM
{
	class StateIsNotFinalState: public Error
	{
	public:
		StateIsNotFinalState(): Error(THE_MACHINE_DID_NOT_FINISH_IN_FINAL_STATE) { }
	};
}