#pragma once

#include "Common.h"

#include <list>
using std::list;

#include <vector>
using std::vector;

class PxCommand
{
public:
	string Command;
	vector<string> Arguments;
	void SetArguments(list<string> & args)
	{
		Arguments.clear();
		Arguments.assign(args.begin(), args.end());
	}
};
