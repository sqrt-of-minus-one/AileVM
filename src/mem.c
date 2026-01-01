////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: mem.c                       //
////////////////////////////////////////

#include "mem.h"

#include <string.h>

Int64 REG_FLAGS, REG_IP,
	REG_AX , REG_BX , REG_CX , REG_DX ,
	REG_BP , REG_SP , REG_SI , REG_DI ,
	REG_R8 , REG_R9 , REG_R10, REG_R11,
	REG_R12, REG_R13, REG_R14, REG_R15;

uint8_t* MEM = nullptr;
uintN_t MEM_SIZE = 0;

// Just copy for little-endian
// Copy and revert byte order for big-endian
void* memcpy_endian(void* dest, const void* src, size_t n)
{
#ifdef LITTLE_ENDIAN
	return memcpy(dest, src, n);
#elifdef BIG_ENDIAN
	for (int i = 0; i < n; ++i)
	{
		((unsigned char*)dest)[n - 1 - i] = ((const unsigned char*)src)[i];
	}
	return dest;
#endif
}

bool is_addr_in_mem(uintN_t addr)
{
	return addr < MEM_SIZE;
}

bool is_range_in_mem(uintN_t addr, uintN_t size)
{
	return
		UINTN_MAX - size >= addr && // Overflow check
		addr + size <= MEM_SIZE;
}

bool read_mem_byte(uintN_t addr, uint8_t* dest)
{
	if (!is_addr_in_mem(addr))
	{
		return false;
	}
	*dest = MEM[addr];
	return true;
}

bool read_mem(uintN_t addr, void* dest, uintN_t size)
{
	if (!is_range_in_mem(addr, size))
	{
		return false;
	}
	memcpy_endian(dest, &MEM[addr], size);
	return true;
}

bool write_mem_byte(uintN_t addr, const uint8_t* value)
{
	if (!is_addr_in_mem(addr))
	{
		return false;
	}
	MEM[addr] = *value;
	return true;
}

bool write_mem(uintN_t addr, const void* value, uintN_t size)
{
	if (!is_range_in_mem(addr, size))
	{
		return false;
	}
	memcpy_endian(&MEM[addr], value, size);
	return true;
}

#define PUSH_N                                   \
	_SP -= sizeof(val);                          \
	if (!is_range_in_mem(_SP, sizeof(val)))      \
	{                                            \
		_SP += sizeof(val);                      \
		return false;                            \
	}                                            \
	memcpy_endian(&MEM[_SP], &val, sizeof(val)); \
	return true

#define POP_N                                    \
	if (!is_range_in_mem(_SP, sizeof(*val)))     \
		return false;                            \
	memcpy_endian(val, &MEM[_SP], sizeof(*val)); \
	_SP += sizeof(*val);                         \
	return true

bool push8(uint8_t val)
{
	PUSH_N;
}

bool push16(uint16_t val)
{
	PUSH_N;
}

bool push32(uint32_t val)
{
	PUSH_N;
}

bool push64(uint64_t val)
{
	PUSH_N;
}

bool pushN(uintN_t val)
{
	PUSH_N;
}

bool pop8(uint8_t* val)
{
	POP_N;
}

bool pop16(uint16_t* val)
{
	POP_N;
}

bool pop32(uint32_t* val)
{
	POP_N;
}

bool pop64(uint64_t* val)
{
	POP_N;
}

bool popN(uintN_t* val)
{
	POP_N;
}

bool pop(uintN_t n)
{
	if (!is_range_in_mem(_SP, n))
	{
		return false;
	}
	_SP += n;
	return true;
}
