#pragma once

#include <common.h>
#include <stddef.h>
#include <stdint.h>
#include <vm.h>
#define SIGNATURE_MAX_ARGS 16 


/** @defgroup function Function
 * @{*/

/// Function signature
struct vm_sig {
    size_t name;                    /// An offset in the constants pool
    size_t arg_count;               /// Arguments count.
    enum vm_type { T_INT, T_DOUBLE, T_PTR } 
    args[SIGNATURE_MAX_ARGS];       /// Argument types.
};

/** Runtime context.
 *  The context size varies with local variables count.  */
struct vm_ctx {
    void*  ret_addr;                /// Return address. 
    struct vm_fun* fun;             /// Corresponding function.
    struct vm_ctx* ctx_prev_same_id;/// Previous function instance (think recursion) 
    struct vm_ctx* ctx_prev;        /// Previous context in stack 
    vm_val  locals[];               /// Local variables
};

/// Function metadata
struct vm_fun_meta {
    uint64_t id;                    /// Function ID
    struct vm_sig sig;              /// Signature
    size_t locals_count;            /// How many locals are allocated
    uint8_t is_native;              /// Is it a native function?
    void*   native_addr;            /// For native functions, its address
    struct vm_ctx* topmost_present; /// Most recent function instance.
};

/// Function
struct vm_fun {
    struct vm_fun_meta meta;        /// Metadata
    size_t code_sz;                 /// Bytecode length in bytes.
    uint8_t* code;                  /// Bytecode start. Allocated in heap.
};

/// Native function
struct vm_native_fun {
    struct vm_fun_meta meta;        /// Metadata (same as non-native)
    void*  addr;                    /// Calling address.
};

struct vm_prog;

/// Function name by its record.
const char* fun_name( struct vm_prog* p, struct vm_fun* fun );

/** Function name by its identifier.
 * @param p Program.
 * @param id Function index in p->funs.  */
const char* fun_name_by_id( struct vm_prog* p, uint64_t id );

/// Find function record by name.
struct vm_fun* fun_by_name( struct vm_prog* p, const char* name );

/** Type string representations.
 * The index corresponds to vm_sig::vm_type values. */
static const char* const type_mnemonic[] = { "int", "double", "ptr" };

/** Combine two `vm_funs` instances and generate a new one, completely detached.
 * @param a,b `vm_funs` instances.
 * @param reloc_offset Relocation offset; count of the `vm_const_pool` 
 *                     corresponding to `a`*/
struct vm_funs funs_combine( 
        struct vm_funs const* a, 
        struct vm_funs const* b,
        size_t reloc_offset );

/// Free all associated memory in heap.
void fun_deinit( struct vm_fun* fun );

/// Free all functions inside.
void funs_deinit( struct vm_funs* funs );


/** @} */
