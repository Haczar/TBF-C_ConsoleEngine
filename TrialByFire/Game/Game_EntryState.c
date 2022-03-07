// Parent Header
#include "Game_EntryState.h"

//Includes
#include"Game_LevelState.h"
#include"Game_LevelState_Ingame.h"
#include"Game_Util.h"
#include"Game_UI.h"



BSS()

	StateObj MainMenu;

Data()
	bool 
		Log_Load   = true;
		Log_Unload = true;

	bool EntryState_DoneOnce = false;

	// UI

	DataSize UI_Index = 1;

	enum 
	{
		EUI_None  = 0,
		EUI_Start = 1,
		EUI_Quit  = 2
	};

	UI_TextObject ProjectName_Title;
	UI_ButtonObject Start_Button;
	UI_ButtonObject Quit_Button;


// Functions

// Private

// Public Class

fn returns(void) Game_EntryState_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Up");

			if (UI_Index == 2)
			{
				UI_Index--;

				Renderer_WriteToLog(L"UI Start Active");

				SetColorToTextCells(getAddress(Start_Button), EUI_TEXT_WHITE_FG);
				SetColorToTextCells(getAddress(Quit_Button), EUI_TEXT_GREY_FG);
			}

			break;
		}
	}
}

fn returns(void) Game_EntryState_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Down");

			if (UI_Index == 1)
			{
				UI_Index++;

				Renderer_WriteToLog(L"UI Quit Active");

				SetColorToTextCells(getAddress(Quit_Button), EUI_TEXT_WHITE_FG);
				SetColorToTextCells(getAddress(Start_Button), EUI_TEXT_GREY_FG);

			}

			break;
		}
	}
}

fn returns(void) Game_EntryState_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Enter");

			switch (UI_Index)
			{
				case EUI_Start:
				{
					Renderer_WriteToLog(L"UI Start Selected");

					State_SetState(GetLevelState());

					break;
				}
				case EUI_Quit:
				{
					Cycler_Quit();

					break;
				}
			}

			break;
		}
	}
}

fn returns(void) MainMenu_Load parameters(void)
{
	InitializeGridStatesAndCells();

	if (!EntryState_DoneOnce)
	{
		ProjectName_Title.Text = L"Generic Platform Demo";
		Populate_UI_Text_Properties(getAddress(ProjectName_Title));

		Start_Button.Text = L"Start";
		Populate_UI_Text_Properties(getAddress(Start_Button));

		Quit_Button.Text = L"Quit";
		Populate_UI_Text_Properties(getAddress(Quit_Button));

		EntryState_DoneOnce = true;
	}
	
	SetColorToTextCells(getAddress(ProjectName_Title), EUI_TEXT_WHITE_FG);
	SetColorToTextCells(getAddress(Start_Button), EUI_TEXT_WHITE_FG);
	SetColorToTextCells(getAddress(Quit_Button), EUI_TEXT_GREY_FG);

	Input_SubscribeTo(Key_Arrow_Up  , getAddress(Game_EntryState_OnKeyArrowUp  ));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_SubscribeTo(Key_Enter     , getAddress(Game_EntryState_OnKeyEnter    ));

	if (Log_Load)
	{
		Renderer_WriteToLog(L"Loaded: Main Menu");

		Log_Load = false;
	}
}

fn returns(void) MainMenu_Unload parameters(void)
{
	Input_Unsubscribe(Key_Arrow_Up  , getAddress(Game_EntryState_OnKeyArrowUp  ));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_Unsubscribe(Key_Enter     , getAddress(Game_EntryState_OnKeyEnter    ));

	if (Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Main Menu");

		Log_Unload = false;
	}
}

fn returns(void) MainMenu_Update parameters(void)
{
}

fn returns(void) MainMenu_Render parameters(void)
{
	RenderTextCells(getAddress(ProjectName_Title), -1, 9);

	RenderTextCells(getAddress(Start_Button), -1, 15);

	RenderTextCells(getAddress(Quit_Button), -2, 17);
}



// Engine Entrypoint

fn returns(Ptr(StateObj)) LoadGame parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		MainMenu.Load   = getAddress(MainMenu_Load);
		MainMenu.Unload = getAddress(MainMenu_Unload);
		MainMenu.Update = getAddress(MainMenu_Update);
		MainMenu.Render = getAddress(MainMenu_Render);
	}

	stateConstructed = true;
	

	return getAddress(MainMenu);
}



