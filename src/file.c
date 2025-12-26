////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: file.c                      //
////////////////////////////////////////

#include "file.h"

#include "file_util.h"
#include "properties.h"

#include <stdlib.h>
#include <string.h>

#define FILE_HEADER_START_SIZE 4
static const unsigned char FILE_HEADER_START[FILE_HEADER_START_SIZE] = { u8'.', u8'l', u8'v', u8'm' };

bool read_file_header(FILE* file, long length)
{
	// The first FILE_HEADER_START_SIZE bytes must be the same as FILE_HEADER_START
	for (int i = 0; i < FILE_HEADER_START_SIZE; ++i)
	{
		unsigned char c = fgetc(file);
		if (ferror(file) || c != FILE_HEADER_START[i])
		{
			return false;
		}
	}

	// Read and check the file format version (3 bytes)
	properties.file_version_major = fread8(file);
	properties.file_version_minor = fread8(file);
	properties.file_version_patch = fread8(file);
	if (ferror(file) ||
		properties.file_version_major > 0 ||
		properties.file_version_minor > 0 ||
		properties.file_version_patch != 1)
	{
		// Only 0.0.1 is supported
		return false;
	}

	// Read and check the bitness (1 byte)
	properties.file_bitness = fread8(file);
	if (ferror(file) ||
		properties.file_bitness != SIZE_N)
	{
		// The bitness of the file must be the same as that of the VM
		return false;
	}

	// There must be at least 3 more N-byte numbers in the file
	if (length - ftell(file) < 3 * AILE_BYTES)
	{
		return false;
	}

	MEM_SIZE = freadN(file);
	REG_BP.value = freadN(file);
	REG_SP.value = REG_BP.value;
	REG_IP.value = freadN(file);
	if (ferror(file))
	{
		return false;
	}

	MEM = malloc(MEM_SIZE);
}

bool read_file_data(FILE* file, long length)
{
	while (ftell(file) < length) // Read until the end of file
	{
		if (length - ftell(file) < 2 * AILE_BYTES)
		{
			return false;
		}

		uintN_t addr = freadN(file); // Where to put data
		uintN_t size = freadN(file); // How long is the data
		uintN_t repeat = 1;
		if (size > 0) // The size is specified
		{
			if (length - ftell(file) < AILE_BYTES + size)
			{
				return false;
			}

			repeat = freadN(file); // How many times should the data be repeated
		}
		else
		{
			size = length - ftell(file);
		}

		// If the data doesn't fit in the memory
		if (!is_range_in_mem(addr, size * repeat))
		{
			return false;
		}

		for (uintN_t i = 0; i < size; ++i) // Read the data from the file and write it to the memory
		{
			MEM[addr + i] = fread8(file);
		}
		for (uintN_t i = 1; i < repeat; ++i) // Repeat the data
		{
			memcpy(MEM + addr + size * i, MEM + addr, size);
		}
	}
	return true;
}

bool read_file(FILE* file)
{
	if (!file)
	{
		return false;
	}

	long length = flength(file);
	if (length < 8)
	{
		return false;
	}

	return
		read_file_header(file, length) &&
		read_file_data(file, length);
}
