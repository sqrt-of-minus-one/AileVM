////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: mem.h                       //
////////////////////////////////////////

#pragma once

#include "bitness.h"

#include <stdbit.h>

// AileVM is always little-endian, but the virtual machine can be built on a big-endian system
// Data in MEM is always supposed to be little-endian; other values are native-endian
#if __STDC_ENDIAN_NATIVE__ == __STDC_ENDIAN_LITTLE__
#	define LITTLE_ENDIAN
#elif __STDC_ENDIAN_NATIVE__ == __STDC_ENDIAN_BIG__
#	define BIG_ENDIAN
#else // If you're neither little- nor big-endian... what are you?
#	error "Only little- and big-endian are supported"
#endif

// Unions allowing to access individual parts of integers

typedef union Int16
{
	uint16_t    value;
	uint16_t  word[1];
	uint8_t   byte[2];
} Int16;

typedef union Int32
{
	uint32_t    value;
	uint32_t dword[1];
	uint16_t  word[2];
	uint8_t   byte[4];
} Int32;

typedef union Int64
{
	uint64_t    value;
	uint64_t qword[1];
	uint32_t dword[2];
	uint16_t  word[4];
	uint8_t   byte[8];
} Int64;

#ifdef AILE_X64
	typedef Int64 IntN;
#elifdef AILE_X32
	typedef Int32 IntN;
#elifdef AILE_X16
	typedef Int16 IntN;
#endif

// Indices of lower parts of integers
#ifdef LITTLE_ENDIAN
#	define QWORD_INDEX 0
#	define DWORD_INDEX 0
#	define  WORD_INDEX 0
#	define LBYTE_INDEX 0
#	define HBYTE_INDEX 1
#elifdef BIG_ENDIAN
#	define QWORD_INDEX 0
#	define DWORD_INDEX 1
#	define  WORD_INDEX 3
#	define LBYTE_INDEX 7
#	define HBYTE_INDEX 6
#endif

#define QWORD qword[QWORD_INDEX]
#define DWORD dword[DWORD_INDEX]
#define  WORD  word[ WORD_INDEX]
#define LBYTE  byte[LBYTE_INDEX]
#define HBYTE  byte[HBYTE_INDEX]

#define REG_ADDR_SIZE_MASK 0b1100'0000 // The two higher bits of a register address always represent the size of the register
#define REG_ADDR_GET_SIZE(addr) (addr >> 6) // Get the size in the exponential form
#ifdef AILE_X64
#	define REG_ADDR_SIZE_N     0b1100'0000 // 64-bit
#	define REG_ADDR_SIZE_SMALL 0b0100'0000 // 16-bit
#elifdef AILE_X32
#	define REG_ADDR_SIZE_N     0b1000'0000 // 32-bit
#	define REG_ADDR_SIZE_SMALL 0b0100'0000 // 16-bit
#elifdef AILE_X16
#	define REG_ADDR_SIZE_N     0b0100'0000 // 16-bit
#	define REG_ADDR_SIZE_SMALL 0b0000'0000 // 8-bit
#endif

// Registers
extern Int64 REG_FLAGS, REG_IP,
	REG_AX , REG_BX , REG_CX , REG_DX ,
	REG_BP , REG_SP , REG_SI , REG_DI ,
	REG_R8 , REG_R9 , REG_R10, REG_R11,
	REG_R12, REG_R13, REG_R14, REG_R15;
extern void* const REGISTERS[256]; // The registers table allowing to get a register by its address

// Registers and their parts

#define RFLAGS REG_FLAGS.QWORD
#define RIP    REG_IP   .QWORD
#define RAX    REG_AX   .QWORD
#define RBX    REG_BX   .QWORD
#define RCX    REG_CX   .QWORD
#define RDX    REG_DX   .QWORD
#define RBP    REG_BP   .QWORD
#define RSP    REG_SP   .QWORD
#define RSI    REG_SI   .QWORD
#define RDI    REG_DI   .QWORD
#define R8     REG_R8   .QWORD
#define R9     REG_R9   .QWORD
#define R10    REG_R10  .QWORD
#define R11    REG_R11  .QWORD
#define R12    REG_R12  .QWORD
#define R13    REG_R13  .QWORD
#define R14    REG_R14  .QWORD
#define R15    REG_R15  .QWORD

