#pragma once


namespace FSM
{
	struct Symbol
	{
	public:
		int type;

		Symbol() { }
		Symbol(int type): type(type) { }
	};
}