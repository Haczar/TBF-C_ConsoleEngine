// Parent Header
#include "Cycler.h"


// Includes
#include "C_STL.h"
#include "Memory.h"
#include "Renderer.h"
#include "Timing.h"



// Static Data

// Private

BSS()
	bool Exist;   // Sentinel value use to exist core engine loop.


// Function

// Public

fn returns(void) Cycler_Lapse parameters(void)
{
	Exist = false;
}

fn returns(void) Cycler_Initialize parameters(void)
{
	while (Exist == true)
	{
		Timing_TakeInitialSnapshot();

		Input_Update();

		// Update UI

		// Update Physics

		// Update State
		
		Stack()
			Ptr(ro TimingData) timingContext = Timing_GetContext();
			Ptr(ro BufferData) inputContext   = Input_GetContext();
			Ptr(ro RendererData) rendererContext = Renderer_GetContext();

		/*Renderer_WriteToPersistentSection(1, L"Tick Elapsed        : %llu" , timingContext->Cycle_TicksElapsed);
		Renderer_WriteToPersistentSection(2, L"Timer      (Seconds): %.7Lf", rendererContext->RefeshTimer);
		Renderer_WriteToPersistentSection(3, L"Delta Time (Seconds): %.7Lf", timingContext->DeltaTime);*/
		Renderer_WriteToPersistentSection(1, L"Current Key  : %i", inputContext->CurrentKey);
		Renderer_WriteToPersistentSection(2, L"Previous Key : %i", inputContext->PreviousKey);
		Renderer_WriteToPersistentSection(3, L"isKeyPressed : %i", inputContext->isAnyKeyPressed);
		Renderer_WriteToPersistentSection(4, L"isKeyHeld    : %i", inputContext->isAnyKeyHeld);

		Renderer_Update();

		Timing_TakeEndingSnapshot();

		Timing_Update();
	}
}

fn returns(void) Cycler_LoadModule parameters(void)
{

	Exist = true;
}