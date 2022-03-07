// Includes

#include "C_STL.h"
#include "LAL.h"
#include "CString.h"
#include "Cycler.h"
#include "Input.h"
#include "Memory.h"
#include "Renderer.h"
#include "State.h"



// Aliases (Typedefs)

alias(enum ExecFlags_Def) as ExecFlags;

alias(char) as CString_13[13];

// Enumerators

enum ExecFlags_Def
{
	ExecFlags_Sucess = 0,
};

//Functions
fn returns(void) PrepareModules parameters(void)
{
	Cycler_LoadModule  ();
	CString_LoadModule ();
	Timing_LoadModule  ();
	Input_LoadModule();
	Renderer_LoadModule();
	State_LoadModule();
	
}

fn returns(void) PrintStartMessage parameters(void)
{
	Stack()
		CTS_CWString EntryMessage = L"TBF C Engine Version: Phase 5\n";

	// Setup the values of the message string. 
	//Print(EntryMessage);

	Renderer_WriteToLog(L"TBF C Engine: ");
	Renderer_WriteToLog(L"");
	Renderer_WriteToLog(L"Version: Phase 5");
}

fn returns(void) UnloadModules parameters(void)
{
	Renderer_UnloadModule();
}
// Entry Point

fn returns(ExecFlags) EntryPoint parameters(void)
{

	// Setup engine components.

	PrepareModules();

	PrintStartMessage();	

	// Core Engine Loop

	Cycler_Initialize();
	
	// Exit Engine

	printf("Exiting Game Engine: Press enter key to continue.");

	getchar();

	UnloadModules();

	GlobalDeallocate();

	return ExecFlags_Sucess;
}
