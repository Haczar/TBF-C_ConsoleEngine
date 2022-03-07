// Parent Header
#include "Renderer.h"
// Includes
#include "FloatCompare.h"
#include "Input.h"
#include "Memory.h"
#include "Timing.h"
#include "State.h"
#include "LAL.h"

// Static Data

// Private

BSS ()
	RendererData Renderer;

	ScreenInfo Screen;

	Ptr(CHAR_INFO) Buffer;
	
	Cell RenderBorder[ERenderer_Width];

	Line Border_GameDebug;
	Line Border_LogPersistent;
	Line DebugLogSection[ERenderer_DebugLogSize];
	Line PersistentSection[4];
	Line GameSection[24];

Data ()
	ro CTS_CWString Renderer_ConsoleTitle = L"TBF Engine: C Edition";
	ro COORD Console_Screen_00 =
	{
		0,  //X
		0	//Y
	};


	
//Forward Declarations
	fn returns(void) InitializeData parameters(void);
	fn returns(void) SetupConsole parameters(void);
	fn returns(void) UpdateSizeAndPosition parameters(void);
	fn returns(void) DrawGameScanlines parameters(void);
	fn returns(bool) ShouldRender parameters(void);
	fn returns(bool) UpdateConsoleInfo parameters(void);


// Functions

// PUBLIC
fn returns(void) Renderer_Clear parameters(void)
	{
		if (UpdateConsoleInfo())
		{
#ifdef USE_OLDWAY
			Renderer.BufferSize = Renderer.CSBI_Instance.dwSize.X * Renderer.CSBI_Instance.dwSize.Y;

			if (FillRendererCellsWithWhitespace() && UpdateRendererInfo() && FormatRendererCells())
			{
				ResetRendererDrawPosition();

				return;
			}
			else
			{
				return;   // If any of the conditions fail, return immediately.
			}
#else
			Memory_FormatByFill(CHAR_INFO, Buffer, 0, ERenderer_Width * ERenderer_Height);
#endif // USE_OLDWAY
		}
	}

