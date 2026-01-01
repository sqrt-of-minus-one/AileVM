////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: run.c                       //
////////////////////////////////////////

#include "run.h"

#include "mem.h"
#include "properties.h"

#include "instructions.h"

#define RUN(command) if (!command()) return false;

bool run()
{
	while (true)
	{
		if (!is_addr_in_mem(_IP))
		{
			return false;
		}

		switch (MEM[_IP])
		{
		case CODE_NOP:
			RUN(run_nop);
			break;
		case CODE_INFO:
			RUN(run_info);
			break;
		case CODE_JMP:
			RUN(run_jmp);
			break;
		default:
		{
			return false;
		}
		}
	}
}
