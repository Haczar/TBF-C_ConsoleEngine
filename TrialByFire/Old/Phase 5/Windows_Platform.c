//Parent Header
#include "C_STL.h"
#include "Windows_Platform.h"
#include "Execution.h"
#include "CString.h"
#include "LAL.h"


//Macros
#define STANDARD_INPUT stdin
#define STANDARD_OUTPUT stdout
#define STANDARD_ERROR stderr



//Static Data
Data()
	CTS_CString SConsole_In = "CONIN$";
	CTS_CString SConsole_Out = "CONOUT$";
	CTS_CString SConsole_Null = "NUL:";

	CTS_CString SReadCode = "r";
	CTS_CString SWriteCode = "w";


//Functions

//Public

fn returns(bool) Bind_IOBufferTo_Console   parameters(void)
{
	Stack()
		bool result = true;
	Ptr(FILE) dummyFile = NULL;

	freopen_s(getAddress(dummyFile), SConsole_In, SReadCode, STANDARD_INPUT);
	freopen_s(getAddress(dummyFile), SConsole_Out, SWriteCode, STANDARD_OUTPUT);
	freopen_s(getAddress(dummyFile), SConsole_Out, SWriteCode, STANDARD_ERROR);

	if (GetStdHandle(STD_INPUT_HANDLE) != INVALID_HANDLE_VALUE)
	{
		if (freopen_s(getAddress(dummyFile), SConsole_In, SReadCode, STANDARD_INPUT) != 0)
		{
			return false;
		}
		else
		{
			setvbuf(STANDARD_INPUT, NULL, _IONBF,0);
		}
	}

	if (GetStdHandle(STD_OUTPUT_HANDLE) != INVALID_HANDLE_VALUE)
	{
		if (freopen_s(getAddress(dummyFile), SConsole_Out, SWriteCode, STANDARD_OUTPUT) != 0)
		{
			return false;
		}
		else
		{
			setvbuf(STANDARD_OUTPUT, NULL, _IONBF, 0);
		}
	}

	if (GetStdHandle(STD_ERROR_HANDLE) != INVALID_HANDLE_VALUE)
	{
		if (freopen_s(getAddress(dummyFile), SConsole_Out, SWriteCode, STANDARD_ERROR) != 0)
		{
			return false;
		}
		else
		{
			setvbuf(STANDARD_OUTPUT, NULL, _IONBF, 0);
		}
	}

	return true;
}

fn returns(bool) Unbind_IOBufferTo_Console parameters(void)
{
	Stack()
		bool result = true;
	Ptr(FILE) dummyFile;

	if (freopen_s(getAddress(dummyFile), SConsole_Null, SReadCode, STANDARD_INPUT) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(STANDARD_INPUT, NULL, _IONBF, 0);
	}

	if (freopen_s(getAddress(dummyFile), SConsole_Null, SWriteCode, STANDARD_OUTPUT) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(STANDARD_OUTPUT, NULL, _IONBF, 0);
	}

	if (freopen_s(getAddress(dummyFile), SConsole_Null, SWriteCode, STANDARD_ERROR) != 0)
	{
		result = false;
	}
	else
	{
		setvbuf(STANDARD_ERROR, NULL, _IONBF, 0);
	}

	return result;

}

fn returns(bool) RequestConsole            parameters(void)
{
	return AllocConsole();
}

//Private

int WINAPI wWinMain parameters(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	EntryPoint();
	return 0;
}