fn returns(bool) Renderer_FillCellsWithWhitespace parameters(void)
{
	return FillConsoleOutputCharacter
	(
		Renderer.Output_Handle,
		(TCHAR)' ',
		Renderer.BufferSize,
		Console_Screen_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(bool) Renderer_FormatCells parameters(void)
{
	return FillConsoleOutputAttribute
	(
		Renderer.Output_Handle,
		Renderer.CSBI_Instance.wAttributes,
		Renderer.BufferSize,
		Console_Screen_00,
		getAddress(Renderer.CharactersWritten)
	);
}

fn returns(ro Ptr(RendererData))Renderer_GetContext parameters(void)
{
	return getAddress(Renderer);
}

fn returns(void) Renderer_LoadModule parameters(void)
{
	SetupConsole();

	InitializeData();

	SetConsoleTitle(Renderer_ConsoleTitle);

	UpdateSizeAndPosition();

	return;
}

fn returns(void) Renderer_ProcessTiming parameters(float64 _deltaTime)
{
	if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
	{
		Renderer.RefeshTimer = Renderer.RefeshTimer + 0.000001L;

		return;
	}
	else
	{
		Renderer.RefeshTimer = Renderer.RefeshTimer + _deltaTime;

		return;
	}
}

fn returns(void) Renderer_RenderFrame parameters(void)
{

#ifdef USE_OLDWAY
	Ptr(ro InputData) inputContext = GetInputContext();
	Ptr(ro TimingData) timingContext = GetTimingContext();

	printf("Tick Elapsed        : %llu  \n", timingContext->Cycle_TicksElapsed);
	printf("Timer      (Seconds): %.7Lf \n", Renderer.RefeshTimer);
	printf("Delta Time (Seconds): %.7Lf \n", timingContext->DeltaTime);
	printf("Key Pressed         :  %c   \n", inputContext->LastPressedKey);

#else
	WriteConsoleOutput(Renderer.Output_Handle, Buffer, Renderer.CoordSize, Console_Screen_00, getAddress(Renderer.Size));
#endif USE_OLDWAY
	return;

}
#undef USE_OLDWAY

fn returns(void) Renderer_UnloadModule parameters(void)
{
	if (Unbind_IOBufferTo_Console() != true)
	{
		perror("Failed to unbind standard IO from renderer console!");

		exit(1);
	}

	if (FreeConsole() != true)
	{
		perror("Failed to free renderer console!");

		exit(1);
	}
}

fn returns(void) Renderer_Update parameters(void)
{
	if (ShouldRender())
	{
		Renderer_Clear();

		//DrawGameScanlines();

		State_Render();

		Stack()
			COORD
			startingCell = { 0, ERenderer_Borderline },
			finalCell = { ERenderer_Width,ERenderer_Borderline };

			//GameSection
			COORD
			startingCell_Game = { 0, ERenderer_GameStart },
			finalCell_Game = { ERenderer_Width,ERenderer_GameEnd };

		//MyVersionOfGameIntro
		for (DataSize index = 0; index < ERenderer_GameSectionSize; index++)
		{
			startingCell_Game.Y = index;
			finalCell_Game.Y = ERenderer_GameEnd;

			Renderer_WriteToBufferCells(getAddress(GameSection[index]), startingCell_Game, finalCell_Game);
		}

		Renderer_WriteToBufferCells(getAddress(Border_GameDebug), startingCell, finalCell);

		startingCell.Y = ERenderer_DebugPersistentStart - 1;
		finalCell.Y = ERenderer_DebugPersistentStart - 1;

		Renderer_WriteToBufferCells(getAddress(Border_LogPersistent), startingCell, finalCell);

		for (DataSize index = 0; index < ERenderer_DebugLogSize; index++)
		{
			startingCell.Y = ERenderer_DebugStart + index;
			finalCell.Y   = ERenderer_DebugStart + index;

			Renderer_WriteToBufferCells(getAddress(DebugLogSection[index]), startingCell, finalCell);
		}

		for (DataSize index = 0; index < ERenderer_PersistentSectionSize; index++)
		{
			startingCell.Y = ERenderer_DebugPersistentStart + index;
			finalCell.Y   = ERenderer_DebugPersistentStart + index;

			Renderer_WriteToBufferCells(getAddress(PersistentSection[index]), startingCell, finalCell);
		}



		Renderer_RenderFrame();

		Renderer.RefeshTimer = 0.0L;
	}
}

fn returns(void) Renderer_WriteToBufferCells parameters(Ptr(Cell)_cells, COORD _initialCell, COORD _finalCell)
{
	Stack()
		DataSize rowOffset    = (_initialCell.Y) * ERenderer_Width;
		DataSize columnOffset = _initialCell.X;
		DataSize totalOffset  = rowOffset + columnOffset;

	Ptr(Byte) bufferPtr = Buffer;

	Ptr(void) bufferOffset = getAddress(Buffer[totalOffset]);

	DataSize dataSize = totalOffset;

	rowOffset = (_finalCell.Y) * ERenderer_Width;
	columnOffset = _finalCell.X;
	totalOffset = rowOffset + columnOffset;

	dataSize = totalOffset - dataSize;

	if (dataSize == 0)
	{
		dataSize = 1;
	}

	Memory_FormatWithData(bufferOffset, _cells, dataSize * sizeof(Cell));

	return;

}

//_HC
fn returns(void) Renderer_WriteToTitleGameSection parameters(sint64 _row, Ptr(WideChar) _lineFormat, ...)
{
	Stack()

		WideChar GameSection_TranslationBuffer[ERenderer_Width];

		Ptr(Cell) GameSubSection = GameSection[_row];

		sint64 CellsFormatted;

		va_list argList;

	va_start(argList, _lineFormat);

	CellsFormatted = _vswprintf_s_l(GameSection_TranslationBuffer, ERenderer_Width, _lineFormat, NULL, argList);

	va_end(argList);

	//centering
	Stack()
		sint64 stringLength = wcslen(_lineFormat);
		sint64 startingCell;
		sint64 centerBufferOffset = 0;

		startingCell = (ERenderer_Width / 2) - (stringLength / 2);

	for (DataSize index = startingCell; index < (CellsFormatted + startingCell); index++)
	{
		GameSubSection[index].Char.UnicodeChar = GameSection_TranslationBuffer[centerBufferOffset];
		GameSubSection[index].Attributes = Console_WhiteCell;
		centerBufferOffset++;
	}
}

fn returns(void) Renderer_FormatTitleGameSectionLine parameters(int _formatType, sint64 _lineNum)
{
	Ptr(Cell) GameSubSection;

	GameSubSection = GameSection[_lineNum];

	for (DataSize cellIndex = 0; cellIndex < ERenderer_Width; cellIndex++)
	{
		switch (_formatType)
		{
			case (ERenderer_GameFadeText):
			{
				GameSubSection[cellIndex].Attributes = BACKGROUND_INTENSITY;

			}

			case (ERenderer_GameStandardText):
			{
				GameSubSection[cellIndex].Attributes = FOREGROUND_INTENSITY;
			}

			case (ERenderer_GameColorText):
			{
				//GameSubSection[cellIndex].Attributes = BACKGROUND_GREEN;
			}
		}
	}
}


fn returns(void) Renderer_ClearGameSection parameters(void)
{
	Ptr(Cell) GameSubSection;

	for (DataSize lineIndex = 0; lineIndex <= ERenderer_GameSectionSize; lineIndex++)
	{
		GameSubSection = GameSection[lineIndex];

		for (DataSize cellIndex = 0; cellIndex < ERenderer_Width; cellIndex++)
		{
			GameSubSection[cellIndex].Char.UnicodeChar = NULL;
			GameSubSection[cellIndex].Attributes = NULL;
		}
	}
}

fn returns(void) Renderer_WriteToPersistentSection parameters(sint64 _row, Ptr(WideChar) _lineFormat, ...)
{
	Stack()

		WideChar TranslationBuffer[ERenderer_Width];

		Ptr(Cell) PersistentSubSection = PersistentSection[_row - 1];
		
		sint64 CellsFormatted;
		
		va_list argList;

	va_start(argList, _lineFormat);

	CellsFormatted = _vswprintf_s_l(TranslationBuffer, ERenderer_Width, _lineFormat, NULL, argList);

	va_end(argList);

	for (DataSize index = 0; index < CellsFormatted; index++)
	{
		PersistentSubSection[index].Char.UnicodeChar = TranslationBuffer[index];
		PersistentSubSection[index].Attributes = Console_WhiteCell;
	}

	for (DataSize index = CellsFormatted + 1; index < ERenderer_Width; index++)
	{
		PersistentSubSection[index].Char.UnicodeChar = NULL;
		PersistentSubSection[index].Attributes = NULL;
	}
}

fn returns(void) Renderer_WriteToLog parameters(Ptr(WideChar) _logString)
{
	Stack()
		sGlobal uInt nextLine = 0;

	DataSize logLength = wcslen(_logString);
	DataSize linePos = 0;

	for (DataSize index = 0; index < logLength; index++)
	{
		if (linePos > ERenderer_Width - 1)
		{
			nextLine++;

			linePos = 0;
		}

		if (nextLine == 18)
		{
			nextLine = 0;
		}

		DebugLogSection[nextLine][linePos].Char.UnicodeChar = _logString[index];
		DebugLogSection[nextLine][linePos].Attributes = Console_WhiteCell;

		linePos++;
	}

	for (DataSize index = linePos; index < ERenderer_Width; index++)
	{
		DebugLogSection[nextLine][index].Char.UnicodeChar = 0;
		DebugLogSection[nextLine][index].Attributes = 0;
	}
	nextLine++;

	if (nextLine == 18)
	{
		nextLine = 0;
	}

	Stack()
		Cell fillInfo;

	fillInfo.Char.UnicodeChar = L'-';
	fillInfo.Attributes = Console_WhiteCell;

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		DebugLogSection[nextLine][index] = fillInfo;
	}
}

//PRIVATE

fn returns(void) InitializeData parameters(void)
{
	Screen.Center.X = GetSystemMetrics(SM_CXSCREEN) / 2;
	Screen.Center.Y = GetSystemMetrics(SM_CYSCREEN) / 2;

	Renderer.ScreenPosition.X = (Screen.Center.X - ((ERenderer_Width / 2) * 8)) - 20;
	Renderer.ScreenPosition.Y = (Screen.Center.Y - ((ERenderer_Height / 2) * 8)) - 200;

	Renderer.RefeshTimer = 0.0L;
	Renderer.RefeshInterval = 0.01L;

	Renderer.CoordSize.X = ERenderer_Width;
	Renderer.CoordSize.Y = ERenderer_Height;

	Renderer.Output_Handle = GetStdHandle(STD_OUTPUT_HANDLE);

	Renderer.Window_Handle = GetConsoleWindow();

	Renderer.Size.Left = Console_Screen_00.X;
	Renderer.Size.Top = Console_Screen_00.Y;
	Renderer.Size.Right = ERenderer_Width - 1;
	Renderer.Size.Bottom = ERenderer_Height - 1;

	Renderer.CursorSettings.dwSize = Console_Cursor_MinSize;
	Renderer.CursorSettings.bVisible = Console_Cursor_NotVisible;

	Buffer = GlobalAllocate(CHAR_INFO, ERenderer_Width * ERenderer_Height);

	Memory_FormatByFill(CHAR_INFO, Buffer, 0, ERenderer_Width * ERenderer_Height);

	Stack()
		Cell borderCell;
	borderCell.Char.UnicodeChar = '=';
	borderCell.Attributes = Console_WhiteCell;

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		//RenderBorder[index] = borderCell;
		Border_GameDebug[index] = borderCell;
		Border_LogPersistent[index] = borderCell;
	}

	Memory_FormatByFill(Line, PersistentSection, 0, 4);

	return;

}

