#pragma once



#include "LAL.h"



// Aliases (Typedefs)

alias(enum ExecFlags_Def) as ExecFlags;



// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};



// Forward Declarations

fn returns(ExecFlags) EntryPoint parameters(void);

