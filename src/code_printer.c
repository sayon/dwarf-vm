#include <debug.h>
#include <inttypes.h>
#include <instructions.h>

/** @addtogroup code_printer Code printer
 * @{ */


    static void print_INVALID(uint8_t* ptr, FILE* f ){ }


    static void print_LOAD(uint8_t* ptr, FILE* f ){
        uint64_t val =  ((vm_val*)(ptr+1))->as_int ;
        fprintf( f, " %"PRIi64"\t(0x%"PRIx64") ",  val, val );
    }


    static void print_LOADS(uint8_t* ptr, FILE* f ){ 
        fprintf( f, " %"PRIi64" ", ((vm_val*)(ptr+1))->as_int ); 
    }


    static void print_DADD(uint8_t* ptr, FILE* f ){ } 

    static void print_IADD(uint8_t* ptr, FILE* f ){ }


    static void print_DSUB(uint8_t* ptr, FILE* f ){ } 

    static void print_ISUB(uint8_t* ptr, FILE* f ){ } 

    static void print_DMUL(uint8_t* ptr, FILE* f ){ } 

    static void print_IMUL(uint8_t* ptr, FILE* f ){ } 

    static void print_DDIV(uint8_t* ptr, FILE* f ){ } 

    static void print_IDIV(uint8_t* ptr, FILE* f ){ } 

    static void print_IMOD(uint8_t* ptr, FILE* f ){ } 

    static void print_DNEG(uint8_t* ptr, FILE* f ){ } 

    static void print_INEG(uint8_t* ptr, FILE* f ){ } 

    static void print_IPRINT(uint8_t* ptr, FILE* f ){
        fprintf( f, " %"PRIi64, ((vm_val*)(ptr+1))->as_int ); 
    }


    static void print_DPRINT(uint8_t* ptr, FILE* f ){ }


    static void print_SPRINT(uint8_t* ptr, FILE* f ){ 
    }


    static void print_I2D(uint8_t* ptr, FILE* f ){ }


    static void print_D2I(uint8_t* ptr, FILE* f ){ }


    static void print_S2I(uint8_t* ptr, FILE* f ){ }


    static void print_SWAP(uint8_t* ptr, FILE* f ){ }


    static void print_POP(uint8_t* ptr, FILE* f ){ }


    static void print_LOADVAR(uint8_t* ptr, FILE* f ){ 
        fprintf( f, " %" PRIu32, *((uint32_t*)(ptr+1))); 
    }


    static void print_LOADSVAR(uint8_t* ptr, FILE* f ){ 
        fprintf( f, " %"PRIu32, *((uint32_t*)(ptr+1)) ); 
    }


    static void print_STOREVAR(uint8_t* ptr, FILE* f ){ 
        fprintf( f, " %"PRIu32, *((uint32_t*)(ptr+1))); 
    }


    static void print_LOADCTXVAR(uint8_t* ptr, FILE* f ){ }


    static void print_STORECTXVAR(uint8_t* ptr, FILE* f ){ }


    static void print_DCMP(uint8_t* ptr, FILE* f ){ }


    static void print_ICMP(uint8_t* ptr, FILE* f ){ }


    static void print_JA(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPNE(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPE(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPG(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPGE(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPL(uint8_t* ptr, FILE* f ){ }


    static void print_IFICMPLE(uint8_t* ptr, FILE* f ){ }


    static void print_DUMP(uint8_t* ptr, FILE* f ){ }


    static void print_STOP(uint8_t* ptr, FILE* f ){ }


    static void print_CALL(uint8_t* ptr, FILE* f ){ 
        fprintf( f, " %"PRIx64, ((vm_val*)(ptr+1))->as_int ); 
    }


    static void print_CALLNATIVE(uint8_t* ptr, FILE* f ){ }


    static void print_RETURN(uint8_t* ptr, FILE* f ){ }


    static void print_BREAK(uint8_t* ptr, FILE* f ){ }

    void bc_print( FILE* f, uint8_t* ptr, size_t sz ) {

        for( uint8_t* ip = ptr; ip < ptr + sz; )
            switch (*ip)
            {


#define PRINT_CASE(n, d, l) \
        case BC_##n: \
        fputs( #n "\t", f);\
        print_##n( ip, f  ); \
        fprintf( f, "\n" );\
        ip +=l; \
        break;


        FOR_BYTECODES( PRINT_CASE )
        default: 
            fprintf( f, "No interpretation for bytecode %s\n",
                    bytecode_mnemonic[*ip] ); 
            return;
            }

#undef PRINT_CASE
    }


/** @} */
