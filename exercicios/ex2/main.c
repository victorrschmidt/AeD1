#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORIGINAL_SIZE 500
#define NEW_SIZE 1000

/*
====================
Realloc
 Implementa a funcao realloc
====================
*/
void *Realloc( void *ptr, const size_t size ) {
    void *newPtr = malloc( size );
    if (!newPtr) {
        printf( "Erro de alocacao de memoria.\n" );
        exit( 1 );
    }
    memcpy( newPtr, ptr, size );
    free( ptr );
    return newPtr;
}

int main() {
    int *a = malloc( ORIGINAL_SIZE * sizeof( int ) );
    int *b = Realloc( a, NEW_SIZE );

    free( b );

    return 0;
}