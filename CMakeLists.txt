cmake_minimum_required(VERSION 3.21)
project(lvm
	VERSION 0.0.1
	LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(SOURCE_INSTRUCTIONS
	src/instructions/get_operand.c
	src/instructions/00_nop.c
	src/instructions/01_info.c
	src/instructions/08_jmp.c)

set(SOURCE_EXE
	src/file_util.c
	src/file.c
	src/mem.c
	src/properties.c
	src/registers.c
	src/run.c
	${SOURCE_INSTRUCTIONS}
	src/main.c)

add_executable(lvm64 ${SOURCE_EXE})
