#pragma once


namespace FSM
{
	class Error
	{
	public:
		const char* message;

	public:
		Error(const char* message);
	};
}