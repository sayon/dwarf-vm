#pragma once

#include <code_visitor.h>

/** @defgroup code_reloc Code Relocation */
/** Relocates code, patching operands in bytecode 
 *
 * Instructions such as CALL (prior to linkage) and LOADS are using offsets
 * in the constant pool to address their operands. When two programs A and B
 * are combined, the immediate IDs of B have to be offset based on A's total
 * constants count.
 *
 * Remember, that function IDs are left blank before all programs are combined.
 * 
 * @param code Bytecode pointer.
 * @param code_sz Total bytecode size.
 * @param reloc_offset An offset to add to all constant pool references
 */
void code_reloc_code( uint8_t* code, size_t code_sz, uint64_t reloc_offset ); 

/** Relocates all code of a function. 
 */
void code_reloc_fun( struct vm_fun* f, uint64_t reloc_offset );

/** @} */