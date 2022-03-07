// Parent Header
#include "Game_LevelState.h"
#include "Game_LevelMenuSubState.h"


BSS()

Ptr(StateObj) CurrentSubState = NULL;

StateObj Level;


Data()
bool
Level_Log_Load = true;
Level_Log_Unload = true;
showLevel = true;
showLevelMenu = false;

//Title
CTS_CWString Level_Text = L"You Are Now In-Game";
DataSize Level_Text_Length = 0;
Ptr(Cell) Level_RenderCells = NULL;

//foward declare
fn returns(void) SubState_SetState parameters(Ptr(StateObj) _subState);

//Functions
//Private
fn returns(void)Game_LevelState_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"Level State: On Key Enter");

			showLevel = false;
			showLevelMenu = true;
			
			SubState_SetState(LoadLevelMenu());

			break;
		}
	}
}

fn returns(void) Level_Load parameters(void)
{
	//Populate Level Text Cells
	Level_Text_Length = wcslen(Level_Text) + 1;
	Level_RenderCells = GlobalAllocate(Cell, Level_Text_Length);

	for (DataSize cellIndex = 0; cellIndex < Level_Text_Length; cellIndex++)
	{
		Level_RenderCells[cellIndex].Char.UnicodeChar = Level_Text[cellIndex];
	}

	ChangeCellsTo_White(Level_RenderCells, Level_Text_Length);

	//Subscribe to only enter input events
	Input_SubscribeTo(Key_Enter, getAddress(Game_LevelState_OnKeyEnter));
	

	//Log
	if (Level_Log_Load)
	{
		Renderer_WriteToLog(L"Load: Level");

		Level_Log_Load = false;
	}
}

fn returns(void) Level_Unload parameters(void)
{
	if (Level_Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Level");
		Input_Unsubscribe(Key_Enter, getAddress(Game_LevelState_OnKeyEnter));

		Level_Log_Unload = false;
	}
}

fn returns(void) Level_Update parameters(void)
{
	if(CurrentSubState != NULL)
	{
		CurrentSubState->Update();
	}

}

fn returns(void) Level_Render parameters(void)
{
	//Render Level_Text

	if (showLevel)
	{
		Stack()
			unbound COORD
			startingCell = { 0, 15 },
			endingCell = { 0, 15 };
		//Level Text Cells
		startingCell.X = (ERenderer_Width / 2) - (Level_Text_Length / 2) - 1;
		endingCell.X = (ERenderer_Width / 2) + (Level_Text_Length / 2) - 1;

		startingCell.Y = 9;
		endingCell.Y = 9;

		Renderer_WriteToBufferCells(Level_RenderCells, startingCell, endingCell);
	}
	
	if (showLevelMenu)
	{
		if (CurrentSubState != NULL)
		{
			CurrentSubState->Render();
		}

		Input_Unsubscribe(Key_Enter, getAddress(Game_LevelState_OnKeyEnter));

	}

	

}


// Engine Entrypoint

fn returns(Ptr(StateObj)) LoadLevel parameters(void)
{
	Level.Load   = getAddress(Level_Load);
	Level.Unload = getAddress(Level_Unload);
	Level.Update = getAddress(Level_Update);
	Level.Render = getAddress(Level_Render);

	return getAddress(Level);
}

fn returns(void) SubState_SetState parameters(Ptr(StateObj) _subState)
{
	CurrentSubState = _subState;

	CurrentSubState->Load();

	Renderer_WriteToLog(L" LevelState: SubState Loaded");

}


fn returns(void) SubState_UnloadState parameters(void)
{
	CurrentSubState->Unload();

	CurrentSubState = NULL;

	showLevel     = true;
	showLevelMenu = false;

	Input_SubscribeTo(Key_Enter, getAddress(Game_LevelState_OnKeyEnter));


	Renderer_WriteToLog(L" LevelState: SubState Unloaded");

}

