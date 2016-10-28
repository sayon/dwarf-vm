#include <malloc.h>
#include <string.h>
#include <vm.h>
#include <function.h>
#include <const_pool.h>

/**@addtogroup vm */
void vm_init( 
        struct vm_machine* vm,
        size_t data_stack_sz,
        size_t ctx_stack_sz,
        struct vm_prog prog
        ) {
    vm-> data_stack_limit = alloc( data_stack_sz, "data stack" );
    vm-> ctx_stack_limit = alloc( ctx_stack_sz, "context stack" );
    vm-> data_stack_ptr =
         vm-> data_stack_limit + data_stack_sz / sizeof(vm_val) - 1;
    vm-> ctx_stack_ptr = ptr_add_raw( vm-> ctx_stack_limit , ctx_stack_sz );
    vm-> instr_ptr = 0;
    vm-> prog = prog;
}

void prog_deinit( struct vm_prog* p ) {
    const_pool_deinit( & p-> consts ) ;
    funs_deinit( & p-> funs );

}


struct vm_prog prog_create(
        struct vm_funs funs,
        struct vm_const_pool consts ) {
    struct vm_prog prog = {
       .funs = funs,
       .consts = consts
    };
    return prog; 
}

void prog_assign_fun_ids( struct vm_prog* prog, uint64_t start_id ) {
    for( uint64_t i = 0; i < prog->funs.count; i++ )
        prog->funs.by_id[i].meta.id = start_id + i; 
}


struct vm_prog prog_combine( 
        struct vm_prog const* fst, 
        struct vm_prog const* snd ) {
    struct vm_prog res = {0};

    res.consts = const_combine( &( fst-> consts), &( snd-> consts) );
    res.funs   = funs_combine ( &( fst-> funs  ), &( snd-> funs  ), 
            fst->consts.count );

    return res;
}

struct vm_prog prog_combine_destr( 
        struct vm_prog* fst, 
        struct vm_prog* snd ) {
    struct vm_prog res = prog_combine( fst, snd );
    prog_deinit( fst );
    prog_deinit( snd );
    return res;
}

/**@} */
