#pragma once

#include <code_visitor.h>

/** @defgroup linker Linker
@{ */

/** Perform linkage. 
 *
 * During linkage the `CALL` instructions are patched. 
 * 
 * Before linkage: `CALL n`, `n` is the string id in constant pool where the
 * function name is located.
 *
 * After linkage: `CALL n`, `n` is the matching function ID.
 */
void prog_link_calls( struct vm_prog* prog );


/** @} */
