// Parent Header
#include "Timing.h"
// Includes
#include "Memory.h"
#include "Renderer.h"



// Static Data

// Private

BSS()
	TimingData Timing;

// Function

// Public

fn returns(void) Timing_LoadModule   parameters(void)
{
	Timing.Cycle_TicksElapsed = 0;
	Timing.Cycle_Microseconds = 0.0L;
	Timing.DeltaTime = 0.0L;

	QueryPerformanceFrequency(getAddress(Timing.TimeFrequency));

	return;
}

fn returns(Ptr(ro TimingData)) Timing_GetContext parameters(void)
{
	return getAddress(Timing);
}

fn returns(void) Timing_TakeInitialSnapshot parameters(void)
{
	QueryPerformanceCounter(getAddress(Timing.TimeSnapshot_Initial));
}

fn returns(void) Timing_TakeEndingSnapshot  parameters(void)
{
	QueryPerformanceCounter(getAddress(Timing.TimeSnapshot_End));
}

//Private

fn returns(void) Timing_Update  parameters(void)
{
	Timing.Cycle_TicksElapsed = Timing.TimeSnapshot_End.QuadPart - Timing.TimeSnapshot_Initial.QuadPart;

	Timing.Cycle_Microseconds = (float64)(Timing.Cycle_TicksElapsed * TickToMicroseconds);
	Timing.Cycle_Microseconds = Timing.Cycle_Microseconds / (float64)Timing.TimeFrequency.QuadPart;

	Timing.DeltaTime = (float64)Timing.Cycle_TicksElapsed / (float64)MicrosecondToSecond;

	Renderer_ProcessTiming(Timing.DeltaTime);
}

