// Parent Header
#include "Input.h"

// Includes
#include "Cycler.h"
#include "Memory.h"



// Static Data

// Private
BSS()
	BufferData InputBufferContainer;

	ro Ptr(TimingData) TimingContext;

	RendererData RendererContext;


// Functions

// Public
fn returns(Ptr(ro BufferData)) Input_GetContext(void)
{
	return getAddress(InputBufferContainer);
}

fn returns(void) Input_LoadModule parameters(void)
{



	InputBufferContainer.InputBufferElement[0].Key = Key_Arrow_Up;
	InputBufferContainer.InputBufferElement[1].Key = Key_Arrow_Down;
	InputBufferContainer.InputBufferElement[2].Key = Key_Arrow_Left;
	InputBufferContainer.InputBufferElement[3].Key = Key_Arrow_Right;

	for (int timerIndex = 0; timerIndex < 4; timerIndex++)
	{
		InputBufferContainer.InputTimers[timerIndex] = 0.0;
	}

	InputBufferContainer.RefeshInterval = 1.0;

	InputBufferContainer.PreviousKey = Key_NoKey;
	InputBufferContainer.CurrentKey = Key_NoKey;

	InputBufferContainer.isAnyKeyHeld = false;

	//ResetInputBufferInfo();

}

fn returns(void) ResetInputBufferInfo parameters(void)
{
	for (int bufferIndex = 0; bufferIndex < 4; bufferIndex++)
	{
		InputBufferContainer.CurrentKey = Key_NoKey;
		InputBufferContainer.PressedKey = Key_NoKey;
		InputBufferContainer.PreviousKey = Key_NoKey;
	}

}

fn returns(void) Input_Update parameters(void)
{
	TimingContext = Timing_GetContext();


	if (Input_isKeyDown())
	{
		Input_ProcessKeyState();
	}
	else
	{
		Input_isKeyPressed();
		Input_ResetKeyTimer(InputBufferContainer.PreviousKey);
	}
}

fn returns(void) Input_ProcessKeyState parameters(void)
{
	if (!ShouldPoll(InputBufferContainer.CurrentKey))
	{
		InputBufferContainer.PreviousKey = InputBufferContainer.CurrentKey;

		Input_IncrementKeyTimer(TimingContext->DeltaTime, InputBufferContainer.CurrentKey);
		Input_isKeyHeld(InputBufferContainer.CurrentKey);
	}
}



fn returns(bool) Input_isKeyDown parameters(void)
{
	
	if (GetKeySignal(Key_Arrow_Up))
	{
		InputBufferContainer.CurrentKey = Key_Arrow_Up;
		InputBufferContainer.isAnyKeyPressed = false;
		
		return true;
	}
	if (GetKeySignal(Key_Arrow_Down))
	{
		InputBufferContainer.CurrentKey = Key_Arrow_Down;
		InputBufferContainer.isAnyKeyPressed = false;

		return true;
	}
	if (GetKeySignal(Key_Arrow_Left))
	{
		InputBufferContainer.CurrentKey = Key_Arrow_Left;
		InputBufferContainer.isAnyKeyPressed = false;

		return true;
	}
	if (GetKeySignal(Key_Arrow_Right))
	{
		InputBufferContainer.CurrentKey = Key_Arrow_Right;
		InputBufferContainer.isAnyKeyPressed = false;

		return true;
	}

	InputBufferContainer.CurrentKey = Key_NoKey;
	InputBufferContainer.isAnyKeyHeld = false;

	return false;
}

fn returns(bool) Input_isKeyPressed parameters(void)
{
	if (InputBufferContainer.PreviousKey != Key_NoKey &&
			InputBufferContainer.CurrentKey == Key_NoKey)
	{
			for (int bufferIndex = 0; bufferIndex < 4; bufferIndex++)
			{
				if (InputBufferContainer.PreviousKey == InputBufferContainer.InputBufferElement[bufferIndex].Key)
				{
					InputBufferContainer.InputBufferElement[bufferIndex].isKeyPressed = true;
					InputBufferContainer.isAnyKeyPressed = true;

				}
			}

	}
	else
	{
		for (int bufferIndex = 0; bufferIndex < 4; bufferIndex++)
		{
			InputBufferContainer.InputBufferElement[bufferIndex].isKeyPressed = false;
			InputBufferContainer.isAnyKeyPressed = false;
		}
	}
}

