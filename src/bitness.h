////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: bitness.h                   //
////////////////////////////////////////

#pragma once

#include <stdint.h>
#include <limits.h>

#define AILE_X64
//#define AILE_X32
//#define AILE_X16


// AileVM can be 16-, 32-, or 64-bit
// AILE_X16, AILE_X32, or AILE_X64 macro should be defined to specify that

#ifndef AILE_X64
#ifndef AILE_X32
#ifndef AILE_X16
#	define AILE_X64
#	warning "No bitness is specified, x64 is assumed (use one of the AILE_X16, AILE_X32, AILE_X64 macros to specify a bitness)"
#endif
#endif
#endif

#ifdef AILE_X64
#	define AILE_BITS 64
#	define AILE_BYTES 8
	typedef uint64_t uintN_t;
	typedef int64_t intN_t;
	typedef uint16_t uint_small;
	typedef int16_t int_small;
#	define UINTN_MAX UINT64_MAX
#	define INTN_MAX INT64_MAX
#	define INTN_MIN INT64_MIN
#elifdef AILE_X32
#	define AILE_BITS 32
#	define AILE_BYTES 4
	typedef uint32_t uintN_t;
	typedef int32_t intN_t;
	typedef uint16_t uint_small;
	typedef int16_t int_small;
#	define UINTN_MAX UINT32_MAX
#	define INTN_MAX INT32_MAX
#	define INTN_MIN INT32_MIN
#elifdef AILE_X16
#	define AILE_BITS 16
#	define AILE_BYTES 2
	typedef uint16_t uintN_t;
	typedef int16_t intN_t;
	typedef uint8_t uint_small;
	typedef int8_t int_small;
#	define UINTN_MAX UINT16_MAX
#	define INTN_MAX INT16_MAX
#	define INTN_MIN INT16_MIN
#endif
