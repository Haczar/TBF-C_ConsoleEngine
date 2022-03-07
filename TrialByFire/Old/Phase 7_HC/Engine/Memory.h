#pragma once


// Includes

#include "LAL.h"
#include "CString.h"
#include "Input.h"
#include "Renderer.h"
#include "Timing.h"



// Public



// Aliases (Typedefs)

alias( Ptr(void) ) as Address;

alias(struct MemoryBlock_Def) as MemoryBlock;

alias(struct MemoryBlockArray_Def) as MemoryBlockArray;

alias(struct AddressTable_Def) as AddressTable;



// Structures

//struct Address_Def
//{
//	Ptr(void) Address;
//};

struct MemoryBlock_Def
{
	Ptr(Address) Location;

	DataSize Size;
};

struct MemoryBlockArray_Def
{
	Ptr( Ptr(MemoryBlock)) Array;

	DataSize Length;
};

struct AddressTable_Def
{
	Ptr(Address) Addresses;

	DataSize TableLength;
};

// Macros

#define GlobalAllocate(_type, _numberToAllocate) \
Internal_GlobalAllocate(sizeof(_type) * _numberToAllocate)

#define ScopedAllocate(_type, _numberToAllocate)  \
Internal_ScopedAllocate(getAddress(scopedMemory), sizeof(_type) * _numberToAllocate)

#define Memory_FormatByFill(_type, _memoryAddress, _fillValue, _sizeOfAllocation) \
Internal_Memory_FormatByFill(_memoryAddress,_fillValue,sizeof(_type) * _sizeOfAllocation)

#define SmartScope              \
{					            \
	MemoryBlock scopedBlock =   \
	{ NULL, { NULL, 0U }, 0U };


#define SmartScope_End                              \
	if (scopedBlock.Address != NULL)                \
	{								                \
		ScopedDeallocate(getAddress(scopedMemory));  \
	}												\
}


// Constant 

#define SizeOf_AllModules \
	sizeof(bool) + SizeOf_CString + SizeOf_InputSystem + SizeOf_Renderer + SizeOf_TimeData 



// Static Data



// Forward Declarations

// C-API

fn returns( Ptr(void) ) AllocateMemory parameters(DataSize _amountToAllocate);
fn returns(void) Deallocate parameters(Ptr(void) _memoryToDeallocate);
fn returns(Ptr(void)) Memory_FormatWithData parameters(Ptr(void) _memoryAddress, ro Ptr(void) _dataSource, DataSize _sizeOfData);
fn returns(Ptr(void)) Internal_Memory_FormatByFill parameters(Ptr(void) _memoryAllocation, sint64 _fillValue, DataSize _sizeOfData);

fn returns(Ptr(MemoryBlock)) MemoryBlockArray_Add parameters(Ptr(MemoryBlockArray) _memoryArray);
fn returns(void) MemoryBlockArray_Deallocate  parameters(Ptr(MemoryBlockArray) _memoryArray);
fn returns(Ptr(MemoryBlock)) MemoryBlockArray_LastEntry parameters(Ptr(MemoryBlockArray) _memoryArray);


// Memory Management

fn returns(Address) Internal_ScopedAllocate(Ptr(MemoryBlockArray) _scopedMemory, DataSize _sizeOfAllocation);
fn returns(void) ScopedDeallocate(Ptr(MemoryBlockArray) _scopedMemory);
fn returns(Address) Internal_GlobalAllocate parameters(DataSize _sizeOfAllocation);
fn returns(void   ) StaticDeallocate        parameters(void                      );



