#include "HashFunctions.h"

/*
Hash function that computes the hash index based on the remainder of division by P.
*/
int hash_function1 (int arg, int P) {
    return arg%P;
}

/*
Hash function that computes the hash index based on the remainder of division by P and then another modulo P.
*/
int hash_function2 (int arg, int P) {
    return (arg/P)%P;
}