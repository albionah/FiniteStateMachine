#include "InputNotAccepted.h"

#include "../Language.h"


InputNotAccepted::InputNotAccepted(const char* file, const char* function, unsigned int line, const char* message, unsigned int transitionCount)
	: Exception(file, function, line, NO_TRANSITION_FUNCTION_COULD_NOT_BE_FOUND, message), transitionCount(transitionCount) { };