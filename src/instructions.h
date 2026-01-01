////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: instructions.h              //
////////////////////////////////////////

#pragma once

#include "mem.h"
#include "properties.h"

// Instruction codes

#define CODE_NOP  0x00
#define CODE_INFO 0x01
#define CODE_JMP  0x08

#define CODE_MOV  0x10
#define CODE_XCHG 0x11
#define CODE_EXTZ 0x12
#define CODE_EXTS 0x13
#define CODE_BIT  0x14
#define CODE_IN   0x18
#define CODE_TIN  0x19
#define CODE_OUT  0x1A
#define CODE_TOUT 0x1B

#define CODE_ADD  0x20
#define CODE_SUB  0x21
#define CODE_MUL  0x22
#define CODE_DIV  0x23
#define CODE_NOT  0x24
#define CODE_AND  0x25
#define CODE_SHL  0x26
#define CODE_SHR  0x27

#define CODE_END  0xFE
#define CODE_ERR  0xFF

// The instructions themselves

bool run_nop();
bool run_info();
bool run_jmp();

bool run_mov();
bool run_xchg();
bool run_extz();
bool run_exts();
bool run_bit();
bool run_in();
bool run_tin();
bool run_out();
bool run_tout();

bool run_add();
bool run_sub();
bool run_mul();
bool run_div();
bool run_not();
bool run_and();
bool run_shl();
bool run_shr();

bool run_end();
bool run_err();

// Some utilities to work with operands

typedef enum EOperandType : uint8_t
{
	OPERAND_INVALID,
	OPERAND_REGISTER,
	OPERAND_CONST,
	OPERAND_MEM_REL,
	OPERAND_MEM_ABS
} EOperandType;

typedef struct OperandMemAbs
{
	struct
	{
		bool has_scale       : 1;
		bool has_offset      : 1;
		bool is_base_as_val  : 1; // If the base address is stored as a value (or as a register)
		bool is_scale_as_val : 1; // If the scale is stored as a value (or as a register)
	};
	union // The base (is stored either as a register or as a value)
	{
		uint8_t base_reg;
		uintN_t base_val;
	};
	uint8_t scale_multiplier; // The multiplier in the exponential form
	union // The scale (is stored either as a register or as a value)
	{
		uint8_t scale_reg;
		int_small scale_val;
	};
	int_small offset; // The offset
} OperandMemAbs;

typedef struct Operand
{
	EOperandType type;
	uint8_t size;      // The size of the data that the operand represents
	uint8_t length;    // The size of the operand data stored in the memory as a part of the instruction
	union // Different operand types depending on the type and size values
	{
		uint8_t reg_addr;
		uint8_t const_8;
		uint16_t const_16;
		uint32_t const_32;
		uint64_t const_64;
		int_small mem_rel;
		OperandMemAbs mem_abs;
	};
} Operand;

// Define the operand data based on the given spec
Operand get_operand(uint8_t spec, uintN_t addr);
Operand get_operand_with_known_size(uint8_t spec, uint8_t size, uintN_t addr);

// Get the actual operand value
bool extract_operand(const Operand* operand, void* dest, uint8_t size);
