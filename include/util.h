#pragma once

#include <stddef.h>

#include <common.h>

/** @defgroup util Util 
@{ */

/** Counts the amount of null-terminated strings consecutively stored in an array
 * @param pool Memory region filled with strings.
 * @param sz Size of `pool` in bytes. */
size_t count_strings( const char* pool, size_t sz );

/** Find string beginnings and return a dynamically allocated array, containing
 * pointers to them.  
 * @param pool Memory region filled with strings.
 * @param sz Size of `pool` in bytes.
 * @param count Strings count in `pool`. */
char const** divide_on_strings( char const* pool, size_t sz, size_t count );


/** @} */