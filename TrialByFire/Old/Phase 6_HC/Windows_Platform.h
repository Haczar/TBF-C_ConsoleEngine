#pragma once



// Windows Library

#include <conio.h>
#include <Windows.h>



#include "LAL.h"



// Macros

#define Console_Cursor_MinSize 1

#define Console_Cursor_NotVisible 0


#define Console_WhiteCell \
FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY



// Enums

enum EKeyCode_Def
{
    Key_NoKey       = 0x00,
    Key_Arrow_Up    = VK_UP,
    Key_Arrow_Down  = VK_DOWN,
    Key_Arrow_Left  = VK_LEFT,
    Key_Arrow_Right = VK_RIGHT,
};

// Aliases (Typedefs)

alias(enum EKeyCode_Def) as EKeyCode;



// Forward Declarations

fn returns(bool) Bind_IOBufferTo_Console parameters(void);

fn returns(bool) RequestConsole parameters(void);

fn returns(bool) Unbind_IOBufferTo_Console parameters(void);

fn returns(bool) GetKeySignal parameters(EKeyCode _key);
