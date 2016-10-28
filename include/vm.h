#pragma once

#include <common.h>
#include <stddef.h>
#include <function.h>

/** @defgroup vm Machine 
@{ */

struct vm_fun;

/// A program, consisting of functions and constant data pool
struct vm_prog { 

    /// Functions
    struct vm_funs {
        size_t              count;
        struct vm_fun*      by_id;   /// Pointer to an array of functions
    } funs;

    /// Stores `count` consecutive null-terminated strings.
    struct vm_const_pool {
        size_t              sz;      /// Total size in bytes.
        char const*         pool;    /// Start of the memory region.
        size_t              count;   /// Amount of strings in the pool.
        const char**        by_id;   /// Points to an array of string starts.
    } consts; 
};


/** Virtual machine, containing the program itself and runtime information.
 * 
 * The machine contains the program to be executed and two stacks:
 * - Data stack, to work with data
 * - Context stack, to store runtime function contexts including local values
 * Both stacks grow towards lower numbered addresses.
 */
struct vm_machine {
    vm_val* restrict        data_stack_limit;  
    vm_val* restrict        data_stack_ptr;    /// Stack pointer itself. Grows towards lower addresses

    struct vm_ctx* restrict  ctx_stack_limit;
    struct vm_ctx* restrict  ctx_stack_ptr;    /// Context stack pointer. Grows towards lower addresses

    uint8_t* restrict       instr_ptr;         /// Instruction pointer, points to the bytecode to be executed next.
    struct vm_prog          prog;              /// Program being executed
};


/** Init virtual machine with a specific program to execute, 
 * @param[out] vm Machine to be initialized.
 * @param data_stack_sz Data stack size in bytes
 * @param ctx_stack_sz Context stack size in bytes
 * @param prog Program to assign to `vm` */
void vm_init( 
        struct vm_machine* vm,
        size_t data_stack_sz,
        size_t ctx_stack_sz,
        struct vm_prog prog
        );

/// Deinit virtual machine, freeing all associated resources
void vm_deinit( struct vm_machine* vm );

/// Deinit program, freeing all associated resources
void prog_deinit( struct vm_prog* p );

/// Create a program given an instance of `vm_funs` and `vm_const_pool`
struct vm_prog prog_create( 
        struct vm_funs funs,
        struct vm_const_pool consts );

/** Fill function IDs with their indices in `prog->funs.by_id`
 * @param prog Program to modify
 * @param start_id ID of the first function in `prog`. It will be incremented for each following function.
 */
void prog_assign_fun_ids( struct vm_prog* prog, uint64_t start_id );

/**Combine two programs into a new one.
 * Functions and constant pools have their contents deeply copied.
 * There are no dependencies between old two programs and a new one.
 * @return A new independent program containing functions and constants from both `fst` and `snd`. Functions taken from `snd` are also relocated.
 */
struct vm_prog prog_combine( 
        struct vm_prog const* fst, 
        struct vm_prog const* snd ) ;

/**
 * Combine two programs into a new one, containing functions and constants
 * from both.
 * Note: This function can be rewritten in a way more efficient way (e.g.
 * reusing old allocated bytecode arrays). The load operation is however rare
 * and not a subject to optimizations; the used approach is much more robust.
 * @param[in,out] fst First program .
 * @param snd Second program.
 */
struct vm_prog prog_combine_destr( 
        struct vm_prog* fst, 
        struct vm_prog* snd );



/**@} */
