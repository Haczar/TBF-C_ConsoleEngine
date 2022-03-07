#pragma once



// Includes

#include "C_STL.h"
#include "OSPlatform.h"
#include "LAL.h"



// Macros

#define Make_BoolArray(_numBool) \
alias(bool) as BoolArray_##_numBool[_numBool]

#define TBoolArray(_numBool) \
BoolArray_##_numBool




// Enums

enum EInput_Constants
{
	Keys_NumTracked = 5,

	InputState_BufferSize = 10
};

enum EInputState_Def
{
	EInput_None,
	EInput_Released,
	EInput_Pressed,
	EInput_PressHeld
};



// Aliases (Typedefs)

alias(enum EInputState_Def) as EInputState;

alias(struct InputState_RingBuffer_Def) as InputState_RingBuffer;

//Make_BoolArray(Keys_NumTracked);

alias(bool) as BoolArray_KeySignals[Keys_NumTracked];

alias(struct StructOf_KeySignals_Def) as StructOf_KeySignals;

alias(struct Input_SignalState_Def) as Input_SignalState;
alias(struct InputData_Def)         as InputData;

alias(struct Input_KeyStates_Def) Input_KeyStates;

alias(FunctionType(InputEvent_Function, void, EInputState));

alias(struct Subscription_Def) as Subscriptions;

alias(Ptr(InputEvent_Function)) as InputEvent_FunctionPtr;



// Structures

struct StructOf_KeySignals_Def
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
	bool Enter;
};

struct Input_SignalState_Def
{
	union
	{
		BoolArray_KeySignals  Array;
		StructOf_KeySignals Keys;
	};
};

struct InputState_RingBuffer_Def
{
	EInputState Buffer[InputState_BufferSize];

	uInt Index;
};

struct Subscription_Def
{
	Ptr(InputEvent_FunctionPtr) Array;

	DataSize Num;
};

struct InputData_Def
{
	// Signal Buffer

	Input_SignalState CurrentSignalState ;
	Input_SignalState PreviousSignalState;

	// Key Input State Ring Buffer

	EInputState KeyStates[Keys_NumTracked];

	//Key Event Subscriptions
	Subscriptions KeyEventSubs[Keys_NumTracked];
};




// Constants

#define SizeOf_InputSystem \
	sizeof(InputData)



// Functions

fn returns(Ptr(ro InputData)) Input_GetContext(void);

fn returns(void) Input_LoadModule parameters(void);

fn returns(void) Input_Update parameters(void);

fn returns(void) Input_SubscribeTo parameters(EKeyCode _key, Ptr(InputEvent_Function)_callbackFunction);

fn returns(void) Input_UnSubscribe parameters(EKeyCode _key, Ptr(InputEvent_Function)_callbackFunction);