#define EFLAGS REG_FLAGS.DWORD
#define EIP    REG_IP   .DWORD
#define EAX    REG_AX   .DWORD
#define EBX    REG_BX   .DWORD
#define ECX    REG_CX   .DWORD
#define EDX    REG_DX   .DWORD
#define EBP    REG_BP   .DWORD
#define ESP    REG_SP   .DWORD
#define ESI    REG_SI   .DWORD
#define EDI    REG_DI   .DWORD
#define R8D    REG_R8   .DWORD
#define R9D    REG_R9   .DWORD
#define R10D   REG_R10  .DWORD
#define R11D   REG_R11  .DWORD
#define R12D   REG_R12  .DWORD
#define R13D   REG_R13  .DWORD
#define R14D   REG_R14  .DWORD
#define R15D   REG_R15  .DWORD

#define FLAGS  REG_FLAGS. WORD
#define IP     REG_IP   . WORD
#define AX     REG_AX   . WORD
#define BX     REG_BX   . WORD
#define CX     REG_CX   . WORD
#define DX     REG_DX   . WORD
#define BP     REG_BP   . WORD
#define SP     REG_SP   . WORD
#define SI     REG_SI   . WORD
#define DI     REG_DI   . WORD
#define R8W    REG_R8   . WORD
#define R9W    REG_R9   . WORD
#define R10W   REG_R10  . WORD
#define R11W   REG_R11  . WORD
#define R12W   REG_R12  . WORD
#define R13W   REG_R13  . WORD
#define R14W   REG_R14  . WORD
#define R15W   REG_R15  . WORD

#define HFLAGS REG_FLAGS.HBYTE
#define AH     REG_AX   .HBYTE
#define BH     REG_BX   .HBYTE
#define CH     REG_CX   .HBYTE
#define DH     REG_DX   .HBYTE
#define R8H    REG_R8   .HBYTE
#define R9H    REG_R9   .HBYTE
#define R10H   REG_R10  .HBYTE
#define R11H   REG_R11  .HBYTE
#define R12H   REG_R12  .HBYTE
#define R13H   REG_R13  .HBYTE
#define R14H   REG_R14  .HBYTE
#define R15H   REG_R15  .HBYTE

#define LFLAGS REG_FLAGS.LBYTE
#define AL     REG_AX   .LBYTE
#define BL     REG_BX   .LBYTE
#define CL     REG_CX   .LBYTE
#define DL     REG_DX   .LBYTE
#define R8L    REG_R8   .LBYTE
#define R9L    REG_R9   .LBYTE
#define R10L   REG_R10  .LBYTE
#define R11L   REG_R11  .LBYTE
#define R12L   REG_R12  .LBYTE
#define R13L   REG_R13  .LBYTE
#define R14L   REG_R14  .LBYTE
#define R15L   REG_R15  .LBYTE

#ifdef AILE_X64
#	define _FLAGS RFLAGS
#	define _IP    RIP
#	define _AX    RAX
#	define _BX    RBX
#	define _CX    RCX
#	define _DX    RDX
#	define _BP    RBP
#	define _SP    RSP
#	define _SI    RSI
#	define _DI    RDI
#	define _R8    R8
#	define _R9    R9
#	define _R10   R10
#	define _R11   R11
#	define _R12   R12
#	define _R13   R13
#	define _R14   R14
#	define _R15   R15
#elifdef AILE_X32
#	define _FLAGS EFLAGS
#	define _IP    EIP
#	define _AX    EAX
#	define _BX    EBX
#	define _CX    ECX
#	define _DX    EDX
#	define _BP    EBP
#	define _SP    ESP
#	define _SI    ESI
#	define _DI    EDI
#	define _R8    R8D
#	define _R9    R9D
#	define _R10   R10D
#	define _R11   R11D
#	define _R12   R12D
#	define _R13   R13D
#	define _R14   R14D
#	define _R15   R15D
#elifdef AILE_X16
#	define _FLAGS FLAGS
#	define _IP    IP
#	define _AX    AX
#	define _BX    BX
#	define _CX    CX
#	define _DX    DX
#	define _BP    BP
#	define _SP    SP
#	define _SI    SI
#	define _DI    DI
#	define _R8    R8W
#	define _R9    R9W
#	define _R10   R10W
#	define _R11   R11W
#	define _R12   R12W
#	define _R13   R13W
#	define _R14   R14W
#	define _R15   R15W
#endif

