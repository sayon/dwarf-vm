#include <debug.h>
#include <function.h>
#include <code_printer.h>
#include <inttypes.h>

/** @addtogroup debug 
  @{ */
void const_pool_dump( FILE* f, struct vm_const_pool const* pool ) {
    assert( f );
    assert( pool );
    fputs( " -- constant pool --\n" , f );
    for( size_t i = 0; i < pool->count; i++ ) {
        fprintf(f, "%"PRIu64" %s \n", i, pool->by_id[i] );
    }
}


void fun_meta_dump( FILE* f, struct vm_fun const* fun, struct vm_const_pool const* pool ) {
    assert( f ); assert( fun );
    fprintf( f, " -- function " );
    if ( pool ) fprintf( f, "%s --\n",  pool->by_id[ fun->meta.sig.name ] );
    else fprintf( f, " name id: %"PRIu64" --", fun->meta.sig.name );
    fprintf( f, "id: %"PRIu64"\ncode_sz: %"PRIu64"\nargs:\n", fun->meta.id, fun->code_sz);

    if (fun->meta.sig.arg_count)
    for( size_t i = 0; i < fun->meta.sig.arg_count-1; i++ )
        fprintf( f, "%s, ", type_mnemonic[ fun->meta.sig.args[i] ] );

    if ( fun->meta.sig.arg_count > 0 )
        fprintf( f, "%s\n", type_mnemonic[ fun->meta.sig.arg_count -1 ] );
   
    fprintf( f, " -- code --\n" ); 
    bc_print( f, fun->code, fun->code_sz );
    fprintf( f, " ----------\n" ); 
}


void funs_dump( FILE* f, struct vm_funs const*  funs, struct vm_const_pool const* pool ) {
    for( size_t i = 0; i < funs->count; i++ )
    {
        fun_meta_dump( f, funs->by_id + i, pool );
        bc_print( f, funs->by_id[i].code, funs->by_id[i].code_sz );
    }
}

void prog_dump( FILE* f, struct vm_prog const* prog ){
    const_pool_dump( f, &prog->consts );
    funs_dump( f, &prog->funs, &prog->consts ); 

}

/** @} */
