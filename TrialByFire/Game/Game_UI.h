#pragma once
#include "Engine/Engine.h"


//alias
alias(struct UI_TextObject_Def) as UI_TextObject;

alias(wchar_t) as CTS_CWString[];

alias(struct UI_Grid_Def) as UI_Grid;

alias(struct UI_GridCell_Def) as UI_GridCell;

alias(struct UI_ButtonObject_Def) as UI_ButtonObject;

alias(struct UI_ButtonManager_Def) as UI_ButtonManager;

alias(struct UI_GridStates_Def) as UI_GridStates;

//enum
enum
{
	EUI_TEXT_RED_FG = FOREGROUND_RED,
	EUI_TEXT_GREEN_FG = FOREGROUND_GREEN,
	EUI_TEXT_BLUE_FG = FOREGROUND_BLUE,
	EUI_TEXT_GREY_FG = FOREGROUND_INTENSITY,
	EUI_TEXT_WHITE_FG = Console_WhiteCell,


	EUI_TEXT_RED_BG = BACKGROUND_RED,
	EUI_TEXT_GREEN_BG = BACKGROUND_GREEN,
	EUI_TEXT_BLUE_BG = BACKGROUND_BLUE,
	EUI_TEXT_GREY_BG = BACKGROUND_INTENSITY,

};

enum
{
	EUI_GRIDSTATES_MAX = 2,
	EUI_GRID_MAX = 6,
};

enum
{
	EUI_MainMenu = 0,
	EUI_PausedMenu = 1
};

//Structures

struct UI_GridStates_Def
{
	Ptr(UI_Grid) GridStates[EUI_GRIDSTATES_MAX];
};
struct UI_Grid_Def
{
	Ptr(UI_GridCell) GridCell[EUI_GRID_MAX];
};

struct UI_GridCell_Def
{
	Ptr(UI_ButtonObject) cellButton;
	COORD StartingCell;
	COORD EndingCell;
};

struct UI_ButtonObject_Def
{
	Ptr(WideChar) Text;
	DataSize Length;
	Ptr(Cell) RenderCells;
	DataSize GridState_Assigned;
	DataSize GridCell_Assigned;

	bool isSelected;
};

struct UI_TextObject_Def
{
	Ptr(WideChar) Text;
	DataSize Length;
	Ptr(Cell) RenderCells;
};


//Forward Declarations
fn returns(void) Populate_UI_Text_Properties parameters(Ptr(UI_TextObject) _txtToPopulate);

fn returns(void) RenderTextCells parameters(Ptr(UI_TextObject) _objToRender, sInt16 x_Offset, sInt16 y_Offset);

fn returns(void) SetColorToTextCells parameters(Ptr(UI_TextObject) _objToRender, int _colorToSet);

fn returns(void) LoadPauseMenuGrid parameters(void);

fn returns(void) InitializeGridStatesAndCells parameters(void);
fn returns(void) Populate_UI_Button_Properties parameters(Ptr(UI_ButtonObject) _buttonToPopulate, DataSize _menuID, DataSize _slotNumber);
fn returns(void) SetColorToButtonCells parameters(Ptr(UI_ButtonObject) _buttonToRender, DataSize _colorToSet);
fn returns(void) RenderToGridCell parameters(Ptr(UI_ButtonObject) _buttonToRender);
fn returns(void) Populate_GridCells_Properties parameters(DataSize _menuID);