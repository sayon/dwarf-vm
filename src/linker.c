#include <linker.h>
#include <vm.h>

#include <code_visitor.h>

/** @addtogroup linker Linker */

static void link_CALL( uint8_t* code, void* ctx) { 
   struct vm_prog* prog = ctx;

   const uint64_t* offset = ctx;
   vm_val* const operand = (vm_val*) ( code + 1 );
   struct vm_fun* callee = 
       fun_by_name( prog, prog->consts.by_id[ operand-> as_int ] );
   operand->as_int = callee->meta.id;
}


void prog_link_calls( struct vm_prog* prog ) {
    struct vm_code_transform link = {0};
    link.for_CALL = link_CALL;
    link.for_LOADCTXVAR = link_CALL;
    link.for_STORECTXVAR = link_CALL;
    for( size_t i = 0; i < prog->funs.count; i++ ) {
    bc_perform_inplace_transformation( &link, 
            prog->funs.by_id[i].code,
            prog->funs.by_id[i].code_sz, 
            prog ); 

    }    

}

/** @} */
