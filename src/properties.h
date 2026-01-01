////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: properties.h                //
////////////////////////////////////////

#pragma once

#include "mem.h"

extern const uint8_t VM_ID[8];
extern const uint16_t VM_VER[3];

typedef enum ESize : uint8_t
{
	SIZE_8  = 0b00,
	SIZE_16 = 0b01,
	SIZE_32 = 0b10,
	SIZE_64 = 0b11,
#ifdef AILE_X64
	SIZE_N  = SIZE_64
#elifdef AILE_X32
	SIZE_N = SIZE_32
#elifdef AILE_X16
	SIZE_N = SIZE_16
#endif
} ESize;

// VM data
typedef struct Properties
{
	uint8_t file_version_major;
	uint8_t file_version_minor;
	uint8_t file_version_patch;
	ESize file_bitness;
} Properties;
extern Properties properties;
