////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: get_operand.c               //
////////////////////////////////////////

#include "../instructions.h"

#include <string.h>

// An operand is usually specified by 4 bits
#define OP_SIZE_MASK 0b0011 // The lower two bits represent the operand size
#define OP_TYPE_MASK 0b1100 // The higher two bits represent the operand type

#define OP_SIZE_8    0b0000
#define OP_SIZE_16   0b0001
#define OP_SIZE_32   0b0010
#define OP_SIZE_64   0b0011

#define OP_TYPE_REGISTER 0b0000
#define OP_TYPE_CONST    0b0100
#define OP_TYPE_MEM_REL  0b1000
#define OP_TYPE_MEM_ABS  0b1100

bool read_const_value(uint8_t addr, Operand* result)
{
	switch (result->size)
	{
	case 1:
		return read_mem_byte(addr, &result->const_8);
	case 2:
		return read_mem(addr, &result->const_16, 2);
	case 4:
		return read_mem(addr, &result->const_32, 4);
	case 8:
		return read_mem(addr, &result->const_64, 8);
	}
	return false;
}

bool read_mem_abs(uint8_t addr, Operand* result)
{
	// The absolute memory address is stored as
	//     s̃õbb'bbbb [B] [ccss'ssss [S]] [O]

	uint8_t base_spec_byte;
	if (!read_mem_byte(addr, &base_spec_byte))
	{
		return false;
	}
	result->length = 1;

	result->mem_abs.is_base_as_val  =  false;
	result->mem_abs.is_scale_as_val =  false;

	result->mem_abs.has_scale       = (base_spec_byte & 0b1000'0000 != 0); // The first bit specifies whether the operand has a scale
	result->mem_abs.has_offset      = (base_spec_byte & 0b0100'0000 != 0); // The second bit specifies whether the operand has an offset
	result->mem_abs.base_reg        =  base_spec_byte & 0b0011'1111;       // The lower 6 bits specify the register with the base value
	if (result->mem_abs.base_reg == 0) // If zero, the base is stored as a value in the next bytes
	{
		result->mem_abs.is_base_as_val = true;
		if (!read_mem(addr + result->length, &result->mem_abs.base_val, sizeof(uintN_t)))
		{
			return false;
		}
		result->length += sizeof(uintN_t);
	}
	else
	{
		result->mem_abs.base_reg |= REG_ADDR_SIZE_N; // Restore the full register address
	}

	// Get the scale if needed
	if (result->mem_abs.has_scale)
	{
		uint8_t scale_spec_byte;
		if (!read_mem_byte(addr + result->length, &scale_spec_byte))
		{
			return false;
		}
		++result->length;
	
		result->mem_abs.scale_multiplier = scale_spec_byte >> 6;          // The higher two bits represent the multiplier in the exponential form
		result->mem_abs.scale_reg        = scale_spec_byte & 0b0011'1111; // The lower 6 bits  represent the register with the scale value
		if (result->mem_abs.scale_reg == 0) // If zero, the scale is stored as a value in the next bytes
		{
			result->mem_abs.is_scale_as_val = true;
			if (!read_mem(addr + result->length, &result->mem_abs.scale_val, sizeof(int_small)))
			{
				return false;
			}
			result->length += sizeof(int_small);
		}
		else
		{
			result->mem_abs.scale_reg |= REG_ADDR_SIZE_SMALL; // Restore the full register address
		}
	}

	// Get the offset if needed
	if (result->mem_abs.has_offset)
	{
		if (!read_mem(addr + result->length, &result->mem_abs.offset, sizeof(int_small)))
		{
			return false;
		}
		result->length += sizeof(int_small);
	}

	return true;
}

// is_size_known is false if the size was figured based on the spec
Operand get_operand_impl(uint8_t spec, uintN_t addr, uint8_t size, bool is_size_known)
{
	Operand result = {
		.type = OPERAND_INVALID,
		.size = size,
		.length = 0
	};
	
	switch (spec & OP_TYPE_MASK)
	{
	case OP_TYPE_REGISTER:
	{
		if ((is_size_known || result.size == 8) && // The size of a register is not specified by the spec, it's always 0011
			read_mem_byte(addr, &result.reg_addr))
		{
			result.size = 1 << (REG_ADDR_GET_SIZE(result.reg_addr));
			result.type = OPERAND_REGISTER;
			result.length = 1;
		}
		break;
	}
	case OP_TYPE_CONST:
	{
		if (read_const_value(addr, &result))
		{
			result.type = OPERAND_CONST;
			result.length = result.size;
		}
		break;
	}
	case OP_TYPE_MEM_REL:
	{
		if (read_mem(addr, &result.mem_rel, sizeof(int_small)))
		{
			result.type = OPERAND_MEM_REL;
			result.length = sizeof(int_small);
		}
		break;
	}
	case OP_TYPE_MEM_ABS:
	{
		if (read_mem_abs(addr, &result))
		{
			result.type = OPERAND_MEM_ABS;
			// result.length is set by read_mem_abs()
		}
		break;
	}
	}
	return result;
}

Operand get_operand(uint8_t spec, uintN_t addr)
{
	return get_operand_impl(spec, addr, 1 << (spec & OP_SIZE_MASK), false);
}

Operand get_operand_with_known_size(uint8_t spec, uint8_t size, uintN_t addr)
{
	return get_operand_impl(spec, addr, size, true);
}

bool extract_operand(const Operand* operand, void* dest, uint8_t size)
{
	switch (operand->type)
	{
	case OPERAND_REGISTER:
	{
		void* reg = REGISTERS[operand->reg_addr];
		if (reg == nullptr)
		{
			return false;
		}
		memcpy(dest, reg, size);
		return true;
	}
	case OPERAND_CONST:
	{
		switch (size)
		{
		case 1:
		{
			*(uint8_t*)dest = operand->const_8;
			return true;
		}
		case 2:
		{
			*(uint16_t*)dest = operand->const_16;
			return true;
		}
		case 4:
		{
			*(uint32_t*)dest = operand->const_32;
			return true;
		}
		case 8:
		{
			*(uint64_t*)dest = operand->const_64;
			return true;
		}
		}
		return false;
	}
	case OPERAND_MEM_REL:
	{
		return read_mem(_IP + operand->mem_rel, dest, size);
	}
	case OPERAND_MEM_ABS:
	{
		uintN_t addr = 0, scale = 0, offset = 0;
		if (operand->mem_abs.is_base_as_val)
		{
			addr = operand->mem_abs.base_val;
		}
		else
		{
			uintN_t* reg = REGISTERS[operand->mem_abs.base_reg];
			if (reg == nullptr)
			{
				return false;
			}
			addr = *reg;
		}

		if (operand->mem_abs.has_scale)
		{
			if (operand->mem_abs.is_scale_as_val)
			{
				scale = operand->mem_abs.scale_val << operand->mem_abs.scale_multiplier;
			}
			else
			{
				uint_small* reg = REGISTERS[operand->mem_abs.scale_reg];
				if (reg == nullptr)
				{
					return false;
				}
				scale = *reg << operand->mem_abs.scale_multiplier;
			}
		}

		if (operand->mem_abs.has_offset)
		{
			offset = operand->mem_abs.offset;
		}

		if (INT_MAX - scale - offset < addr) // Overflow check
		{
			return false;
		}

		return read_mem(addr + scale + offset, dest, size);
	}
	}
	return false;
}
