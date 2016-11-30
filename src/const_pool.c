#include <const_pool.h>
#include <string.h>
#include <util.h>


/** @addgroup const_pool Constant pool
 * @{ */

void const_pool_deinit( struct vm_const_pool * pool ) {
    assert( pool );

    if ( pool-> pool )  free( (char*) pool->pool );
    if ( pool-> by_id ) free( (char**) pool->by_id ); 
}

struct vm_const_pool const_combine( 
        struct vm_const_pool const* a,
        struct vm_const_pool const* b ) {
    assert( a ); assert( b );

    struct vm_const_pool res;
    res.count = a->count + b->count;
    res.sz = a->sz + b->sz;

    char* new_pool = malloc( res.sz );
    memcpy( new_pool, a->pool, a->sz );
    memcpy( new_pool + a->sz, b->pool, b->sz ); 

    res.pool = new_pool;
    res.by_id = divide_on_strings( res.pool, res.sz, res.count );
    return res; 
}

/** @} */
