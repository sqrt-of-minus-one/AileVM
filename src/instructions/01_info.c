////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: 01_info.c                   //
////////////////////////////////////////

#include "../instructions.h"

bool run_info()
{
	_IP += 1;
	
	switch (AH)
	{
	case 0x00:
	{
		AH = SIZE_N;
		break;
	}
	case 0x01:
	{
		AL = VM_ID[0];
		AH = VM_ID[1];
		BL = VM_ID[2];
		BH = VM_ID[3];
		CL = VM_ID[4];
		CH = VM_ID[5];
		DL = VM_ID[6];
		DH = VM_ID[7];
		break;
	}
	case 0x02:
	{
		AX = VM_VER[0];
		BX = VM_VER[1];
		CX = VM_VER[2];
		break;
	}
	}
	return true;
}
