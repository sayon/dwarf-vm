#include <instructions.h>
#include <code_visitor.h>
#include <vm.h>

/** @addtogroup code_visitor 
 * This module defines common code for all bytecode transformations
 * @{ */

#define INTERPRETER_CASE(n, d, l) \
    case BC_##n: \
    if ( transformation-> for_##n != NULL )\
    transformation->for_##n( ip, ctx );\
    ip+=l; \
    break;

void bc_perform_inplace_transformation( 
        struct vm_code_transform const* transformation, 
        uint8_t* code, 
        size_t code_sz, 
        void* ctx
        ) { 
        for ( uint8_t* ip = code; ip < code + code_sz; )
            switch ( *ip ) { 
            FOR_BYTECODES( INTERPRETER_CASE )
            }
}

#undef INTERPRETER_CASE

/** @} */

