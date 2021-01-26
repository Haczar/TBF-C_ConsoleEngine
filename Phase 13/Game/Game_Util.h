#pragma once



// Includes

#include "Engine/Engine.h"




// Enums

enum 
{
	ECharacter_DontMove ,
	ECharacter_MoveLeft ,
	ECharacter_MoveRight,

	LevelCell_Empty  = 0,
	LevelCell_Pit    = BACKGROUND_BLUE,
	LevelCell_Ground = BACKGROUND_GREEN,
	LevelCell_Finish = BACKGROUND_RED
};



// Aliases

// Character

alias(struct Character_Def) as Character;

// Level

alias(Line) as GameScreenBuffer [ERenderer_GameEnd + 1];

alias(GameScreenBuffer) as Level;

// Space

alias(struct Vector2D_Def) as Vector2D;


// UI

alias(struct UI_Text_Def  ) as UI_Text;
alias(struct UI_Button_Def) as UI_Button;
alias(struct UI_Grid_Def  ) as UI_Grid;
alias(struct UI_Widget_Def) as UI_Widget;



// Structs

// Space

struct Vector2D_Def
{
	float32 X;
	float32 Y;
};

// Character

struct Character_Def
{
	Cell Sprite;

	Vector2D Position;

	float32 VerticalVelocity;

	bool ShouldJump, Fell;

	sInt Active_MoveState;
	sInt MoveState;
};

// UI

struct UI_Text_Def
{
	Ptr(WideChar) Content;

	DataSize Length;

	Ptr(Cell) RenderCells;

	COORD StartingCell, EndingCell;
};

struct UI_Button_Def
{
	UI_Text Text;

	Ptr(Void_Function) Callback;
};

struct UI_Grid_Def
{
	Ptr(UI_Button) Buttons;

	DataSize Num;

	DataSize CurrentIndex;
};

struct UI_Widget_Def
{
	Ptr(UI_Text) TextUIs;

	DataSize Num_TextUIs;

	//Ptr(UI_Grid) Grids;

	UI_Grid Grid;
};



// Functions

// Character

fn returns(bool) Character_AtFinish parameters(Ptr(Character) _character, Ptr(Level) _level);

fn returns(bool) Character_IsGrounded parameters(Ptr(Character) _character, Ptr(Level) _level);

fn returns(void) Character_Load parameters(Ptr(Character) _character);

fn returns(void) Character_Update parameters(Ptr(Character) _character, Ptr(Level) _level);

fn returns(void) Character_Render parameters(Ptr(Character) _character);

// Level

fn returns(sInt) Level_GetCellAtPosition parameters(Ptr(Level) _level, Vector2D _position);

fn returns(void) Level_SetCells parameters(Ptr(Level) _level, COORD _firstCell, COORD _lastCell, sInt _cellType);

fn returns(void) Level_Render parameters(Ptr(Level) _level);

// Space

fn returns(COORD) Convert_Vector2D_ToRenderCoord parameters(Vector2D _vector);

// General Rendering

fn returns(void) ChangeCellsTo_Grey parameters(Ptr(Cell) _renderCells, DataSize _length);

fn returns(void) ChangeCellsTo_White parameters(Ptr(Cell) _renderCells, DataSize _length);

// UI

fn returns(void) UI_Text_Create 

parameters
(
	   Ptr(UI_Text)  _uiText, 
	   Ptr(WideChar) _content, 
	       COORD     _startingCell, 
	       COORD     _endingCell,
	       bool      _shouldCenter
);

fn returns(void) UI_Text_Render parameters(ro Ptr(UI_Text) _uiText);

fn returns(void) UI_Button_Create 

parameters
(
	   Ptr(UI_Button)     _button, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Button_Press  parameters(ro Ptr(UI_Button) _uiButton);
fn returns(void) UI_Button_Render parameters(ro Ptr(UI_Button) _uiButton);

fn returns(void) UI_Grid_Add 

parameters
(
	   Ptr(UI_Grid)       _uiGrid, 
	ro Ptr(WideChar)      _text, 
	       COORD          _startingCell, 
	       COORD          _endingCell, 
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Grid_MoveUp   parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_MoveDown parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_Select   parameters(Ptr(UI_Grid) _uiGrid);
fn returns(void) UI_Grid_Render   parameters(Ptr(UI_Grid) _uiGrid);

fn returns(void) UI_Widget_AddText

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell,
	       bool           _shouldCenter
);

fn returns(void) UI_Widget_AddButton 

parameters
(
	   Ptr(UI_Widget)     _uiWidget,
	ro Ptr(WideChar)      _text,
	       COORD          _startingCell,
	       COORD          _endingCell,
	       bool           _shouldCenter,
	   Ptr(Void_Function) _callback
);

fn returns(void) UI_Widget_MoveUp   parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_MoveDown parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_Select   parameters(Ptr(UI_Widget) _uiWidget);
fn returns(void) UI_Widget_Render   parameters(Ptr(UI_Widget) _uiWidget);


