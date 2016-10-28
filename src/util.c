#include <util.h>

/** @addgroup util */
size_t count_strings( const char* pool, size_t sz ) {
    size_t strings = 0;
    for( size_t i = 0; i < sz; i++ ) 
        if ( pool[i] == 0 ) 
            strings++;
    return strings;
}

char const** divide_on_strings( 
        char const* pool, 
        size_t sz, 
        size_t count ) { 

    char const** ptrs = alloc( 
            count * sizeof( char const* ),
            "Initializing a constant pool" ); 

    ptrs[0] = pool;
    size_t j = 1; 
    for( size_t i = 0; sz && i < sz - 1; i++ ) 
        if ( pool[i] == 0 && pool[i+1] != 0 ) 
            ptrs[j++] = pool+i+1;
    return ptrs;
}

/** @} */