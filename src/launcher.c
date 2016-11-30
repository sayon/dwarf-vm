#include <stdio.h>

#include <common.h>
#include <function.h>
#include <vm.h>
#include <instructions.h>
#include <loader.h>
#include <debug.h>
#include <const_pool.h>
#include <linker.h>

/** @defgroup launcher 
 * @{*/

///Virtual machine exit code.
enum vm_exit_code {
   VM_EXIT_OK = 0,         /// < No errors.
   VM_EXIT_BAD_FILE,       /// < IO error when reading bytecode file.
   VM_EXIT_FILE_FORMAT,    /// < Bytecode file format is invalid.
   VM_EXIT_NO_MAIN         /// < No function with name `main` defined.
};


/** Dump program to a file .
 * @param name File name.
 * @param prog Program to dump.
 * */
static void prog_dump_file( const char* name, const struct vm_prog* prog ) {
    FILE* f = fopen( name, "w" );
    prog_dump( f, prog );
    fclose( f ); 
}

int main( int argc, char const* const* argv) {
    struct vm_machine vm;
    struct vm_prog prog = {0};
    if (argc < 2) { fprintf( stderr, "Usage: vm file1 ... fileN\n" ); return 2;}

    enum vm_load_result file_load_status = 
        file_load_many( argv + 1, argc-1, &prog, stderr );

    if (file_load_status == LOAD_IO_ERROR) return VM_EXIT_BAD_FILE;
    if (file_load_status == LOAD_INVALID_FORMAT || 
            file_load_status == LOAD_INCOMPATIBLE_VERSION ) 
        return VM_EXIT_FILE_FORMAT;
    
    vm_init( &vm, 65536, 65536, prog );

    prog_dump_file( "dump_read.txt", &vm.prog );

    prog_assign_fun_ids( &vm.prog, 0 ); 

    prog_dump_file( "dump_ids_assigned.txt", &vm.prog );
   
    prog_link_calls( &vm.prog );
    prog_dump_file( "dump_linked.txt", &vm.prog );
  
    FILE* trace = fopen( "dump_trace.txt", "w" );

    struct vm_fun* main_fun = fun_by_name( & vm.prog , "main" );
    if (! main_fun ) { 
        fprintf( trace, "No <main> function defined!\n" );
        return VM_EXIT_NO_MAIN; }
    else 
        fprintf( trace, "Main function: id %lu, name %lu\n", main_fun->meta.id, main_fun->meta.sig.name );


    interpret( &vm, main_fun->meta.id, trace ); 
    return 0;
}


/** @} */
