#include <function.h>
#include <string.h>
#include <malloc.h>
#include <code_reloc.h>

/** @addtogroup function
 */

const char* fun_name( struct vm_prog* p, struct vm_fun* fun ) {
    assert( p ); assert( fun );
    return p->consts.by_id[ fun->meta.sig.name ]; 
}
const char* fun_name_by_id( struct vm_prog* p, uint64_t id ) {
    assert( p );
    return fun_name( p, p->funs.by_id + id );
}

struct vm_fun* fun_by_name( struct vm_prog* p, const char* name ) {
    for( size_t i = 0; i < p-> funs.count; i++ ) {
        const char* fname = fun_name( p, p->funs.by_id + i );
        if ( fname && 0 == strcmp( fname, name ) )
            return p->funs.by_id + i;
    }
    return NULL;
}


static
void fun_copy_bytecode( struct vm_fun const* src, 
        struct vm_fun* dest) {
    dest-> code = alloc( src-> code_sz, "bytecode copy" );
   memcpy(  dest-> code, src-> code, src-> code_sz );
   dest-> code_sz = src-> code_sz; 
}


struct vm_funs funs_combine( 
        struct vm_funs const* a, 
        struct vm_funs const* b,
        size_t reloc_offset ) {
    struct vm_funs result; 
    result.count = a-> count + b-> count;
    result.by_id = alloc( result.count * sizeof( struct vm_fun ), 
            "new fun_t::by_id" );
    for( size_t i = 0;         i < a->   count; i++ ) 
    {
        result.by_id[i] = a-> by_id[ i ];
        fun_copy_bytecode( a-> by_id + i, result.by_id + i );
    }

    for( size_t i = 0; i < b->count ; i++ ) 
    {
        struct vm_fun const* const f = b-> by_id + i ;
        const size_t ri = a-> count + i;
        result.by_id[ ri ] =  *f;
        fun_copy_bytecode( f, result.by_id + ri );
        code_reloc_fun( result.by_id + ri , reloc_offset );
    }

    return result; 
}


void fun_deinit( struct vm_fun* fun ) {
    free( fun->code );
}

void funs_deinit( struct vm_funs* funs ) {
    for( size_t i = 0; i < funs-> count; i++ )
        fun_deinit( funs-> by_id  + i ); 
    free( funs-> by_id );
    funs-> by_id = NULL;
    funs-> count = 0;
}

/** @} */
