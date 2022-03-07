// Parent Header
#include "Input.h"



// Includes
#include "Cycler.h"
#include "Memory.h"



// Static Data

// Private

BSS()

	InputData Input;



// Forward Declarations

fn returns(EKeyCode) GetKeyCodeAtIndex(DataSize _index);
fn returns(DataSize) GetKeyIndexFromCode(EKeyCode _key);



// Functions

// Public

fn returns(void) Input_LoadModule parameters(void)
{
	//Input.StateIndex = 0;
}

fn returns(ro Ptr(InputData)) Input_GetContext(void)
{
	return getAddress(Input);
}



fn returns(void) Input_Update parameters(void)
{
	DataSize index = 0; 

	for (; index < Keys_NumTracked; index++)
	{
		Stack()
			bool Current, Previous;

		// Get current signal state

		Input.PreviousSignalState.Array[index] = Input.CurrentSignalState.Array[index];

		Previous = Input.CurrentSignalState.Array[index];

		Input.CurrentSignalState.Array[index] = GetKeySignal(GetKeyCodeAtIndex(index));

		Current = Input.CurrentSignalState.Array[index];

		//Determine latest Key State
		Stack()
			//Ptr(InputState_RingBuffer) ringBuffer = getAddress(Input.KeyStateBuffer[index]);

		Ptr(EInputState) CurrentState = getAddress(Input.KeyStates[index]);
			EInputState latestState;

		// Determine latest key state.
		if (Current == Previous)
		{
			if (Current == true)
			{
				latestState = EInput_PressHeld;
			}
			else
			{
				if (val(CurrentState) != EInput_PressHeld)
				{
					latestState = EInput_None;
				}
			}
		}
		else
		{
			if (Current == false)
			{
				latestState = EInput_Released;
			}
			else
			{
				latestState = EInput_Pressed;
			}
		}

		if (latestState != val(CurrentState))
		{
			val(CurrentState) = latestState;

			for (DataSize subIndex = 0; subIndex < Input.KeyEventSubs[index].Num; subIndex++)
			{
				if (Input.KeyEventSubs[index].Array[subIndex] != NULL)
				{
					Input.KeyEventSubs[index].Array[subIndex](val(CurrentState));
				}
			}
		}

	/*	Ptr(InputState_RingBuffer) ringBuffer = getAddress(Input.KeyStateBuffer[index]);

		Stack() EInputState CurrentState = ringBuffer->Buffer[ringBuffer->Index];

		if (latestState != CurrentState)
		{
			if (CurrentState >= (InputState_BufferSize - 1))
			{
				ringBuffer->Index = 0;
			}
			else
			{
				ringBuffer->Index = ringBuffer->Index + 1;
			}

			ringBuffer->Buffer[ringBuffer->Index] = latestState;

			switch (latestState)
			{
				case EInput_PressHeld:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Held");

					break;
				}
				case EInput_None:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: None");

					break;
				}
				case EInput_Released:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Released");

					break;
				}
				case EInput_Pressed:
				{
					if (index != 1) break;

					Renderer_WriteToLog(L"Key State: Pressed");

					break;
				}
			}
		}*/
	}
}

fn returns(void) Input_SubscribeTo parameters(EKeyCode _key, Ptr(InputEvent_Function)_callbackFunction)
{
	Stack()
		Ptr(Subscriptions) subs = getAddress(Input.KeyEventSubs[GetKeyIndexFromCode(_key)]);

	if (subs->Num == 0)
	{
		subs->Array = GlobalAllocate(Ptr(InputEvent_FunctionPtr), 1);

		subs->Num++;
	}
	else
	{

		for (DataSize subIndex = 0; subIndex < subs->Num; subIndex++)
		{
			if (subs->Array[subIndex] == NULL)
			{
				subs->Array[subs->Num - 1] = _callbackFunction;

				return;
			}
		}


		Stack()
			Address resizeIntermdiary = GlobalReallocate(Ptr(InputEvent_FunctionPtr), subs->Array, (subs->Num + 1));

		if (resizeIntermdiary != NULL)
		{
			subs->Array = resizeIntermdiary;

			subs->Num++;
		}
		else
		{
			perror("Failed to globally reallocate subscription array.");
			exit(1);
		}
	}

	subs->Array[subs->Num - 1] = _callbackFunction;

}

fn returns(void) Input_Unsubscribe parameters(EKeyCode _key, Ptr(InputEvent_Function)_callbackFunction)
{
	Stack()
		Ptr(Subscriptions) subs = getAddress(Input.KeyEventSubs[GetKeyIndexFromCode(_key)]);

	for (DataSize subIndex = 0; subIndex < subs->Num; subIndex++)
	{
		if (subs->Array[subIndex] == _callbackFunction)
		{
			subs->Array[subIndex] = NULL;
		}
	}
}



// Private
fn returns(EKeyCode) GetKeyCodeAtIndex(DataSize _index)
{
	switch (_index)
	{
		case 0:
		{
			return Key_Arrow_Up;
		}
		case 1:
		{
			return Key_Arrow_Down;
		}
		case 2:
		{
			return Key_Arrow_Left;
		}
		case 3:
		{
			return Key_Arrow_Right;
		}
		case 4:
		{
			return Key_Enter;
		}
	}
}

fn returns(DataSize) GetKeyIndexFromCode(EKeyCode _key)
{
	switch (_key)
	{
		case Key_Arrow_Up:
		{
			return 0;
		}
		case Key_Arrow_Down:
		{
			return 1;
		}
		case Key_Arrow_Left:
		{
			return 2;
		}
		case Key_Arrow_Right:
		{
			return 3;
		}
		case Key_Enter:
		{
			return 4;
		}
	}
}
