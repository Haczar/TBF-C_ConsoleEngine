#pragma once

// Windows Library

#include <conio.h>
#include <Windows.h>

#include "LAL.h"
//Aliases (Typedefs)

#define Console_Cursor_MinSize 1
#define Console_Cursor_NotVisible 0
#define Console_WhiteCell \
FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY


//Forward Declarations
fn returns(bool) Bind_IOBufferTo_Console parameters(void);
fn returns(bool) Unbind_IOBufferTo_Console parameters(void);
fn returns(bool) RequestConsole parameters(void);