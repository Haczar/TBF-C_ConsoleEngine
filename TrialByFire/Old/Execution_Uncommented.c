// This is a comment, it lets me put some notes with my code to keep sanity + also help future me remember wtf I was doing here, or someone else.
/*
This is a c file. This where you define whats called "implementation". Or how some part of your program is supposed to work.
There is another file type called a header file that lets you organize your code as well... but, for now lets get the basics down here:

Global Scope: AKA File Scope
This is the raw area of your file.

You can define includes, macros, data, and data types, and functions here.

I'm going to choose to separate my code into my own sectors for the sake of organization.
*/

//Includes

//Standard Library

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

//Windows API

#include <Windows.h>   //High-Performance Timing

////////////////////////////////////////////


//Macro

//Execution

// Entrypoint for app execution.
#define EntryPoint \
main

//The return value for the entrypoint function.
#define ExecFlags \
int

//Success flag used for entrypoint function's return.
#define ExecFlags_Success \
0


//Memory Related

//Stores an address of specified type.
#define address(_type) \
_type*

//Gets the data instance from the specified address
#define data(_address) \
*_address

#define AllocateMemory(_numberOfBytesToAllocate) \
malloc(_numberOfBytesToAllocate)

#define ReallocateMemory(_address, _numberOfBytesToAllocate) \
realloc(_address, _numberOfBytesToAllocate)

#define Deallocate(_address) \
free(_address)


//Data Related

//Alias for the fundamental bool type.
#define bool \
_Bool

#define true \
1

#define false \
0

#define int64 \
long long int

#define uInt \
unsigned int

#define uInt64 \
unsigned long long int

#define floatEP \
long double

#define CSBI \
CONSOLE_SCREEN_BUFFER_INFO


//Function Related

//Used to clearly state a function declare.
#define fn

//Used to clearly state paramater declare.
#define parameters

// States what the function will return data if any. (Put void if you don't want to return data).
#define returns(_returnType) \
_returnType


//Console Related

#define print(_string) \
puts(_string)



//#define alias(_typeToAlias) \
//typedef _typeToAlias

/////////////////////////////////////////////


//Enums

//enum ExecFlags_Enum
//{
//	ExecFlags_Success = 0
//};

////////////////////////////////////////////


//Alias

//alias(enum ExecFlags_Enum) ExecFlags;

//alias(_Bool) bool;

/////////////////////////////////////////////


// EntryPoint: Where you define the execution of your program. (Its also a function. All execution is within some function)

