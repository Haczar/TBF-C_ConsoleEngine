//Parent Header
#include "State.h"
#include "State_Intro.h"
#include "Engine.h"





//State

//Functions
//Public

Data()
	Ptr(StateObj) CurrentState = NULL;

fn returns(void) State_LoadModule parameters(void)
{

	CurrentState = GetIntroState();

	CurrentState->Load();
}

fn returns(void) State_SetState parameters(Ptr(StateObj) _state)
{
	if (CurrentState != NULL)
	{
		CurrentState->Unload();
	}

	CurrentState = _state;

	CurrentState->Load();
}

fn returns(void) State_Update parameters(void)
{
	if (CurrentState != NULL)
	{
		CurrentState->Update();
	}
}

fn returns(void) State_Render parameters(void)
{
	if (CurrentState != NULL)
	{
		CurrentState->Render();
	}
}

fn returns(void) State_LoadGame parameters(void)
{
	State_SetState(LoadGame());

}