#ifdef LITTLE_ENDIAN
#	define CF_BYTE_INDEX 0
#	define OF_BYTE_INDEX 0
#	define SF_BYTE_INDEX 0
#	define ZF_BYTE_INDEX 0
#elifdef BIG_ENDIAN
#	define CF_BYTE_INDEX 7
#	define OF_BYTE_INDEX 7
#	define SF_BYTE_INDEX 7
#	define ZF_BYTE_INDEX 7
#endif

// Flags register
#define ONE 0b0000'0001u

#define CF_BYTE REG_FLAGS.byte[CF_BYTE_INDEX]
#define OF_BYTE REG_FLAGS.byte[OF_BYTE_INDEX]
#define SF_BYTE REG_FLAGS.byte[SF_BYTE_INDEX]
#define ZF_BYTE REG_FLAGS.byte[ZF_BYTE_INDEX]

#define CF_INDEX 0
#define OF_INDEX 1
#define SF_INDEX 2
#define ZF_INDEX 3

#define CF_1_MASK (ONE << CF_INDEX)
#define OF_1_MASK (ONE << OF_INDEX)
#define SF_1_MASK (ONE << SF_INDEX)
#define ZF_1_MASK (ONE << ZF_INDEX)
#define CF_0_MASK (~CF_1_MASK)
#define OF_0_MASK (~OF_1_MASK)
#define SF_0_MASK (~SF_1_MASK)
#define ZF_0_MASK (~ZF_1_MASK)

#define CF (CF_BYTE & CF_1_MASK)
#define OF (OF_BYTE & OF_1_MASK)
#define SF (SF_BYTE & SF_1_MASK)
#define ZF (ZF_BYTE & ZF_1_MASK)

#define CF_GET (CF >> CF_INDEX)
#define OF_GET (OF >> OF_INDEX)
#define SF_GET (SF >> SF_INDEX)
#define ZF_GET (ZF >> ZF_INDEX)

#define CF_SET (CF_BYTE |= CF_1_MASK)
#define OF_SET (OF_BYTE |= OF_1_MASK)
#define SF_SET (SF_BYTE |= SF_1_MASK)
#define ZF_SET (ZF_BYTE |= ZF_1_MASK)

#define CF_CLEAR (CF_BYTE &= CF_0_MASK)
#define OF_CLEAR (OF_BYTE &= OF_0_MASK)
#define SF_CLEAR (SF_BYTE &= SF_0_MASK)
#define ZF_CLEAR (ZF_BYTE &= ZF_0_MASK)

#define CF_MODIFY(value) (CF_BYTE = CF_BYTE & CF_0_MASK | (value & ONE) << CF_INDEX)
#define OF_MODIFY(value) (OF_BYTE = OF_BYTE & OF_0_MASK | (value & ONE) << OF_INDEX)
#define SF_MODIFY(value) (SF_BYTE = SF_BYTE & SF_0_MASK | (value & ONE) << SF_INDEX)
#define ZF_MODIFY(value) (ZF_BYTE = ZF_BYTE & ZF_0_MASK | (value & ONE) << ZF_INDEX)

// Memory
extern uint8_t* MEM;
extern uintN_t MEM_SIZE;

// Check if an address is valid
bool is_addr_in_mem(uintN_t addr);
bool is_range_in_mem(uintN_t addr, uintN_t size);

// Read/write data; return false if the address is invalid
bool read_mem_byte(uintN_t addr, uint8_t* dest);
bool read_mem(uintN_t addr, void* dest, uintN_t size);
bool write_mem_byte(uintN_t addr, const uint8_t* value);
bool write_mem(uintN_t addr, const void* value, uintN_t size);

// Push data in the stack (use _SP and _BP)
// If the new value of the _SP would be out of memory range, return false without changing anything
bool push8(uint8_t val);
bool push16(uint16_t val);
bool push32(uint32_t val);
bool push64(uint64_t val);
bool pushN(uintN_t val);

// Pop data from the stack (use _SP and _BP)
// If the current vaule of the _SP is out of memory range, return false without changing anything
bool pop8(uint8_t* val);
bool pop16(uint16_t* val);
bool pop32(uint32_t* val);
bool pop64(uint64_t* val);
bool popN(uintN_t* val);
bool pop(uintN_t n); // Just changes the _SP by n
