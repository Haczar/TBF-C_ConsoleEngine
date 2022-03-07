#pragma once

#include "LAL.h"

//Alias(typedefs)

alias(enum ExecFlags_Def) as ExecFlags;

//Enumerators
enum ExecFlags_Def
{
	ExecFlags_Success = 0,
};

//Forward Declarations

fn returns(ExecFlags) EntryPoint parameters(void);