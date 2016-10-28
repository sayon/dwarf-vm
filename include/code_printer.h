#pragma once

#include <common.h>
#include <stdio.h>

/** @defgroup code_printer Code Printer 
 * Allows to disassemble bytecode and print its mnemonics
 @{ */

/** Pretty print the bytecode mnemonics
 * @param f File to print information to
 * @param bc Bytecode pointer
 * @param sz Bytecode size
 */
void bc_print( FILE* f, uint8_t* bc, size_t sz );


/** @} */