fn returns(void) Input_IncrementKeyTimer parameters(float64 _deltaTime, EKeyCode TimerKey)
{
	switch (TimerKey)
	{
		case Key_Arrow_Up:
		{
			if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
			{
				InputBufferContainer.InputTimers[0] = InputBufferContainer.InputTimers[0] + 0.000001L;

				return;
			}
			else
			{
				InputBufferContainer.InputTimers[0] = InputBufferContainer.InputTimers[0] + _deltaTime;

				return;
			}

			break;
		}

		case Key_Arrow_Down:
		{
			if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
			{
				InputBufferContainer.InputTimers[1] = InputBufferContainer.InputTimers[1] + 0.000001L;

				return;
			}
			else
			{
				InputBufferContainer.InputTimers[1] = InputBufferContainer.InputTimers[1] + _deltaTime;

				return;
			}

			break;
		}

		case Key_Arrow_Left:
		{
			if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
			{
				InputBufferContainer.InputTimers[2] = InputBufferContainer.InputTimers[2] + 0.000001L;

				return;
			}
			else
			{
				InputBufferContainer.InputTimers[2] = InputBufferContainer.InputTimers[2] + _deltaTime;

				return;
			}

			break;
		}

		case Key_Arrow_Right:
		{
			if (Float64_ApproxEqual(_deltaTime, 0.000001L) || Float64_ApproxLess(_deltaTime, 0.000001L))
			{
				InputBufferContainer.InputTimers[3] = InputBufferContainer.InputTimers[3] + 0.000001L;

				return;
			}
			else
			{
				InputBufferContainer.InputTimers[3] = InputBufferContainer.InputTimers[3] + _deltaTime;

				return;
			}

			break;
		}
	}

}

fn returns(void) Input_ResetKeyTimer parameters(EKeyCode TimerKey)
{
	InputBufferContainer.CurrentKey = Key_NoKey;

	switch (TimerKey)
	{
		case Key_Arrow_Up:
		{
			InputBufferContainer.InputTimers[0] = 0.0;
			break;
		}
		case Key_Arrow_Down:
		{
			InputBufferContainer.InputTimers[1] = 0.0;
			break;
		}
		case Key_Arrow_Left:
		{
			InputBufferContainer.InputTimers[2] = 0.0;
			break;
		}
		case Key_Arrow_Right:
		{
			InputBufferContainer.InputTimers[3] = 0.0;
			break;
		}

	}

	
}

fn returns(bool) Input_isKeyHeld parameters(EKeyCode keyToCheckifHeld)
{
	if (ShouldPoll(keyToCheckifHeld))
	{
		if (keyToCheckifHeld == InputBufferContainer.CurrentKey)
		{
			InputBufferContainer.isAnyKeyHeld = true;
		}
	}
	
}

fn returns(bool) ShouldPoll parameters(EKeyCode currentKey)
{
	switch (currentKey)
	{
		case Key_Arrow_Up:
		{
			return Float64_ApproxGreater(InputBufferContainer.InputTimers[0], InputBufferContainer.RefeshInterval) ||
				   Float64_ApproxEqual(InputBufferContainer.InputTimers[0], InputBufferContainer.RefeshInterval);
		}
		case Key_Arrow_Down:
		{
			return Float64_ApproxGreater(InputBufferContainer.InputTimers[1], InputBufferContainer.RefeshInterval) ||
				Float64_ApproxEqual(InputBufferContainer.InputTimers[1], InputBufferContainer.RefeshInterval);
		}
		case Key_Arrow_Left:
		{
			return Float64_ApproxGreater(InputBufferContainer.InputTimers[2], InputBufferContainer.RefeshInterval) ||
				Float64_ApproxEqual(InputBufferContainer.InputTimers[2], InputBufferContainer.RefeshInterval);
		}
		case Key_Arrow_Right:
		{
			return Float64_ApproxGreater(InputBufferContainer.InputTimers[3], InputBufferContainer.RefeshInterval) ||
				Float64_ApproxEqual(InputBufferContainer.InputTimers[3], InputBufferContainer.RefeshInterval);
		}
	}
	
}







