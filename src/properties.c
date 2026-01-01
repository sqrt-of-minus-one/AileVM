////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: properties.c                //
////////////////////////////////////////

#include "properties.h"

const uint8_t VM_ID[8] = { u8'A', u8'i', u8'l', u8'e', u8'V', u8'M', u8'\0', u8'\0' };
const uint16_t VM_VER[3] = { 0, 0, 1 };

Properties properties = {
	.file_version_major = 0,
	.file_version_minor = 0,
	.file_version_patch = 0,
	.file_bitness = 0,
};
