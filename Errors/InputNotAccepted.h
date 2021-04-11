#include "Error.h"
#include "../Language.h"


class InputNotAccepted: public Error
{
public:
	InputNotAccepted(): Error(NO_TRANSITION_FUNCTION_COULD_NOT_BE_FOUND) { }
};