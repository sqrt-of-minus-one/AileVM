# File structure

The structure of the `.lvm` format (v0x00.00.01).

## Header

1. 4 bytes with values `2E 6C 76 6D` (`.lvm` in UTF-8).
1. 3 bytes: the format version (`00 00 01`). The `00 00 00` value is always invalid.
1. 1 byte: the bitness that the program is designed for:
	- `01` — 16-bit;
	- `02` — 32-bit;
	- `03` — 64-bit.
1. N bytes: the memory size.
1. N bytes: the initial value of the `_BP` and `_SP` registers.
1. N bytes: the initial value of the `_IP` register.

## Data

The rest of the file consists of a sequence of blocks which describe the initial state of the memory. Each block includes the following parts.
1. N bytes: the address in the memory where the data will be places.
1. N bytes: the size of the data in bytes. Can be 0, in which case the size is not explicitly defined.
1. N bytes: how many times the data will be repeated in the memory. Are absent if the size of the data is defined as 0.
1. The data that will be placed in the memory. If the size is not defined, everything till the end of file is data.
