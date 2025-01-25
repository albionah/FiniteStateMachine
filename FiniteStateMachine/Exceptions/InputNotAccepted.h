#pragma once
#include <Exceptions/Exception.h>
#include "../Language.h"



class InputNotAccepted : public Exception
{
public:
	unsigned int transitionCount;

	InputNotAccepted(const char* file, const char* function, unsigned int line, const char* message, unsigned int transitionCount);
};