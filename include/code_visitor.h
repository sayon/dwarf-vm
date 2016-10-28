#pragma once
#include <stdint.h>

#include <instructions.h>

/** @defgroup code_visitor Code Visitor */

/** Stores pointers to transformation pieces for all types of bytecode instructions
 */
struct vm_code_transform { 
#define TRANSFORM_FUNCTION( n, d, l )  void (*for_##n)(uint8_t*, void*);
   FOR_BYTECODES( TRANSFORM_FUNCTION ); 
#undef TRANSFORM_FUNCTION
   void* vm_ctx;
};

/** Performs a transformation on a certain piece of bytecode.
 *
 * @param transformation Transformation description
 * @param code Bytecode pointer
 * @param code_sz Bytecode size
 * @param ctx  A context. This pointer will be passed to all transformation 
 * functions so that they can interact with each other and the outside world
 * using it.
 */
void bc_perform_inplace_transformation( 
        struct vm_code_transform const* transformation, 
        uint8_t* code, 
        size_t code_sz, 
        void* ctx
        );
		
/** @} */
