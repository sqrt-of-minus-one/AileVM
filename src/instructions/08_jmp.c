////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: 08_jmp.c                    //
////////////////////////////////////////

#include "../instructions.h"

#define CODE_JMP 0x08

#define FIRST_MASK         0b1100'0000
#define POSITIVITY_MASK    0b0011'0000
#define CONDITION_MASK     0b0000'1111

#define POSITIVITY_FALSE   0b0000'0000
#define POSITIVITY_TRUE    0b0001'0000
#define POSITIVITY_RET     0b0010'0000
#define POSITIVITY_RET_ARG 0b0011'0000

#define CONDITION_NONE     0b0000'0000
#define CONDITION_C        0b0000'0001
#define CONDITION_O        0b0000'0010
#define CONDITION_Z        0b0000'0100
#define CONDITION_S        0b0000'1000
#define CONDITION_BE       0b0000'0101
#define CONDITION_L        0b0000'1010
#define CONDITION_LE       0b0000'1110
#define CONDITION_CX       0b0000'1111

bool read_operands(uint8_t spec, uint8_t size)
{
	Operand first = get_operand_with_known_size((spec & FIRST_MASK) >> 4, size, _IP + 2);
	if (first.type == OPERAND_INVALID || first.size != size)
	{
		return false;
	}
	_IP += 2 + first.length;
	return true;
}

bool read_operands_and_jump(uint8_t spec, bool push_ip)
{
	Operand first = get_operand_with_known_size((spec & FIRST_MASK) >> 4, sizeof(uintN_t), _IP + 2);
	if (first.type == OPERAND_INVALID || first.size != sizeof(uintN_t))
	{
		return false;
	}
	_IP += 2 + first.length;
	return extract_operand(&first, &_IP, sizeof(uintN_t));
}

bool read_operands_and_pop(uint8_t spec)
{
	Operand first = get_operand_with_known_size((spec & FIRST_MASK) >> 4, sizeof(int_small), _IP + 2);
	if (first.type == OPERAND_INVALID || first.size != sizeof(int_small))
	{
		return false;
	}
	_IP += 2 + first.length;
	uint_small delta;
	if (!extract_operand(&first, &delta, sizeof(uint_small)))
	{
		return false;
	}
	return pop(delta);
}

bool run_jmp()
{
	uint8_t spec;
	if (!read_mem_byte(_IP + 1, &spec))
	{
		return false;
	}

	bool condition = true;
	switch (spec & CONDITION_MASK)
	{
	case CONDITION_NONE: // JMP, CALL, RET
	{
		switch (spec & POSITIVITY_MASK)
		{
		case POSITIVITY_TRUE: // CALL
		{
			return read_operands_and_jump(spec, true);
		}
		case POSITIVITY_FALSE: // JMP
		{
			return read_operands_and_jump(spec, true);
		}
		case POSITIVITY_RET:
		{
			if (spec & FIRST_MASK != 0)
			{
				return false;
			}
			popN(&_IP);
			break;
		}
		case POSITIVITY_RET_ARG:
		{
			popN(&_IP);
			return read_operands_and_pop(spec);
		}
		default:
		{
			return false;
		}
		}
		break;
	}
	case CONDITION_C:
	{
		condition = CF_GET;
		break;
	}
	case CONDITION_O:
	{
		condition = OF_GET;
		break;
	}
	case CONDITION_Z:
	{
		condition = ZF_GET;
		break;
	}
	case CONDITION_S:
	{
		condition = SF_GET;
		break;
	}
	case CONDITION_BE:
	{
		condition = CF_GET || ZF_GET;
		break;
	}
	case CONDITION_L:
	{
		condition = SF_GET != OF_GET;
		break;
	}
	case CONDITION_LE:
	{
		condition = (SF_GET != OF_GET) || ZF_GET;
		break;
	}
	case CONDITION_CX:
	{
		condition = _CX != 0;
		break;
	}
	default:
	{
		return false;
	}
	}

	switch (spec & POSITIVITY_MASK)
	{
	case POSITIVITY_FALSE:
	{
		if (!condition)
		{
			return read_operands_and_jump(spec, false);
		}
		break;
	}
	case POSITIVITY_TRUE:
	{
		if (condition)
		{
			read_operands_and_jump(spec, false);
		}
		break;
	}
	default:
	{
		return false;
	}
	}
}
