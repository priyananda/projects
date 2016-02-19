#pragma once
#include "PxCommandList.h"

#include <map>
using std::map;
#include <vector>
using std::vector;

class PxShaderData
{
public:
	string Name;
	std::unique_ptr<PxCommandList> Commands;
	vector< std::unique_ptr<PxCommandList> > Stages;

	PxShaderData( cstrref name = "" ) :
		Name(name)
	{
	}

	PxShaderData(const PxShaderData&) = delete;

	PxShaderData(PxShaderData&& other) :
		Name(std::move(other.Name)),
		Commands(std::move(other.Commands)),
		Stages(std::move(other.Stages))
	{
	}

	void AddCommand(UP<PxCommand>&& spCmd)
	{
		if (!this->Commands)
			this->Commands = std::move(std::make_unique<PxCommandList>());
		this->Commands->Commands.emplace_back(std::move(spCmd));
	}

	void AddCommandToStage(UP<PxCommand>&& spCmd)
	{
		if (!this->Stages.empty())
			this->Stages.back()->Commands.emplace_back(std::move(spCmd));
	}
};

class PxShaderParser
{
	map<string, std::unique_ptr<PxShaderData>> m_shaders;
	FILE * m_file;

	string _GetNextToken(bool ignoreNewline);
	bool _IgnoreWhiteSpace(bool ignorenl);
	void _ReadShaders();
public:
	void Parse( cstrref filename );
	typedef map<string,PxShaderData>::iterator Iterator;
    const PxShaderData & operator [] ( cstrref name );
	auto begin(){ return m_shaders.begin(); }
	auto end(){ return m_shaders.end(); }
};

#define FOR_EACH_SHADER(item, shaders)	\
	for( auto& item : shaders )
