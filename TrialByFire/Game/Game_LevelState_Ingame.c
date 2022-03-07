//Parent Header
#include "Game_LevelState_Ingame.h"

#include "Game_Util.h"
#include "Game_UI.h"
#include "Game_LevelState_Paused.h"

BSS()
	StateObj Ingame_State;

	StateObj LevelState;

	//In-Game Title
	UI_TextObject InGame_Title;

	bool Ingame_DoneOnce = false;

//Functions

//Class Public

fn returns(void) LevelState_Ingame_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"EntryState: On Key Enter");

			LevelState_SetSubstate(GetPausedState());
			break;
		}
	}
}

fn returns(void) Load_Ingame parameters(void)
{
	if (!Ingame_DoneOnce)
	{
		InGame_Title.Text = L"In-game";

		Populate_UI_Text_Properties(getAddress(InGame_Title));

		Ingame_DoneOnce = true;
	}

	SetColorToTextCells(getAddress(InGame_Title), EUI_TEXT_WHITE_FG);

	Input_SubscribeTo(Key_Enter, LevelState_Ingame_OnKeyEnter);
}

fn returns(void) Unload_Ingame parameters(void)
{
	Input_Unsubscribe(Key_Enter, LevelState_Ingame_OnKeyEnter);
}

fn returns(void) Update_Ingame parameters(void)
{

}

fn returns(void) Render_Ingame parameters(void)
{
	RenderTextCells(getAddress(InGame_Title), 0, 9);
}

fn returns(Ptr(StateObj)) GetIngameState parameters(void)
{
	unbound bool stateConstructed = false;

	if (!stateConstructed)
	{
		Ingame_State.Load = getAddress(Load_Ingame);
		Ingame_State.Unload = getAddress(Unload_Ingame);
		Ingame_State.Update = getAddress(Update_Ingame);
		Ingame_State.Render = getAddress(Render_Ingame);

		stateConstructed = true;
	}

	return getAddress(Ingame_State);

}