#include "Game_LevelState_Paused.h"

#include "Game_Util.h"
#include "Game_UI.h"
#include "Game_LevelState_Ingame.h"

BSS()
	unbound StateObj Paused_State;

	bool Paused_DoneOnce;

//Paused

	uInt PauseUI_Index = 0;

	enum
	{
		EUI_Resume = 0,
		EUI_QuitToMenu = 1
	};

	
	//Pause Title
	UI_TextObject Paused_Title;

	//Resume Button
	UI_ButtonObject Resume_Button;

	//Quit To MM Button
	UI_ButtonObject QuitToMenu_Button;

//Functions

//Class Public

fn returns(void) LevelState_Paused_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"Pause: On Key Up");

			if (PauseUI_Index == 1)
			{
				PauseUI_Index--;

				Renderer_WriteToLog(L"Pause UI: Resume Active");
				
				//Resume = White
				SetColorToTextCells(getAddress(Resume_Button), EUI_TEXT_WHITE_FG);
				//Quit To MM = Grey
				SetColorToTextCells(getAddress(QuitToMenu_Button), EUI_TEXT_GREY_FG);
			}

			break;
		}
	}
}

fn returns(void) LevelState_Paused_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"Pause: On Key Down");

			if (PauseUI_Index == 0)
			{
				PauseUI_Index++;

				Renderer_WriteToLog(L"Pause UI Quit to Menu Active");

				//Resume = Grey
				SetColorToTextCells(getAddress(Resume_Button), EUI_TEXT_GREY_FG);
				//Quit To MM = White
				SetColorToTextCells(getAddress(QuitToMenu_Button), EUI_TEXT_WHITE_FG);

			}

			break;
		}
	}
}

fn returns(void) LevelState_Paused_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
				switch (PauseUI_Index)
				{
					case EUI_Resume:
					{
						LevelState_SetSubstate(GetIngameState());
						break;
					}
					case EUI_QuitToMenu:
					{
						State_SetState(LoadGame());
						break;
					}
				}
			break;
		}
	}
}

fn returns(void) Load_Paused parameters(void)
{
	PauseUI_Index = 0;


	Populate_GridCells_Properties(EUI_PausedMenu);
	//Pause Title Setup

	Paused_Title.Text = L"Paused";
	Populate_UI_Text_Properties(getAddress(Paused_Title));

	Resume_Button.Text = L"Resume";
	Populate_UI_Button_Properties(getAddress(Resume_Button), EUI_PausedMenu, 2);

	QuitToMenu_Button.Text = L"Quit To Menu";
	Populate_UI_Text_Properties(getAddress(QuitToMenu_Button));

	SetColorToTextCells(getAddress(Paused_Title), EUI_TEXT_WHITE_FG);

	SetColorToButtonCells(getAddress(Resume_Button), EUI_TEXT_WHITE_FG);

	SetColorToTextCells(getAddress(QuitToMenu_Button), EUI_TEXT_GREY_FG);

	Input_SubscribeTo(Key_Enter, getAddress(LevelState_Paused_OnKeyEnter));
	Input_SubscribeTo(Key_Arrow_Up, getAddress(LevelState_Paused_OnKeyArrowUp));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(LevelState_Paused_OnKeyArrowDown));
}

fn returns(void) Unload_Paused parameters(void)
{
	Input_Unsubscribe(Key_Enter, getAddress(LevelState_Paused_OnKeyEnter));
	Input_Unsubscribe(Key_Arrow_Up, getAddress(LevelState_Paused_OnKeyArrowUp));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(LevelState_Paused_OnKeyArrowDown));
}

fn returns(void) Update_Paused parameters(void)
{

}

fn returns(void) Render_Paused parameters(void)
{
	//UI_RenderPausedMenu();

	RenderTextCells(getAddress(Paused_Title), -1, 9);

	RenderToGridCell(getAddress(Resume_Button));

	RenderTextCells(getAddress(QuitToMenu_Button), -1, 17);
}

fn returns(Ptr(StateObj)) GetPausedState parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		Paused_State.Load   = getAddress(Load_Paused);
		Paused_State.Unload = getAddress(Unload_Paused);
		Paused_State.Update = getAddress(Update_Paused);
		Paused_State.Render = getAddress(Render_Paused);

		stateConstructed = true;
	}

	return getAddress(Paused_State);
}

