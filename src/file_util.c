////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: file_util.c                 //
////////////////////////////////////////

#include "file_util.h"

#include "mem.h"

// Iterate through bytes (from low to high)
#ifdef LITTLE_ENDIAN
#	define ENDIAN_FOR(i, bytes) for (int i = 0; i < (bytes); ++i)
#elifdef BIG_ENDIAN
#	define ENDIAN_FOR(i, bytes) for (int i = (bytes) - 1; i >= 0; --i)
#endif

#define FREAD_N(Int_type, bytes)      \
	Int_type result;                  \
	ENDIAN_FOR(i, (bytes))            \
	{                                 \
		result.byte[i] = fgetc(file); \
	}                                 \
	return result.value

uint8_t fread8(FILE* file)
{
	return fgetc(file);
}

uint16_t fread16(FILE* file)
{
	FREAD_N(Int16, 2);
}

uint32_t fread32(FILE* file)
{
	FREAD_N(Int32, 4);
}

uint64_t fread64(FILE* file)
{
	FREAD_N(Int64, 8);
}

uintN_t freadN(FILE* file)
{
	FREAD_N(IntN, AILE_BYTES);
}

long flength(FILE* file)
{
	fpos_t pos;
	fgetpos(file, &pos); // Save the current position
	fseek(file, 0, SEEK_END); // Go to the end
	long size = ftell(file); // Get the end position
	fsetpos(file, &pos); // Restore the current position
	return size;
}
