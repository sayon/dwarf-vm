#pragma once

#include <vm.h>

/** @defgroup instructions Instruction set
 * @{ */

/** @def FOR_BYTECODES(DO)
 * Instruction descriptions.
 *
 * TOS = top of the stack
 * 
 * Each entry is a triple of bytecode mnemonic, description and the instruction
 * length in bytes.  All instructions except DUMP are consuming stack operands. 
 * For "binary" instructions the second operand is on top of the stack, e.g.:
 *    ```
 *    LOAD 2
 *    LOAD 1
 *    ISUB
 *    ```
 *    will, as the result, place 1 on TOS (not -1)
 *
 *
 * The command system was inspired by `mathvm` (author: Nikolai Igotti), an
 * educational virtual machine project proposed to Academic University students
 * in St.-Petersburg, Russia.
 */
 
#define FOR_BYTECODES(DO)\
        DO(INVALID,		"Invalid instruction.", 1)\
        DO(LOAD,		"Load value inlined into insn stream.", 9)\
        DO(LOADS,		"Load an address of a string stored in constant pool, whose ID is inlined into insn stream.", 9)\
        DO(DADD,		"Binary double addition.", 1)\
        DO(IADD,		"Binary integer addition.", 1)\
        DO(DSUB,		"Binary double subtraction.", 1)\
        DO(ISUB,		"Binary integer subtraction.", 1)\
        DO(DMUL,		"Binary double multiplication.", 1)\
        DO(IMUL,		"Binary integer multiplication.", 1)\
        DO(DDIV,		"Binary double division", 1)\
        DO(IDIV,		"Binary integer division", 1)\
        DO(IMOD,		"Modulo operation on 2 ints on stack", 1)\
        DO(DNEG,		"Negate double on TOS.", 1)\
        DO(INEG,		"Negate int on TOS.", 1)\
        DO(IPRINT,		"Pop and print integer TOS.", 1)\
        DO(DPRINT,		"Pop and print double TOS.", 1)\
        DO(SPRINT,		"Pop and print string TOS.", 1)\
        DO(I2D,	    	"Convert int on TOS to double.", 1)\
        DO(D2I,	    	"Convert double on TOS to int.", 1)\
        DO(S2I,	        "Convert string on TOS to int.", 1)\
        DO(SWAP,		"Swap 2 topmost values.", 1)\
        DO(POP  ,		"Remove topmost value.", 1)\
        DO(LOADVAR,		"Load value from variable, whose 4-byte id is inlined to insn stream, push on TOS.", 5)\
        DO(LOADSVAR,	"Load constant pool string address by its id, taken from from variable, whose 4-byte id is inlined to insn stream.", 5)\
        DO(LOADCTXVAR,	"Load value from a variable whose 2-byte context id and 4-byte id is inlined into insn stream.", 5)\
        DO(STOREVAR,	"Pop TOS and store to a variable, whose l-byte id is inlined to insn stream.", 5)\
        DO(STORECTXVAR,	"Pop TOS and store to double variable, whose 2-byte context and 4-byte id is inlined to insn stream.", 7)\
        DO(DCMP,		"Compare 2 topmost doubles, pushing libc-stryle comparator value cmp(upper, lower) as integer.", 1)\
        DO(ICMP,		"Compare 2 topmost ints, pushing libc-style comparator value cmp(upper, lower) as integer.", 1)\
        DO(JA,	    	"Jump always, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPNE,	"Compare two topmost integers and jump if upper != lower, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPE,		"Compare two topmost integers and jump if upper == lower, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPG,		"Compare two topmost integers and jump if upper > lower, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPGE,	"Compare two topmost integers and jump if upper >= lower, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPL,		"Compare two topmost integers and jump if upper < lower, next two bytes - signed offset of jump destination.", 3)\
        DO(IFICMPLE,	"Compare two topmost integers and jump if upper <= lower, next two bytes - signed offset of jump destination.", 3)\
        DO(DUMP,		"Dump value on TOS, without removing it.", 1)\
        DO(STOP,		"Stop execution.", 1)\
        DO(CALL,		"Call function, next 8 bytes -- function ID", 9)\
        DO(RETURN,		"Return to call location", 1)\
        DO(BREAK,		"Breakpoint for the debugger (not implemented).", 1)


/// All instruction opcodes
typedef enum {
#define ENUM_ELEM(b, d, l) BC_##b,
    FOR_BYTECODES(ENUM_ELEM)
#undef ENUM_ELEM
    BC_LAST
} bytecode_t;

#define MNEMONIC(b,s,l) #b,

/// All instruction mnemonics
static const char* const bytecode_mnemonic[] = {
FOR_BYTECODES( MNEMONIC )
	""
	};

#undef MNEMONIC

/// Embed 64-bit number into byte array
#define EMBED64( x )\
    ((uint8_t)(x) & 0xff),\
    ((uint8_t)(x>>8) & 0xff),\
    ((uint8_t)(x>>16) & 0xff),\
    ((uint8_t)(x>>24) & 0xff),\
    ((uint8_t)(x>>32) & 0xff),\
    ((uint8_t)(x>>40) & 0xff),\
    ((uint8_t)(x>>48) & 0xff),\
    ((uint8_t)(x>>56) & 0xff)

/// Embed 16-bit number into byte array
#define EMBED16( x )\
    ((uint8_t)(x) & 0xff),\
    ((uint8_t)(x>>8) & 0xff)

struct vm_machine;

/** Launches the interpreter loop
 * @param vm Virtual machine instance
 * @param id Entry point function ID
 * @param debug FILE* instance used for debugging.
 */
void interpret( struct vm_machine* vm, uint64_t id, FILE* debug );

/** @} */
