#pragma once
#include <vm.h>
#include <stdio.h>
/** @mainpage
 * -------------------------------------------------------------------------
 *
 * # The bytecode file format
 *   The file structure is described the following way:
 *
 *    * Signature: 0xBA 0xBA, 2 bytes
 *    * Version (8 bytes). Current version is 1
 *    * Constant pool, which is:
 *      + Constant pool size (8 bytes)
 *      + Constant strings, divided by null-terminator.
 *    * Functions:
 *      + Functions count (8 bytes)
 *      + Each function is described as follows:
 *        - Name (8 byte offset in constant pool).
 *        - Local variables count (8 bytes). 
 *        - Flags (8 byte)
 *          + Is exported?
 *          + Is it a native function? (as an import)
 *        - Arguments count (8 bytes).
 *        - Argument types (each 1 byte: 0 for int, 1 for double, 2 for ptr).
 *        This field has a size of SIGNATURE_MAX_ARGS=16
 *        - Size of bytecode (8 bytes)
 *        - Bytecode 
 *
 */

/** @defgroup loader Bytecode loader 
 @{ */

///Bytecode file format
#define FILE_FORMAT_VERSION 1

/// Bytecode loading status
enum vm_load_result {
    LOAD_OK,                        ///< Load successful
    LOAD_INCOMPATIBLE_VERSION,      ///< Bytecode version is not supported
    LOAD_INVALID_FORMAT,            ///< Bytecode file is malformed
    LOAD_IO_ERROR,                  ///< Error when reading or opening file
    LOAD_INVALID_ARGUMENTS          ///< Arguments given to the parsing functions were not valid (e.g. reading 0 files)
};

/// Load bytecode from FILE*
enum vm_load_result file_load( FILE* f, struct vm_prog* prog );


/** Open file by name and load bytecode from there.
 * @param name File name.
 * @param[out] result_prog Pointer to the resulting program.
 * @param error_callback A function which will be called to signalize about errors.
*/
enum vm_load_result file_load_by_name( 
        const char* name, 
        struct vm_prog* result_prog,
        void (error_callback)(enum vm_load_result, const char*) 
        );


/** Open files by names, load bytecode from all of them and combine it.
 * @param names File names.
 * @param count Amount of files. 
 * @param[out] result_prog Pointer to the resulting program.
 * @param error_callback A function which will be called to signalize about errors.
 */
enum vm_load_result file_load_many(
        char const* const* names, 
        size_t count, 
        struct vm_prog* result,
        void (error_callback)(enum vm_load_result, const char*) );

		
/** @} */
