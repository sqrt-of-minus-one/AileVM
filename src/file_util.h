////////////////////////////////////////////
/////         AileVM by sqrt(-1)         //
////                                    //
///  File: file_util.h                 //
////////////////////////////////////////

#pragma once

#include "bitness.h"

#include <stdio.h>

uint8_t fread8(FILE* file);   // Read a byte from file
uint16_t fread16(FILE* file); // Read a word from file
uint32_t fread32(FILE* file); // Read a dword from file
uint64_t fread64(FILE* file); // Read a qword from file
uintN_t freadN(FILE* file);   // Read N bytes from file

long flength(FILE* file);     // Get the file length
