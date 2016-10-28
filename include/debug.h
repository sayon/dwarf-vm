#pragma once

#include <stdio.h>

#include <common.h>
#include <vm.h>
#include <function.h>

/** @defgroup debug Debug functions */

void const_pool_dump( FILE* f, struct vm_const_pool const* pool );
void fun_dump( FILE* f, struct vm_fun const * fun );
void prog_dump( FILE* f, struct vm_prog const* prog ); 
void funs_dump( FILE* f, const struct vm_funs* fun, struct vm_const_pool const* pool );
void fun_meta_dump( FILE* f, struct vm_fun const* fun, struct vm_const_pool const* pool );

/** @} */