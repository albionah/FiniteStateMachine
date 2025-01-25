#include "Error.h"
#include "../Language.h"


namespace FSM
{
	class TransitionFunctionNotFound: public Error
	{
	public:
		TransitionFunctionNotFound(): Error(THERE_ARE_TERMINALS_ON_THE_INPUT_BUT_NO_APPROPRIATE_TRASITION_FUNCTION_WAS_NOT_FOUND) { }
	};
}