////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: main.c                      //
////////////////////////////////////////

#include "file.h"
#include "properties.h"

#include <threads.h>

#define DEFAULT_FILENAME "../test.lvm"

void create_test_file(const char* filename)
{
	FILE* file = fopen(filename, "wb");
	static const char CONTENT[] = {

		// Header
		u8'.', u8'l', u8'v', u8'm', // Header start
		0, 0, 1, SIZE_64,           // Version & bitness
		0x00, 0x02, 0x00, 0x00,     // Memory size
		0x00, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00, 0x00,     // _BP
		0x00, 0x00, 0x00, 0x00,
		0x20, 0x00, 0x00, 0x00,     // _IP
		0x00, 0x00, 0x00, 0x00,

		// Data block 1
		0x00, 0x00, 0x00, 0x00,     // Address
		0x00, 0x00, 0x00, 0x00,
		0x08, 0x00, 0x00, 0x00,     // Size
		0x00, 0x00, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00,     // Repeat
		0x00, 0x00, 0x00, 0x00,
		0xEF, 0xCD, 0xAB, 0x89,     // Data
		0x67, 0x45, 0x23, 0x01,

		// Data block 2
		0x00, 0x01, 0x00, 0x00,     // Address
		0x00, 0x00, 0x00, 0x00,
		0x04, 0x00, 0x00, 0x00,     // Size
		0x00, 0x00, 0x00, 0x00,
		0x04, 0x00, 0x00, 0x00,     // Repeat
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,     // Data

		// Data block 3
		0x80, 0x01, 0x00, 0x00,     // Address
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,     // Size
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x10, 0x00, 0x09      // Data

	};
	for (int i = 0; i < 112; ++i)
	{
		fputc(CONTENT[i], file);
	}
	fclose(file);
}

int main(int argc, const char* argv[])
{
	const char* filename = (argc >= 2 ? argv[1] : DEFAULT_FILENAME);
	create_test_file(filename);
	FILE* file = fopen(filename, "rb");
	if (!read_file(file))
	{
		return 1;
	}
	fclose(file);

	for (int i = 0; i < MEM_SIZE; ++i)
	{
		if (i % 8 == 0)
		{
			printf("%3x: ", i);
		}
		printf("%2x ", MEM[i]);
		if (i % 8 == 7)
		{
			printf("\n");
		}
	}

	return 0;
}

/*
int func(void* c)
{
	for (int i = 0; i < 100; ++i)
	{
		printf(c);
	}
	return 0;
}

int main(int argc, const char** argv)
{
	FILE* f = fopen("test.dat", "rb");
	if (!feof(f))
	{
		for (char c = fgetc(f); !feof(f); c = fgetc(f))
		{
			printf("%c", c);
		}
	}
	fclose(f);

	thrd_t ft, st;
	thrd_create(&ft, func, "1");
	thrd_create(&st, func, "2");
	printf("0");
	thrd_join(ft, nullptr);
	thrd_join(st, nullptr);

	return 0;
}
*/
