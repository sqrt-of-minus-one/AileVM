////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: mem.c                       //
////////////////////////////////////////

#include "mem.h"

Int64 REG_FLAGS, REG_IP,
	REG_AX , REG_BX , REG_CX , REG_DX ,
	REG_BP , REG_SP , REG_SI , REG_DI ,
	REG_R8 , REG_R9 , REG_R10, REG_R11,
	REG_R12, REG_R13, REG_R14, REG_R15;

uint8_t* MEM = nullptr;
uintN_t MEM_SIZE = 0;

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
