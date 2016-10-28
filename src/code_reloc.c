#include <code_reloc.h>

/** @addtogroup code_reloc Relocation 
 * @{ */

/// Relocate a single 8-byte operand 
static void reloc_operand( uint8_t* code, void* ctx) { 
   const uint64_t* offset = ctx;
   vm_val* const operand = (vm_val*) ( code + 1 );
   operand->as_int += *offset; 
}

void code_reloc_code( 
        uint8_t* code, 
        size_t code_sz,
        uint64_t reloc_offset ) {

    struct vm_code_transform reloc = {0};
    reloc.for_LOADS = reloc_operand;
    reloc.for_CALL = reloc_operand;

    bc_perform_inplace_transformation( &reloc, code, code_sz, &reloc_offset ); 

}

void code_reloc_fun( struct vm_fun* f, uint64_t reloc_offset ) {
    code_reloc_code( f->code, f->code_sz, reloc_offset );
    f->meta.sig.name += reloc_offset; 
}


/** @} */