fn returns(void) DrawGameScanlines parameters(void)
{
	Stack()
		sGlobal COORD cellIndex = { 0, 0 };

		ro WideChar BlockChar = '-';

		Cell cellUnit;

	cellUnit.Char.UnicodeChar = BlockChar;
	cellUnit.Attributes = FOREGROUND_GREEN;
	
	Stack()
		Cell cellLine[ERenderer_Width];

	for (DataSize index = 0; index < ERenderer_Width; index++)
	{
		cellLine[index] = cellUnit;
	}

	Stack()
		COORD cellIndex_End = { ERenderer_Width, cellIndex.Y };

	Renderer_WriteToBufferCells(getAddress(cellLine), cellIndex, cellIndex_End);

	cellIndex.Y++;

	if (cellIndex.X >= ERenderer_Width)
	{
		cellIndex.X = 0;
		cellIndex.Y++;
	}
	if (cellIndex.Y > ERenderer_GameEnd)
	{
		cellIndex.X = 0;
		cellIndex.Y = 0;
	}

}

fn returns(void) ResetRendererDrawPosition parameters(void)
{
	SetConsoleCursorPosition(Renderer.Output_Handle, Console_Screen_00);

	return;
}

fn returns(bool) ShouldRender parameters(void)
{
	return Float64_ApproxGreater(Renderer.RefeshTimer, Renderer.RefeshInterval) ||
		Float64_ApproxEqual(Renderer.RefeshTimer, Renderer.RefeshInterval);
}

