# Instruction format
An instruction consists of the three parts, which are stored directly after each other:
1. the instruction code (1 B);
1. the operands specification (0–2 B);
1. operands (0–3).

Each operand is usually specified with 4 bytes:
- `0000`: no operand (o);
- `0011`: a register (r);
- `01ss`: a constant value (i);
- `10ss`: data in memory with a relative address (mᵣ);
- `11ss`: data in memory with an absolute address (mₐ).

`ss` encodes the operand size:
- `00`: 1 B;
- `01`: 2 B;
- `10`: 4 B;
- `11`: 8 B.

Below is the description of the operands format.

## r
A register operand is stored as a one-byte address.

## i
A constant operand is stored directly.

## mᵣ
Is stored as a signed number (1 B for x16; 2 B for x32 and x64), which has to be added to the current `_IP` value in order to get the requested address.

## mₐ
An absolute address is stored as `B + C*S + O`. Here `B` is the base address (an unsigned n-bit number or register). `C` is the number 1, 2, 4, or 8. `S` is the scale (a signed 8-bit (x16) or 16-bit (x32, x64) number or register). `O` is the offset (a signed 8-bit (x16) or 16-bit (x32, x64) number). All the summands but `B` are optional.

The operand format in the memory:
```
s̃õbb'bbbb [B] [ccss'ssss [S]] [O]
```
- `s̃`: presence (`1`) or absence (`0`) of a scale (see `s`).
- `õ`: presence (`1`) or absence (`0`) of an offset (см. `O`).
- `b`: the lower bits of the address of the n-bit register that keeps the base address. If all the bits are zeros, the base address is stored directly (см. `B`).
- `B`: the n-bit base address. Is only present if all of the `b` bits are zeros.
- `c`: the multiplier of the scale in the exponential form: `C` = 2^`c`. Is only present if the `s̃` bit is not zero.
- `s`: the lower bits of an 8-bit (x16) or 16-bit (x32, x64) register that keeps the scale. If all the bits are zeros, the scale is stored directly (see `S`). Is only present if the `s̃` bit is not zero.
- `S`: the 8-bit (x16) or 16-bit (x32, x64) scale. Is only present if the `s̃` bit is not zero and all of the `s` bits are zeros.
- `O`: the 8-bit (x16) or 16-bit (x32, x64) offset. Is only present if the `õ` bit is not zero.