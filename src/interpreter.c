#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include <common.h>
#include <function.h>
#include <vm.h>
#include <inttypes.h>
#include <instructions.h>

static vm_val val_at( void* ptr ) {return *( (vm_val*)ptr ); }

static const bool DEBUG = 1;

/** @addtogroup interpreter 
 * @{ */

#define OPCODE_HANDLER(OPCODE) \
    __attribute__((allways_inline)) \
static void interpret_##OPCODE(struct vm_machine* vm, FILE *debug) \

OPCODE_HANDLER(INVALID) {
    (void) vm; fprintf( debug, "Invalid operation\n" ); exit(2);
}

OPCODE_HANDLER(LOAD) {
        vm->data_stack_ptr --;
        *(vm->data_stack_ptr) = val_at( vm-> instr_ptr+1 );
    }

OPCODE_HANDLER(LOADS) {
        vm->data_stack_ptr--;
        const vm_val id = val_at( vm-> instr_ptr+1 ) ;
        vm->data_stack_ptr->as_ptr = (void*) 
            vm->prog.consts.by_id[id.as_int] ;
    }

/** Create an interpreter case to perform a binary operator on stack elements
 *
 * @param mnemonic Bytecode mnemonic
 * @param type     Either `double` or `int64_t` depending on number formats
 * @param action   Binary infix operand such as `+` or `/`
 */ 
#define DEFINE_BINOP(mnemonic, type, action)\
OPCODE_HANDLER(mnemonic) {\
        const vm_val* x = vm->data_stack_ptr ;\
        const vm_val* y = vm->data_stack_ptr + 1;\
        vm->data_stack_ptr++;\
        vm->data_stack_ptr->as_##type = x->as_##type action y->as_##type; \
    }

DEFINE_BINOP( DADD, double,  + )
DEFINE_BINOP( DMUL, double,  * )
DEFINE_BINOP( DSUB, double,  - )
DEFINE_BINOP( DDIV, double,  / )

DEFINE_BINOP( IADD, int,  + )
DEFINE_BINOP( IMUL, int,  * )
DEFINE_BINOP( ISUB, int,  - )
DEFINE_BINOP( IDIV, int,  / )
DEFINE_BINOP( IMOD, int,  % )

#undef DEFINE_BINOP

OPCODE_HANDLER(DNEG) {
    vm->data_stack_ptr->as_double =  - vm->data_stack_ptr->as_double; 
    }

OPCODE_HANDLER(INEG) {
    vm->data_stack_ptr->as_int =  - vm->data_stack_ptr->as_int ; 
   }

__attribute__((always_inline))
OPCODE_HANDLER(IPRINT) {
        printf("%"PRIi64, vm->data_stack_ptr->as_int); 
        vm->data_stack_ptr++; 
    }

OPCODE_HANDLER(DPRINT) {
        printf("%lf", vm->data_stack_ptr->as_double );
        vm->data_stack_ptr++; 
    }

OPCODE_HANDLER(SPRINT) {
        fputs( vm->data_stack_ptr->as_ptr, stdout );
        vm->data_stack_ptr++; 
    }

OPCODE_HANDLER(I2D) {}
OPCODE_HANDLER(D2I) {}
OPCODE_HANDLER(S2I) {}
OPCODE_HANDLER(SWAP) {}
OPCODE_HANDLER(POP) {}
OPCODE_HANDLER(LOADVAR) {}
OPCODE_HANDLER(LOADSVAR) {}
OPCODE_HANDLER(STOREVAR) {}
OPCODE_HANDLER(LOADCTXVAR) {}
OPCODE_HANDLER(STORECTXVAR) {}
OPCODE_HANDLER(STORECTXSVAR) {}
OPCODE_HANDLER(DCMP) {}
OPCODE_HANDLER(ICMP) {}
OPCODE_HANDLER(JA) {}
OPCODE_HANDLER(IFICMPNE) {}
OPCODE_HANDLER(IFICMPE) {}
OPCODE_HANDLER(IFICMPG) {}
OPCODE_HANDLER(IFICMPGE) {}
OPCODE_HANDLER(IFICMPL) {}
OPCODE_HANDLER(IFICMPLE) {}
OPCODE_HANDLER(DUMP) {}
OPCODE_HANDLER(STOP) {exit(0); }


__attribute__((always_inline))
static void ctx_init( struct vm_ctx* ctx, 
        void* ret_addr, 
        struct vm_fun* fun,
        struct vm_ctx* prev,
        struct vm_ctx* prev_same_id 
            ) {
        ctx-> ret_addr = ret_addr,
        ctx-> ctx_prev = prev;
        ctx-> ctx_prev_same_id = prev_same_id;
        ctx-> fun = fun;
        fun->meta.topmost_present = ctx;

    }

OPCODE_HANDLER(CALL) {
        vm_val fun_id = val_at( vm->instr_ptr + 1);
        struct vm_fun* const fun = vm->prog.funs.by_id + fun_id.as_int;

        struct vm_ctx* const old_sp = vm-> ctx_stack_ptr;
        const size_t ctx_size = sizeof( struct vm_ctx ) + fun->meta.locals_count * sizeof( vm_val ); 
        vm-> ctx_stack_ptr = ptr_add_raw( vm->ctx_stack_ptr, ctx_size );
       
        ctx_init( vm-> ctx_stack_ptr,
                  vm-> instr_ptr + 9,
                  fun, 
                  old_sp,
                  fun->meta.topmost_present );
        vm->instr_ptr = fun->code - 9;
    }

OPCODE_HANDLER(CALLNATIVE) {}

OPCODE_HANDLER(RETURN) {
        vm->instr_ptr = vm->ctx_stack_ptr->ret_addr - 1;
        vm-> ctx_stack_ptr->fun->meta.topmost_present =
            vm-> ctx_stack_ptr->ctx_prev_same_id;
        vm-> ctx_stack_ptr = vm->ctx_stack_ptr->ctx_prev;
    }

OPCODE_HANDLER(BREAK) {}


    void interpret( struct vm_machine* vm, uint64_t id, FILE* debug ) {
        vm->instr_ptr = vm->prog.funs.by_id[id].code;

#define LABEL_NAME_ARRAY(n,d,l) &&_##n,

        const void* const labels[] = {
            FOR_BYTECODES( LABEL_NAME_ARRAY ) 
                0 };

#undef LABEL_NAME_ARRAY

        goto *labels[ *vm->instr_ptr ];

#define INTERPRETER_CASE(n, d, l) \
        _##n: \
        if (DEBUG) fprintf( debug, "IP: %p " #n, vm->instr_ptr ); \
        interpret_##n( vm, debug ); \
        if (DEBUG) fprintf( debug, "n" ); \
        vm->instr_ptr+=l; \
        goto *labels[ *vm->instr_ptr ];

        FOR_BYTECODES( INTERPRETER_CASE )

#undef INTERPRETER_CASE
    }


/** @} */
