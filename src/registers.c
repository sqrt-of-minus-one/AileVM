////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: registers.c                 //
////////////////////////////////////////

#include "mem.h"

// This table is designed to get a register by its address
// The higher two bits of an address always represent the size of a register
void* const REGISTERS[256] = {
	// 0000
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 0001
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 0010
	&AL,     &BL,     &CL,     &DL,     nullptr, nullptr, nullptr, nullptr,
	&R8L,    &R9L,    &R10L,   &R11L,   &R12L,   &R13L,   &R14L,   &R15L,  
	
	// 0011
	&AH,     &BH,     &CH,     &DH,     nullptr, nullptr, nullptr, nullptr,
	&R8H,    &R9H,    &R10H,   &R11H,   &R12H,   &R13H,   &R14H,   &R15H,  
	
	// 0100
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 0101
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 0110
	&AX,     &BX,     &CX,     &DX,     &SI,     &DI,     &SP,     &BP,    
	&R8W,    &R9W,    &R10W,   &R11W,   &R12W,   &R13W,   &R14W,   &R15W,  
	
	// 0111
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,

#if defined(AILE_X64) || defined(AILE_X32)

	// 1000
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 1001
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 1010
	&EAX,    &EBX,    &ECX,    &EDX,    &ESI,    &EDI,    &ESP,    &EBP,   
	&R8D,    &R9D,    &R10D,   &R11D,   &R12D,   &R13D,   &R14D,   &R15D,  
	
	// 1011
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,

#ifdef AILE_X64
	
	// 1100
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 1101
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	
	// 1110
	&RAX,    &RBX,    &RCX,    &RDX,    &RSI,    &RDI,    &RSP,    &RBP,   
	&R8,     &R9,     &R10,    &R11,    &R12,    &R13,    &R14,    &R15,   

#endif
#endif
	
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
	nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr
};
