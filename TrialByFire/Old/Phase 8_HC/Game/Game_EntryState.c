// Parent Header
#include "Game_EntryState.h"
#include "Game_LevelState.h"



BSS()

	StateObj MainMenu;

Data()
	bool 
		Log_Load   = true;
		Log_Unload = true;

	//UI
	
	DataSize UI_Index = 1;

	enum
	{
		EUI_None = 0,
		EUI_Start = 1,
		EUI_Quit = 2
	};

	//Title
	CTS_CWString MainMenu_Title_Text         = L"Generic Platform Demo";
	DataSize     MainMenu_Title_Text_Length  = 0;
	Ptr(Cell)    MainMenu_Title_RenderCells  = NULL;

	//Start Button
	CTS_CWString Start_Text = L"Start";
	DataSize  Start_Text_Length = 0;
	Ptr(Cell) Start_Rendercells = NULL;
	sint16 Start_X = -1;

	TimerData Start_NudgeTime;
	bool Start_Nudged = false;


	//Quit Button
	CTS_CWString Quit_Text = L"Quit";
	DataSize Quit_Text_Length = 0;
	Ptr(Cell) Quit_Rendercells = NULL;




	



// Functions
//Private

fn returns(void)ChangeCellsTo_Grey parameters(Ptr(Cell)_renderCells, DataSize _length)
{
	for (DataSize cellIndex = 0; cellIndex < _length; cellIndex++)
	{
		_renderCells[cellIndex].Attributes = FOREGROUND_INTENSITY;
	}
}

fn returns(void)ChangeCellsTo_White parameters(Ptr(Cell)_renderCells, DataSize _length)
{
	for (DataSize cellIndex = 0; cellIndex < _length; cellIndex++)
	{
		_renderCells[cellIndex].Attributes = Console_WhiteCell;
	}
}

//Public
fn returns(void)Game_EntryState_OnKeyArrowUp parameters  (EInputState _state)
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

				ChangeCellsTo_White(Start_Rendercells, Start_Text_Length);
				ChangeCellsTo_Grey(Quit_Rendercells, Quit_Text_Length);
			}
			break;
		}
	}
}
fn returns(void)Game_EntryState_OnKeyArrowDown parameters(EInputState _state)
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

				ChangeCellsTo_Grey(Start_Rendercells, Start_Text_Length);
				ChangeCellsTo_White(Quit_Rendercells, Quit_Text_Length);
			}

			break;
		}
	}
}
fn returns(void)Game_EntryState_OnKeyEnter parameters    (EInputState _state)
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

					Start_X++;

					Start_Nudged = true;

					//Load Game Level
					State_SetState(LoadLevel());

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
	MainMenu_Title_Text_Length = wcslen(MainMenu_Title_Text) + 1;
	Start_Text_Length = wcslen(Start_Text) + 1;
	Quit_Text_Length = wcslen(Quit_Text);

	MainMenu_Title_RenderCells = GlobalAllocate(Cell, MainMenu_Title_Text_Length);
	Start_Rendercells = GlobalAllocate(Cell, Start_Text_Length);
	Quit_Rendercells  = GlobalAllocate(Cell, Quit_Text_Length);

	for (DataSize cellIndex = 0; cellIndex < MainMenu_Title_Text_Length; cellIndex++)
	{
		MainMenu_Title_RenderCells[cellIndex].Char.UnicodeChar = MainMenu_Title_Text[cellIndex];
	}

	for (DataSize cellIndex = 0; cellIndex < Start_Text_Length; cellIndex++)
	{
		Start_Rendercells[cellIndex].Char.UnicodeChar = Start_Text[cellIndex];
	}

	for (DataSize cellIndex = 0; cellIndex < Quit_Text_Length; cellIndex++)
	{
		Quit_Rendercells[cellIndex].Char.UnicodeChar = Quit_Text[cellIndex];

	}

	ChangeCellsTo_White(MainMenu_Title_RenderCells, MainMenu_Title_Text_Length);
	ChangeCellsTo_White(Start_Rendercells, Start_Text_Length);
	ChangeCellsTo_Grey (Quit_Rendercells, Quit_Text_Length);

	Start_NudgeTime.EndTime = 0.075f;

	//Subscribe to input events
	Input_SubscribeTo(Key_Arrow_Up, getAddress(Game_EntryState_OnKeyArrowUp));
	Input_SubscribeTo(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_SubscribeTo(Key_Enter, getAddress(Game_EntryState_OnKeyEnter));

	if (Log_Load)
	{
		Renderer_WriteToLog(L"Loaded: Main Menu");

		Log_Load = false;
	}
}

fn returns(void) MainMenu_Unload parameters(void)
{
	Input_Unsubscribe(Key_Arrow_Up, getAddress(Game_EntryState_OnKeyArrowUp));
	Input_Unsubscribe(Key_Arrow_Down, getAddress(Game_EntryState_OnKeyArrowDown));
	Input_Unsubscribe(Key_Enter, getAddress(Game_EntryState_OnKeyEnter));
	
	if (Log_Unload)
	{
		Renderer_WriteToLog(L"Unload: Main Menu");

		Log_Unload = false;
	}
}

fn returns(void) MainMenu_Update parameters(void)
{

	if (Start_Nudged)
	{
		Timer_Tick(getAddress(Start_NudgeTime));
		if (Timer_Ended(getAddress(Start_NudgeTime)))
		{
			Start_X--;
			Start_Nudged = false;
			Timer_Reset(getAddress(Start_NudgeTime));
		}
	}
}

fn returns(void) MainMenu_Render parameters(void)
{
	Stack()
		unbound COORD
		startingCell = { 0, 15 },
		endingCell   = { 0, 15};

	//Title Cells
	startingCell.X = (ERenderer_Width / 2) - (MainMenu_Title_Text_Length / 2) - 1;
	endingCell.X   = (ERenderer_Width / 2) + (MainMenu_Title_Text_Length / 2) - 1;

	startingCell.Y = 9;
	endingCell.Y = 9;

	Renderer_WriteToBufferCells(MainMenu_Title_RenderCells, startingCell, endingCell);

// Start UI Cells
	startingCell.X = (ERenderer_Width / 2) - (Start_Text_Length / 2) + Start_X;
	endingCell.X   = (ERenderer_Width / 2) + (Start_Text_Length / 2) + Start_X;

	startingCell.Y = 15;
	endingCell.Y = 15;

	Renderer_WriteToBufferCells(Start_Rendercells, startingCell, endingCell);

// Quit UI Cells
	startingCell.X = (ERenderer_Width / 2) - (Quit_Text_Length / 2) - 2;
	endingCell.X = (ERenderer_Width / 2) + (Quit_Text_Length / 2) - 2;

	startingCell.Y = 17;
	endingCell.Y = 17;

	Renderer_WriteToBufferCells(Quit_Rendercells, startingCell, endingCell);
}

fn returns( Ptr(StateObj) ) GetState_MainMenu parameters(void)
{
	return getAddress(MainMenu);
}

// Engine Entrypoint

fn returns(Ptr(StateObj)) LoadGame parameters(void)
{
	MainMenu.Load   = getAddress(MainMenu_Load  );
	MainMenu.Unload = getAddress(MainMenu_Unload);
	MainMenu.Update = getAddress(MainMenu_Update);
	MainMenu.Render = getAddress(MainMenu_Render);

	return getAddress(MainMenu);
}



