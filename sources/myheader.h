#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "BasicDefinitions.h"


// // #ifdef REAL_LONG_DOUBLE
// #define RealT long double
// #define SQRT sqrtl
// #define ABS fabsl
// #define LOG logl
// #define COS cosl
// #define FLOOR_INT32(x) ((Int32T)(floorl(x)))
// #define CEIL(x) ((int)(ceill(x)))
// #define POW(x, y) (powl(x, y))
// #define FPRINTF_REAL(file, value) {fprintf(file, "%0.3Lf", value);}
// #define FSCANF_REAL(file, value) {fscanf(file, "%Lf", value);}
// // #endif
// DECLARE_EXTERN MemVarT totalAllocatedMemory EXTERN_INIT(= 0);
// // #ifdef REAL_DOUBLE
// #define RealT double
// #define SQRT sqrt
// #define ABS fabs
// #define LOG log
// #define COS cos
// #define FLOOR_INT32(x) ((Int32T)(floor(x)))
// #define CEIL(x) ((int)(ceil(x)))
// #define POW(x, y) (pow(x, y))
// #define FPRINTF_REAL(file, value) {fprintf(file, "%0.3lf", value);}
// #define FSCANF_REAL(file, value) {fscanf(file, "%lf", value);}
// #define EXP exp
// #define ERF erf
// #define ERFC erfc
// // #endif

// #define TimeVarT double

// #define IntT int
// #define LongUns64T long long unsigned
// #define Uns32T unsigned
// #define Int32T int
// #define BooleanT int
// #define TRUE 1
// #define FALSE 0


// #define MALLOC(amount) ((amount > 0) ? totalAllocatedMemory += amount, malloc(amount) : NULL)
// #define FREE(pointer) {if (pointer != NULL) {free(pointer);} pointer = NULL; }


// #define FAILIF(b) {if (b) {fprintf(ERROR_OUTPUT, "FAILIF triggered on line %d, file %s. Memory allocated: %lld\n", __LINE__, __FILE__, totalAllocatedMemory); exit(1);}}
// #define FAILIFWR(b, s) {if (b) {fprintf(ERROR_OUTPUT, "FAILIF triggered on line %d, file %s. Memory allocated: %lld\nReason: %s\n", __LINE__, __FILE__, totalAllocatedMemory, s); exit(1);}}
