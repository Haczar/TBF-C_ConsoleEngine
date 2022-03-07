//Parent Hearder
#include "Game_UI.h"


UI_GridStates MenuContainer;
UI_Grid Menu;


//Populating Properties
fn returns(void) InitializeGridStatesAndCells parameters(void)
{
	for (DataSize gridStateIndex = 0; gridStateIndex < EUI_GRIDSTATES_MAX; gridStateIndex++)
	{
		MenuContainer.GridStates[gridStateIndex] = GlobalAllocate(UI_Grid, 1);

		for (DataSize gridCellIndex = 0; gridCellIndex < EUI_GRID_MAX; gridCellIndex++)
		{
			MenuContainer.GridStates[gridStateIndex]->GridCell[gridCellIndex] = GlobalAllocate(UI_GridCell, 1);
		}
	}
}

fn returns(void) Populate_GridCells_Properties parameters(DataSize _menuID)
{
	DataSize yOffset = 11;

	for (int gridCellIndex = 0; gridCellIndex < EUI_GRID_MAX; gridCellIndex++)
	{
		if (yOffset <= ERenderer_GameEnd)
		{
			MenuContainer.GridStates[_menuID]->GridCell[gridCellIndex]->StartingCell.X = 0;
			MenuContainer.GridStates[_menuID]->GridCell[gridCellIndex]->EndingCell.X = ERenderer_Width;

			MenuContainer.GridStates[_menuID]->GridCell[gridCellIndex]->StartingCell.Y = yOffset;
			MenuContainer.GridStates[_menuID]->GridCell[gridCellIndex]->EndingCell.Y = yOffset;

			MenuContainer.GridStates[_menuID]->GridCell[gridCellIndex]->cellButton = NULL;

			yOffset = yOffset + 2;
		}
	}
}

fn returns(void) Populate_UI_Text_Properties parameters(Ptr(UI_TextObject) _txtToPopulate)
{
	//Populate Text Length
	_txtToPopulate->Length = wcslen(_txtToPopulate->Text);

	if ((_txtToPopulate->Length % 2) != 0)
	{
		_txtToPopulate->Length++;
	}

	//Assign RenderCell
	_txtToPopulate->RenderCells = GlobalAllocate(Cell, _txtToPopulate->Length);

	//Fill RenderCell
	for (DataSize cellIndex = 0; cellIndex < _txtToPopulate->Length; cellIndex++)
	{
		_txtToPopulate->RenderCells[cellIndex].Char.UnicodeChar = _txtToPopulate->Text[cellIndex];
	}
}

fn returns(void) Populate_UI_Button_Properties parameters(Ptr(UI_ButtonObject) _buttonToPopulate, DataSize _menuID, DataSize _slotNumber)
{
	//Populate ButtonText Length
	_buttonToPopulate->Length = wcslen(_buttonToPopulate->Text);

	if ((_buttonToPopulate->Length % 2) != 0)
	{
		_buttonToPopulate->Length++;
	}
	//Assign RenderCell To Memory
	_buttonToPopulate->RenderCells = GlobalAllocate(Cell, _buttonToPopulate->Length);

	//Assign the menu the button belongs to
	_buttonToPopulate->GridState_Assigned = _menuID;
	//Assign the slot in the menu the button belongs to 
	_buttonToPopulate->GridCell_Assigned = _slotNumber;

	//None are selected at the start
	_buttonToPopulate->isSelected = false;
	
	//populate render cells
	for (DataSize cellIndex = 0; cellIndex < _buttonToPopulate->Length; cellIndex++)
	{
		_buttonToPopulate->RenderCells[cellIndex].Char.UnicodeChar = _buttonToPopulate->Text[cellIndex];
	}

	//Update Starting and Ending Cell X Values For Centered Buttons
	MenuContainer.GridStates[_buttonToPopulate->GridState_Assigned]->GridCell[_buttonToPopulate->GridCell_Assigned]->StartingCell.X =
		(ERenderer_Width / 2) - (_buttonToPopulate->Length / 2);

	MenuContainer.GridStates[_buttonToPopulate->GridState_Assigned]->GridCell[_buttonToPopulate->GridCell_Assigned]->EndingCell.X =
		(ERenderer_Width / 2) + (_buttonToPopulate->Length / 2);

	//Assign reference to Button Object To Memory and copy address to grid cell
	MenuContainer.GridStates[_menuID]->GridCell[_slotNumber]->cellButton = GlobalAllocate(UI_ButtonObject, 1);
}

//Rendering
fn returns(void) RenderTextCells parameters(Ptr(UI_TextObject) _objToRender, sInt16 x_Offset, sInt16 y_Offset)
{
	Stack()
		unbound COORD startingCell, endingCell;

	// Title Cells
	startingCell.X = (ERenderer_Width / 2) - (_objToRender->Length / 2) + x_Offset;
	endingCell.X   = (ERenderer_Width / 2) + (_objToRender->Length / 2) + x_Offset;

	startingCell.Y = y_Offset;
	endingCell.Y   = y_Offset;

	Renderer_WriteToBufferCells(_objToRender->RenderCells, startingCell, endingCell);
}

fn returns(void) RenderToGridCell parameters(Ptr(UI_ButtonObject) _buttonToRender)
{
	COORD startingCell = MenuContainer.GridStates[_buttonToRender->GridState_Assigned]->GridCell[_buttonToRender->GridCell_Assigned]->StartingCell;
	COORD endingCell   = MenuContainer.GridStates[_buttonToRender->GridState_Assigned]->GridCell[_buttonToRender->GridCell_Assigned]->EndingCell;
	
	Renderer_WriteToBufferCells(_buttonToRender->RenderCells, startingCell, endingCell);
}

//Modifying Values
fn returns(void) SetColorToTextCells parameters(Ptr(UI_TextObject) _objToRender, DataSize _colorToSet)
{
	for (DataSize cellIndex = 0; cellIndex < _objToRender->Length; cellIndex++)
	{
		_objToRender->RenderCells[cellIndex].Attributes = _colorToSet;
	}
}

fn returns(void) SetColorToButtonCells parameters(Ptr(UI_ButtonObject) _buttonToRender, DataSize _colorToSet)
{
	for (DataSize cellIndex = 0; cellIndex < _buttonToRender->Length; cellIndex++)
	{
		_buttonToRender->RenderCells[cellIndex].Attributes = _colorToSet;
	}
}

fn returns(void) ProcessButtonAction parameters(Ptr(UI_ButtonObject) _buttonSelected)
{
	//processing button function if selected
}

fn returns(void) ProcessUISelection parameters(EInputState _state)
{
	//processing up and down actions and setting selected button
}

fn returns(void) SetupUI parameters(UI_Grid _uiToSetup)
{
	//switch case per menu with text, enum of butotons, selected button
}




