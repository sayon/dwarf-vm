#pragma once

#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/** @defgroup common Common
 * @{ */

/** Bytecode file format */
#define FILE_FORMAT_VERSION 1

/** A type of a stack cell
 *
 * DWARF is operating mostly on 64bit values, and the data stack consists of 
 * them. Most instruction with operands also contain this value as an immediate
 * operand.
 */
typedef union {
    int64_t as_int;
    double  as_double;
    void*   as_ptr;
} vm_val;

/** A malloc() wrapper which crashes if malloc() fails.
 * aborts the program execution if
 * @param sz Size of an area to allocate in bytes
 * @param msg Message to be displayed if `malloc` fails. Can be NULL.
*/
static inline 
void* alloc( size_t sz, const char* msg ) {
    void* res = malloc( sz );
    if (res) return res;
    if (msg) perror( msg ); 
    abort();
    return NULL;
}

/** Utility, change pointer without multiplying by element size.
 */
static void* ptr_add_raw( void* ptr, size_t offset ) {
    return (uint8_t*)ptr + offset; 
}


/** @} */
