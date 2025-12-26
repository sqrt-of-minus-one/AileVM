cmake_minimum_required(VERSION 3.21)
project(lvm
	VERSION 0.0.1
	LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(SOURCE_EXE
	src/mem.c
	src/properties.c
	src/file_util.c
	src/file.c
	src/main.c)

add_executable(lvm64 ${SOURCE_EXE})
