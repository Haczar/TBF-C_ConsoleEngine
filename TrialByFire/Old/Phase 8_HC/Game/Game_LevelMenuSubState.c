// Parent Header
#include "Game_LevelMenuSubState.h"
#include "Game_EntryState.h"



BSS()
StateObj LevelMenu;


Data()
bool
LevelMenu_Log_Load = true;
LevelMenu_Log_Unload = true;
canUseUI = false;

//UI

DataSize LevelMenu_UI_Index = 1;

enum
{
	EUI_Resume = 1,
	EUI_QuitToMM = 2
};

//Title
CTS_CWString LevelMenu_Title_Text        = L"Pause Menu";
DataSize	 LevelMenu_Title_Text_Length = 0;
Ptr(Cell)	 LevelMenu_Title_RenderCells = NULL;

//Resume Button
CTS_CWString LevelMenu_Resume_Text   = L"Resume";
DataSize	 LevelMenu_Resume_Length = 0;
Ptr(Cell)    Resume_RenderCells      = NULL;

//Quit To Main Menu Button
CTS_CWString LevelMenu_QuitMM_Text = L"Quit To Main Menu";
DataSize	 LevelMenu_QuitMM_Text_Length = 0;
Ptr(Cell)    QuitMM_RenderCells = NULL;

//Public
fn returns(void)Game_LevelMenuSubState_OnKeyArrowUp parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"LevelMenu: On Key Up");

			if (LevelMenu_UI_Index == 2)
			{
				LevelMenu_UI_Index--;

				Renderer_WriteToLog(L"LevelMenu: UI Resume Active");

				ChangeCellsTo_White(Resume_RenderCells, LevelMenu_Resume_Length);
				ChangeCellsTo_Grey(QuitMM_RenderCells, LevelMenu_QuitMM_Text_Length);
			}


			break;
		}
	}
}
fn returns(void)Game_LevelMenuSubState_OnKeyArrowDown parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"LevelMenu: On Key Down");

			if (LevelMenu_UI_Index == 1)
			{
				LevelMenu_UI_Index++;
				Renderer_WriteToLog(L"LevelMenu: Quit To MM Resume Active");

				ChangeCellsTo_Grey(Resume_RenderCells, LevelMenu_Resume_Length);
				ChangeCellsTo_White(QuitMM_RenderCells, LevelMenu_QuitMM_Text_Length);
			}

			break;
		}
	}
}
fn returns(void)Game_LevelMenuSubState_OnKeyEnter parameters(EInputState _state)
{
	switch (_state)
	{
		case EInput_Pressed:
		{
			Renderer_WriteToLog(L"LevelMenu: On Key Enter");

				switch (LevelMenu_UI_Index)
				{
					case EUI_Resume:
					{
						Renderer_WriteToLog(L"LevelMenu: UI Resume Selected");

						if (canUseUI)
						{
							SubState_UnloadState();
						}

						break;

					}
					case EUI_QuitToMM:
					{
						Renderer_WriteToLog(L"LevelMenu: UI Quit To Main Menu Selected");

						SubState_UnloadState();

						State_SetState(GetState_MainMenu());

						break;
					}
				}
		}
	}
}