fn returns(void) SetupConsole parameters(void)
{
	if (RequestConsole() != true)
	{
		perror("Failed to get console from OS");
		exit(1);
	}

	if (Bind_IOBufferTo_Console() != true)
	{
		perror("Failed to bind standard IO to render console");
		exit(1);
	}
}

fn returns(bool) UpdateConsoleInfo parameters(void)
{
	return GetConsoleScreenBufferInfo(Renderer.Output_Handle, getAddress(Renderer.CSBI_Instance));
}

fn returns(void) UpdateSizeAndPosition parameters(void)
{
	//Set desired cursor preferences
	SetConsoleCursorInfo(Renderer.Output_Handle, getAddress(Renderer.CursorSettings));

	//Change the window size
	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(Renderer.Size));

	//Update the buffer size
	SetConsoleScreenBufferSize(Renderer.Output_Handle, Renderer.CoordSize);

	//Update the window size
	SetConsoleWindowInfo(Renderer.Output_Handle, true, getAddress(Renderer.Size));

	SetWindowPos(Renderer.Window_Handle,
		HWND_TOP,
		Renderer.ScreenPosition.X,
		Renderer.ScreenPosition.Y,
		0,
		0,
		SWP_NOSIZE);

}

fn returns(void) Backend_WriteToPersistentSection parameters(sint64 _row, Ptr(WideChar) _lineFormat, va_list _arguments)
{

}



