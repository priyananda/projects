#pragma once
#include "PxCommand.h"

#include <list>
using std::list;
#include <memory>
#include <functional>

class PxCommandList
{
public:
	string Type;
	list<std::unique_ptr<PxCommand>> Commands;

	PxCommandList()
	{
	}

	PxCommandList(const PxCommandList& other) = delete;

	PxCommandList(PxCommandList&& other) :
		Commands(std::move(other.Commands))
	{
	}

	typedef std::function<void (PxCommand*)> HandlerFn;
	void ForEach(const HandlerFn& func)
	{
		for (auto& spCmd : Commands)
			func(spCmd.get());
	}

	auto begin() { return Commands.begin(); }
	auto end() { return Commands.end(); }
};
