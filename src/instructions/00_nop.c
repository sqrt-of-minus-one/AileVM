////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: 00_nop.c                    //
////////////////////////////////////////

#include "../instructions.h"

bool run_nop()
{
	_IP += 1;
	return true;
}