fn returns(ExecFlags) EntryPoint parameters(void)
{
	//Memory_Initialization:

	address(void) memoryBlock;

	#define SizeOf_HelloWorld \
	sizeof(char) * 13

	#define SizeOf_TimeData \
	sizeof(LARGE_INTEGER) * 3 + sizeof(int64) + sizeof(uInt64) + sizeof(floatEP) * 2

	#define SizeOf_ConsoleData \
	sizeof(floatEP) * 2 + sizeof(HANDLE) + sizeof(DWORD) + sizeof(COORD) + sizeof(CSBI) + sizeof(DWORD) + sizeof(bool) * 2 + sizeof(uInt)

	memoryBlock = AllocateMemory( sizeof(bool) + SizeOf_HelloWorld + SizeOf_TimeData + SizeOf_ConsoleData);


	//Memory_Formatting:

	address(bool) exist;

	exist = memoryBlock;

	data(exist) = true;


	address(char) message;

	message = memoryBlock;

	message = message + 1;

	data( (message + 0 ) ) = 'H' ;   //This means the same as data(message) = 'H'; I just did it to keep the whitespace aligned / keep an explicit index of what data block were accessing.
	data( (message + 1 ) ) = 'e' ;   //Since every character data block is one byte, we simply increment the address of our message by how far from the first block it is. 
	data( (message + 2 ) ) = 'l' ;   //We can do this cause we restricted the address of message to be a character.
	data( (message + 3 ) ) = 'l' ;   //Since its restricted to be addresssing a character, every time you do numerical operation on the value of the address,
	data( (message + 4 ) ) = 'o' ;   //your saying to increment the address by the size of a character which is in this case 1 byte.
	data( (message + 5 ) ) = ' ' ;
	data( (message + 6 ) ) = 'W' ;
	data( (message + 7 ) ) = 'o' ;
	data( (message + 8 ) ) = 'r' ;
	data( (message + 9 ) ) = 'l' ;
	data( (message + 10) ) = 'd' ;
	data( (message + 11) ) = '!' ;
	data( (message + 12) ) = '\0';


	//Printing_Message:

	print(message);


	//Getting timers ready.

	address(LARGE_INTEGER) timeSnapshot_Initial;
	address(LARGE_INTEGER) timeSnapshot_End    ;
	address(LARGE_INTEGER) timeFrequency       ;

	address(int64 ) loopTime_Elapsed;
	address(uInt64) cycleCount      ;

	address(floatEP) cycle_MicroInterval;
	address(floatEP) deltaTime          ;   //In Seconds

	timeSnapshot_Initial = (address(LARGE_INTEGER))(message              + 13);
	timeSnapshot_End     =                         (timeSnapshot_Initial + 1 );
	timeFrequency        =                         (timeSnapshot_End     + 1 );
	loopTime_Elapsed     = (address(int64        ))(timeFrequency        + 1 );
	cycleCount           = (address(uInt64       ))(loopTime_Elapsed     + 1 );
	cycle_MicroInterval  = (address(floatEP      ))(cycleCount           + 1 );
	deltaTime            = (address(floatEP      ))(cycle_MicroInterval  + 1 );

	data(loopTime_Elapsed) = 0  ;
	data(cycleCount      ) = 0U ;
	data(deltaTime       ) = 0.0;

	QueryPerformanceFrequency(timeFrequency);

	#define TickToMicroseconds \
	1000000

	#define LoopTime_ToSeconds \
	100000


	//Getting Console Ready

	address(floatEP) consoleRefreshTimer   ;
	address(floatEP) conosleRefreshInterval;

	consoleRefreshTimer    = (deltaTime           + 1);
	conosleRefreshInterval = (consoleRefreshTimer + 1);

	data(consoleRefreshTimer   ) =     0.0;
	data(conosleRefreshInterval) = 10000.0;


	//Clear Console Routine

	address(HANDLE) consoleHandle    ;
	address(DWORD ) charactersWritten;
	address(COORD ) screenCoordinates;   //Home for the cursor.
	address(CSBI  ) csbi_instance    ;
	address(DWORD ) consoleSize      ;
	address(bool  ) fillResult       ;
	address(bool  ) attributeResult  ;
	address(uInt  ) returnRoutes     ;

	consoleHandle     = (address(HANDLE))(conosleRefreshInterval  + 1);
	charactersWritten = (address(DWORD ))(consoleHandle           + 1);
	screenCoordinates = (address(COORD ))(charactersWritten       + 1);
	csbi_instance     = (address(CSBI  ))(screenCoordinates       + 1);
	consoleSize       = (address(DWORD ))(csbi_instance           + 1);
	fillResult        = (address(bool  ))(consoleSize             + 1);
	attributeResult   = (address(bool  ))(fillResult              + 1);
	returnRoutes      = (address(uInt  ))(attributeResult         + 1);

	screenCoordinates->X = 0;
	screenCoordinates->Y = 0;

	data(consoleHandle) = GetStdHandle(STD_OUTPUT_HANDLE);
	data(returnRoutes ) = 0                              ;

	#define ClearConsoleReturn_CoreEngineLoop \
	0

	goto Skip_Section_ClearConsole;

	ClearConsole:

	if (GetConsoleScreenBufferInfo(data(consoleHandle), csbi_instance))
	{
		data(consoleSize) = csbi_instance->dwSize.X * csbi_instance->dwSize.Y;

		data(fillResult) = \
			!FillConsoleOutputCharacter
			(
				data(consoleHandle    ),   //Handle to console screen buffer.
				(TCHAR)' '             ,   //Character to write to the buffer.
				data(consoleSize      ),   //Number of cells to write.
				data(screenCoordinates),   //Coordinates of the first cell.
			    charactersWritten   //Receive number of character written.
			);

		if (data(fillResult) == true)
		{
			goto ClearConsole_Return;
		}

		//Get the number of character cells in the current buffer.
		if (!GetConsoleScreenBufferInfo(data(consoleHandle), csbi_instance))
		{
			goto ClearConsole_Return;
		}

		//Set the buffer's attributes accordingly.
		data(attributeResult) = \
			!FillConsoleOutputAttribute
			(
				data(consoleHandle)       ,   //Handle to console screen buffer.
				csbi_instance->wAttributes,   //Character attributes to use.
				data(consoleSize      )   ,   //Number of cells to set attribute.
				data(screenCoordinates)   ,   //Coordinates of first cell.
			    charactersWritten       //Receive number of characters written.
			);

		if (data(attributeResult))
		{
			goto ClearConsole_Return;
		}

		SetConsoleCursorPosition(data(consoleHandle), data(screenCoordinates));   //Put the cursor at its home coordinates.
		
		//Successfuly cleared. Returning to originating routine.
	}

	ClearConsole_Return:
	
	if (data(returnRoutes) == ClearConsoleReturn_CoreEngineLoop)
	{
		goto CoreEngineLoop_ClearConsoleReturn;
	}

	Skip_Section_ClearConsole:


	Core_Engine_Loop:

	//Conditional for loop
	if (data(exist) == true)
	{
		data(cycleCount) = data(cycleCount) + 1;

		QueryPerformanceCounter(timeSnapshot_Initial);

		//Engine Cycle: Start

		//Update Input

		//Update UI

		//Update Physics

		//Update State
		
		//Update Render

		if (data(consoleRefreshTimer) >= data(conosleRefreshInterval))
		{
			//Call clear console.
			goto ClearConsole;

			CoreEngineLoop_ClearConsoleReturn:

			printf("Cycle Count         : %lld \n", data(cycleCount         ));
			printf("Micro Time          : %lf  \n", data(cycle_MicroInterval));
			printf("Delta Time (Seconds): %lf  \n", data(deltaTime          ));

			data(consoleRefreshTimer) = 0.0;
		}


		//Engine Cycle: End

		QueryPerformanceCounter(timeSnapshot_End);


		//Time Calculations

		data(loopTime_Elapsed) = timeSnapshot_End->QuadPart - timeSnapshot_Initial->QuadPart;

		data(cycle_MicroInterval) = (floatEP)(data(loopTime_Elapsed * TickToMicroseconds)) / (floatEP)timeFrequency->QuadPart;
		data(deltaTime          ) = (floatEP) data(cycle_MicroInterval)                    / (floatEP)LoopTime_ToSeconds     ;

		data(consoleRefreshTimer) = data(consoleRefreshTimer) + data(cycle_MicroInterval);

		goto Core_Engine_Loop;
	}

	//End_Of_Loop:


	//Deallocation:

	Deallocate(memoryBlock);
}

//////////////////////////////////////////////