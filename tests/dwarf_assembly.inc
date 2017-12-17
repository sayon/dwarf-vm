%define INVALID      db   0
%macro LOAD 1
db                        1
dq %1
%endmacro

%macro LOADS 1
db                        2
dq %1
%endmacro

%define DADD         db   3
%define IADD         db   4
%define DSUB         db   5
%define ISUB         db   6
%define DMUL         db   7
%define IMUL         db   8
%define DDIV         db   9
%define IDIV         db   10
%define IMOD         db   11
%define DNEG         db   12
%define INEG         db   13
%define IPRINT       db   14
%define DPRINT       db   15
%define SPRINT       db   16
%define I2D          db   17
%define D2I          db   18
%define S2I          db   19
%define SWAP         db   20
%define POP          db   21

%macro LOADVAR 1
db                        22
dd %1
%endmacro

%macro LOADSVAR 1
db                        23
dd %1
%endmacro

%macro LOADCTXVAR 2
db                        24
dq %1
dd %2
%endmacro

%macro STOREVAR 1
db                        25
dd %1
%endmacro

%macro STORECTXVAR 2
db                        26
dq %1
dd %2
%endmacro

%define DCMP         db   27
%define ICMP         db   28

%macro JA 1
db                        29
dw %1
%endmacro

%macro IFICMPNE 1
db                        30
dw %1
%endmacro

%macro IFICMPE 1
db                        31
dw %1
%endmacro

%macro IFICMPG 1
db                        32
dw %1
%endmacro

%macro IFICMPGE 1
db                        33
dw %1
%endmacro

%macro IFICMPL 1
db                        34
dw %1
%endmacro

%macro IFICMPLE 1
db                        35
dw %1
%endmacro

%define DUMP         db   36
%define STOP         db   37

%macro  CALL 1
db   38
dq %1
%endmacro

%define RETURN       db   39
%define BREAK        db   40

%define CONST 
%macro ENDCONST 0
const_pool_end:
%endmacro


db 0xba, 0xba
dq 1
dq const_pool_end - const_pool 

const_pool:

%macro FUNCTIONS_COUNT 1
dq %1
functions_start:
%endmacro

%define CODE_SIZE dq .bc_end - .bc_start
%define CODE .bc_start:
%define ENDCODE .bc_end:
