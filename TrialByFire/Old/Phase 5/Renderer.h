#pragma once

// Includes
#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"

// Constants
#define SizeOf_Renderer \
	sizeof(RendererData)

enum ERenderer
{
	ERenderer_Width = 80,
	ERenderer_Height = 48,
	ERenderer_GameEnd = 23,
	ERenderer_Borderline = 24,
	ERenderer_DebugStart = 25,
	ERenderer_DebugLogSize = 18,
	ERenderer_DebugPersistentStart = 44,
	ERenderer_PersistentSectionSize = 4
};
//Aliases (Typedefs)

alias(CONSOLE_SCREEN_BUFFER_INFO) as CSBI;
alias(CHAR_INFO) as Cell;
alias(Cell) as Line[ERenderer_Width];
alias(struct RendererData_Def)     as RendererData;
alias(struct ScreenInfo_Def)	  as ScreenInfo;
alias(struct Vec2D_Int_Def)		as Vec2D_Int;



// Structures

struct Vec2D_Int_Def { sint64 X, Y; };

struct RendererData_Def
{
	// Procedure Data
	HWND   Window_Handle;
	HANDLE Output_Handle    ;

	DWORD  BufferSize;
	DWORD  CharactersWritten;
	COORD  CoordSize        ;
	CSBI   CSBI_Instance    ;
	SMALL_RECT Size;

	CONSOLE_CURSOR_INFO CursorSettings;
	
	Vec2D_Int ScreenPosition;

	// Render Timing
	float64 RefeshTimer   ;
	float64 RefeshInterval;
};

struct ScreenInfo_Def
{
	Vec2D_Int Center;
};





// Forward Declarations

fn returns(void) Renderer_Clear parameters(void);

fn returns(bool) Renderer_FillCellsWithWhitespace parameters(void);

fn returns(bool) Renderer_FormatCells parameters(void);

fn returns(ro Ptr(RendererData))Renderer_GetContext parameters(void);

fn returns(void) Renderer_LoadModule parameters(void);

fn returns(void) Renderer_ProcessTiming parameters(float64 _deltaTime);

fn returns(void) Renderer_RenderFrame parameters(void);

fn returns(void) ResetRendererDrawPosition parameters(void);

fn returns(void) Renderer_UnloadModule parameters(void);

fn returns(void) Renderer_Update parameters(void);

fn returns(void) Renderer_WriteToBufferCells parameters(Ptr(Cell) _cells, COORD _initialCell, COORD _finalCell);

//BS Fix for now:
alias(wchar_t) WideChar;
fn returns(void) Renderer_WriteToPersistentSection parameters(sint64 _row, Ptr(WideChar) _lineFormat, ...);

fn returns(void) Renderer_WriteToLog parameters(Ptr(WideChar) _logString);



