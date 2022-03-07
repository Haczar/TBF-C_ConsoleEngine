// Parent Header
#include "State_Intro.h"
#include "Memory.h"
#include "Renderer.h"
#include "Cycler.h"
#include "CString.h"



// Intro State
BSS()
	StateObj IntroState;
	RendererData RendererContext;
	

Data()
	CTS_CWString Title = L"Trial By Fire Engine: C";
	CTS_CWString EngineVersion = L"Phase 7";

	TimerData Timer_WholeIntro;

	TimerData Timer_FadeIntro;
	TimerData Timer_TillIntroTextStandard;
	TimerData Timer_FillIntro;
	TimerData Timer_FadeIntroX2;

	sGlobal bool
		//game
		showGameTitle = false,
		showGameVersion = false,
		showTitleFade = true;
		showVersionFade = true;
		//log
		LogTitle = true,
		LogVersion = true,
		LogFade = true,
		LogEnd = true;


// Functions

// Class Public

fn returns(void) IntroState_Load parameters(void)
{
	Renderer_WriteToLog(L"Intro State: Loaded");

	Timer_WholeIntro.EndTime = 4.5L;
	Timer_FadeIntro.EndTime = 0.5L;
	Timer_TillIntroTextStandard.EndTime = 1.0L;
	Timer_FadeIntroX2.EndTime = 4.0L;
}

fn returns(void) IntroState_Unload parameters(void)
{

	Renderer_WriteToLog(L"Intro State: Unloaded");
}

fn returns(void) IntroState_Update parameters(void)
{
	Timer_Tick(getAddress(Timer_WholeIntro));
	Timer_Tick(getAddress(Timer_FadeIntro));

	//Title and Version should show up in faded text
	if (Timer_Ended(getAddress(Timer_FadeIntro)))
	{
		if (LogTitle)
		{
			Renderer_WriteToLog(L"Title and version should show up faded...");
			//_HC
			showGameTitle = true;
			showGameVersion = true;

			showTitleFade = true;
			showVersionFade = true;

			LogTitle = false;
		}

	}
	Timer_Tick(getAddress(Timer_TillIntroTextStandard));


	if (Timer_Ended(getAddress(Timer_TillIntroTextStandard)))
	{
		if (LogVersion)
		{
			Renderer_WriteToLog(L"Title and version should show up standard...");
			//_HC
			showGameTitle = true;
			showGameVersion = true;
			
			showTitleFade = false;
			showVersionFade = false;

			LogVersion = false;
		}
	}

	Timer_Tick(getAddress(Timer_FadeIntroX2));

	if (LogFade && Timer_Ended(getAddress(Timer_FadeIntroX2)))
	{
		Renderer_WriteToLog(L"Title and version should show up faded again...");

		//SET THE RIGHT SHIT
		showGameTitle = true;
		showGameVersion = true;
		
		showTitleFade = true;
		showVersionFade = true;

		LogTitle = false;	
		LogFade = false;
	}

	if (LogEnd && Timer_Ended(getAddress(Timer_WholeIntro)))
	{
		Renderer_WriteToLog(L"Intro Ends now. Title and version gone.");

		showGameTitle = false;
		showGameVersion = false;

		Renderer_ClearGameSection();
		
		LogEnd = false;

		State_LoadGame();
	}
}

fn returns(void) IntroState_Render parameters(void)
{
	if (showGameTitle)
	{
		Renderer_WriteToTitleGameSection(ERenderer_TitleLine, Title);

		//Renderer_WriteToLog(L"Title is written.");
	}


	if (showGameVersion)
	{
		Renderer_WriteToTitleGameSection(ERenderer_VersionLine, EngineVersion);
		//Renderer_WriteToLog(L"Version is written.");
	}


	if (showTitleFade && showVersionFade)
	{
		Renderer_FormatTitleGameSectionLine(ERenderer_GameFadeText, ERenderer_TitleLine);
		Renderer_FormatTitleGameSectionLine(ERenderer_GameFadeText, ERenderer_VersionLine);
	}
}


// Public

fn returns(Ptr(StateObj)) GetIntroState parameters(void)
{
	Stack()

		sGlobal firstGet = true;

	if (firstGet)
	{
		IntroState.Load = getAddress(IntroState_Load);
		IntroState.Unload = getAddress(IntroState_Unload);
		IntroState.Update = getAddress(IntroState_Update);
		IntroState.Render = getAddress(IntroState_Render);

		firstGet = false;
	}

	return getAddress(IntroState);
}

