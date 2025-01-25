#pragma once



struct Terminal
{
	Terminal() { }
	Terminal(int type)
	{
		this->type = type;
	}

	int type;
};