fn returns(void) LevelMenu_Load parameters(void)
{
	LevelMenu_Title_Text_Length  = wcslen(LevelMenu_Title_Text);
	LevelMenu_Resume_Length      = wcslen(LevelMenu_Resume_Text);
	LevelMenu_QuitMM_Text_Length = wcslen(LevelMenu_QuitMM_Text) + 1;

	LevelMenu_Title_RenderCells = GlobalAllocate(Cell, LevelMenu_Title_Text_Length);
	Resume_RenderCells          = GlobalAllocate(Cell, LevelMenu_Resume_Length);
	QuitMM_RenderCells          = GlobalAllocate(Cell, LevelMenu_QuitMM_Text_Length);

	for (DataSize cellIndex = 0; cellIndex < LevelMenu_Title_Text_Length; cellIndex++)
	{
		LevelMenu_Title_RenderCells[cellIndex].Char.UnicodeChar = LevelMenu_Title_Text[cellIndex];
	}

	for (DataSize cellIndex = 0; cellIndex < LevelMenu_Resume_Length; cellIndex++)
	{
		Resume_RenderCells[cellIndex].Char.UnicodeChar = LevelMenu_Resume_Text[cellIndex];
	}

	for (DataSize cellIndex = 0; cellIndex < LevelMenu_QuitMM_Text_Length; cellIndex++)
	{
		QuitMM_RenderCells[cellIndex].Char.UnicodeChar = LevelMenu_QuitMM_Text[cellIndex];
	}

	ChangeCellsTo_White(LevelMenu_Title_RenderCells, LevelMenu_Title_Text_Length);
	ChangeCellsTo_White(Resume_RenderCells         , LevelMenu_Resume_Length);
	ChangeCellsTo_Grey(QuitMM_RenderCells          , LevelMenu_QuitMM_Text_Length);
	
	//Reset UI Selection
	LevelMenu_UI_Index = 1;

	Input_SubscribeTo(Key_Arrow_Up, getAddress(Game_LevelMenuSubState_OnKeyArrowUp));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(Game_LevelMenuSubState_OnKeyArrowDown));
	Input_SubscribeTo(Key_Enter, getAddress(Game_LevelMenuSubState_OnKeyEnter));
	
	if (LevelMenu_Log_Load)
	{
		Renderer_WriteToLog(L"Load: Level Menu");

		LevelMenu_Log_Load = false;
	}

	
}

fn returns(void) LevelMenu_Unload parameters(void)
{	
	Input_Unsubscribe(Key_Arrow_Up, getAddress(Game_LevelMenuSubState_OnKeyArrowUp));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(Game_LevelMenuSubState_OnKeyArrowDown));
	Input_Unsubscribe(Key_Enter, getAddress(Game_LevelMenuSubState_OnKeyEnter));

	if (LevelMenu_Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Level Menu");

		LevelMenu_Log_Unload = false;
	}
}

fn returns(void) LevelMenu_Update parameters(void)
{

}

fn returns(void) LevelMenu_Render parameters(void)
{
	Stack()
		unbound COORD
		startingCell = { 0, 15 },
		endingCell = { 0, 15 };

	//Level Menu Title Cells
	startingCell.X = (ERenderer_Width / 2) - (LevelMenu_Title_Text_Length / 2) - 1;
	endingCell.X = (ERenderer_Width / 2) + (LevelMenu_Title_Text_Length / 2) - 1;

	startingCell.Y = 9;
	endingCell.Y = 9;

	Renderer_WriteToBufferCells(LevelMenu_Title_RenderCells, startingCell, endingCell);

	// Level Menu Resume Button 
	startingCell.X = (ERenderer_Width / 2) - (LevelMenu_Resume_Length / 2) - 1 ;
	endingCell.X = (ERenderer_Width / 2) + (LevelMenu_Resume_Length / 2) - 1;

	startingCell.Y = 15;
	endingCell.Y = 15;

	Renderer_WriteToBufferCells(Resume_RenderCells, startingCell, endingCell);

	// Level Menu Quit To Main Menu Button
	startingCell.X = (ERenderer_Width / 2) - (LevelMenu_QuitMM_Text_Length / 2) - 1 ;
	endingCell.X = (ERenderer_Width / 2) + (LevelMenu_QuitMM_Text_Length / 2) - 1;

	startingCell.Y = 17;
	endingCell.Y = 17;

	Renderer_WriteToBufferCells(QuitMM_RenderCells, startingCell, endingCell);

	canUseUI = true;
}

fn returns(Ptr(StateObj)) LoadLevelMenu parameters(void)
{
	LevelMenu.Load   = getAddress(LevelMenu_Load);
	LevelMenu.Unload = getAddress(LevelMenu_Unload);
	LevelMenu.Update = getAddress(LevelMenu_Update);
	LevelMenu.Render = getAddress(LevelMenu_Render);

	return getAddress(LevelMenu);
}