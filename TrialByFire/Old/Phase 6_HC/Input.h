#pragma once
// Includes
#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"


enum EInputConstants
{
	EInputConsoleInputBufferSize = 100,
};

// Aliases (Typedefs)

alias(struct InputData_Def  ) as InputData;
alias(struct InputDataBuffer_Def) as BufferData;



// Structures

struct InputData_Def
{
	EKeyCode Key;
	bool isKeyPressed;
	bool isKeyReleased;
	bool isKeyHeld;
};

struct InputDataBuffer_Def
{
	InputData InputBufferElement[4];
	EKeyCode PressedKey;
	EKeyCode CurrentKey;
	EKeyCode PreviousKey;
	bool isAnyKeyPressed;
	bool isAnyKeyHeld;

	float64 InputTimers[4];
	
	// Render Timing
	float64 RefeshInterval;
};



// Constants

#define SizeOf_InputSystem \
	sizeof(InputData)

// Forward Declarations

fn returns(void) Input_LoadModule parameters(void);

fn returns(Ptr(ro BufferData)) Input_GetContext(void);





fn returns(void) Input_Update parameters(void);

fn returns(void) Input_ProcessKeyState parameters(void);

fn returns(bool) Input_isKeyDown parameters(void);

fn returns(bool) Input_isKeyPressed parameters(void);

fn returns(bool) Input_isKeyHeld parameters(void);

fn returns(void) ResetInputBufferInfo parameters(void);

fn returns(bool) ShouldPoll parameters(void);

fn returns(void) Input_IncrementKeyTimer parameters(float64 _deltaTime, EKeyCode TimerKey);

fn returns(void) Input_ResetKeyTimer parameters(EKeyCode TimerKey);




