#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_DIMENSIONS 256
#define MAX_VALUE 1024

typedef struct {
    int **content;
    int currentSum;
    size_t lineCount;
    size_t columnCount;
} Matrix_t;

/*
====================
ClearTerminal
 Limpa o terminal
====================
*/
void ClearTerminal( void ) {
#ifdef _WIN32
    system( "cls" );
#else
    system( "clear" );
#endif
}

/*
====================
NewCalloc
 Retorna um ponteiro com memoria alocada (possui tratamento de erro)
====================
*/
void *NewCalloc( const size_t count, const size_t size ) {
    void *const ptr = ( void* ) calloc( count, size );
    if ( !ptr ) {
        printf( "Erro de alocacao de memoria.\n" );
        exit( 1 );
    }
    return ptr;
}

/*
====================
NewRealloc
 Retorna um ponteiro com memoria realocada (possui tratamento de erro)
====================
*/
void *NewRealloc( void *const ptr, const size_t size ) {
    void *const newPtr = ( void* ) realloc( ptr, size );
    if ( !newPtr ) {
        printf( "Erro de alocacao de memoria.\n" );
        exit( 1 );
    }
    return newPtr;
}

/*
====================
NewRealloc
 Retorna um ponteiro com memoria realocada (possui tratamento de erro)
====================
*/
Matrix_t *CreateMatrix( void ) {
    Matrix_t *const matrix = ( Matrix_t* ) NewCalloc( 1, sizeof( Matrix_t ) );
    matrix->content = ( int** ) NewCalloc( 1, sizeof( int* ) );
    matrix->content[0] = ( int* ) NewCalloc( 1, sizeof( int ) );
    matrix->lineCount = 1;
    matrix->columnCount = 1;
    return matrix;
}

/*
====================
ReadInt
 Le e retorna um inteiro no intervalo [min, max]
====================
*/
int ReadInt( const int min, const int max ) {
    int value;
    while ( true ) {
        scanf( "%d", &value );
        if ( min <= value && value <= max ) {
            break;
        }
        printf( "Erro. Digite um valor valido.\n" );
    }
    return value;
}

/*
====================
ResizeMatrix
 Redimensiona a matriz de acordo com o numero de linhas e colunas informadas
====================
*/
void ResizeMatrix( Matrix_t *const matrix ) {
    printf( "Digite o numero de linhas da matriz (entre 1 e %zu): ", ( size_t ) MAX_DIMENSIONS );
    size_t lineCount = ( size_t ) ReadInt( 1, MAX_DIMENSIONS );
    printf( "Digite o numero de colunas da matriz (entre 1 e %zu): ", ( size_t ) MAX_DIMENSIONS );
    size_t columnCount = ( size_t ) ReadInt( 1, MAX_DIMENSIONS );
    for ( size_t i = columnCount; i < matrix->columnCount; i++ ) {
        free( matrix->content[i] );
    }
    matrix->content = NewRealloc( matrix->content, columnCount * sizeof( int** ) );
    for ( size_t i = 0; i < columnCount; i++ ) {
        matrix->content[i] = NewRealloc( matrix->content[i], lineCount * sizeof( int ) );
    }
    matrix->lineCount = lineCount;
    matrix->columnCount = columnCount;
    int currentSum = 0;
    for ( size_t i = 0; i < matrix->lineCount; i++ ) {
        for ( size_t j = 0; j < matrix->columnCount; j++ ) {
            currentSum += matrix->content[j][i];
        }
    }
    matrix->currentSum = currentSum;
    printf( "Matriz redimensionada!\n" );
}

/*
====================
ReadMatrix
 Le os elementos de cada posicao da matriz
====================
*/
void ReadMatrix( Matrix_t *const matrix ) {
    int currentSum = 0;
    for ( size_t i = 0; i < matrix->lineCount; i++ ) {
        for ( size_t j = 0; j < matrix->columnCount; j++ ) {
            printf( "matriz[%zu][%zu] = ", i, j );
            matrix->content[j][i] = ReadInt( 0, MAX_VALUE );
            currentSum += matrix->content[j][i];
        }
    }
    matrix->currentSum = currentSum;
}

/*
====================
ShowMatrixSum
 Mostra a soma atual dos elementos da matriz
====================
*/
void ShowMatrixSum( const Matrix_t *const matrix ) {
    printf( "Soma dos elementos da matriz: %d\n", matrix->currentSum );
}

/*
====================
ShowMatrixColumn
 Mostra os elementos de uma coluna especifica da matriz
====================
*/
void ShowMatrixColumn( const Matrix_t *const matrix ) {
    printf( "Digite o numero da coluna (entre 0 e %zu): ", matrix->columnCount - 1 );
    size_t column = ( size_t ) ReadInt( 0, matrix->columnCount - 1 );
    printf( "Elementos da colunas %zu:\n", column );
    printf( "[" );
    for ( size_t i = 0; i < matrix->lineCount; i++ ) {
        printf( "%d%c", matrix->content[column][i], i == matrix->lineCount - 1 ? ']' : ' ' );
    }
    printf( "\n" );
}

/*
====================
ShowMatrix
 Mostra todos os elementos da matriz
====================
*/
void ShowMatrix( Matrix_t *const matrix ) {
    for ( size_t i = 0; i < matrix->lineCount; i++ ) {
        printf( "[" );
        for ( size_t j = 0; j < matrix->columnCount; j++ ) {
            printf( "%d%c", matrix->content[j][i], j == matrix->columnCount - 1 ? ']' : ' ' );
        }
        printf( "\n" );
    }
    printf( "----------------------------------------\n" );
}

/*
====================
FreeMatrix
 Libera toda a memoria alocada por uma Matrix_t
====================
*/
void FreeMatrix( Matrix_t *const matrix ) {
    for ( size_t i = 0; i < matrix->columnCount; i++ ) {
        free( matrix->content[i] );
    }
    free( matrix->content );
    free( matrix );
}

/*
====================
ShowMenu
 Mostra todas as opcoes do menu
====================
*/
void ShowMenu( void ) {
    printf( "Digite uma opcao:\n" );
    printf( "1 - Definir dimensoes da matriz\n" );
    printf( "2 - Ler elementos da matriz\n" );
    printf( "3 - Mostrar a soma dos elementos da matriz\n" );
    printf( "4 - Mostrar elementos de uma coluna especifica\n" );
    printf( "5 - Mostrar a matriz completa\n" );
    printf( "6 - Sair\n" );
}

int main() {
    Matrix_t *const matrix = CreateMatrix();

    while ( true ) {
        ShowMenu();
        int option = ReadInt( 1, 6 );
        bool quit = false;
        ClearTerminal();

        switch( option ) {
            case 1:
                ResizeMatrix( matrix );
                break;
            case 2:
                ReadMatrix( matrix );
                break;
            case 3:
                ShowMatrixSum( matrix );
                break;
            case 4:
                ShowMatrixColumn( matrix );
                break;
            case 5:
                ShowMatrix( matrix );
                break;
            case 6:
                quit = true;
                break;
        }

        if ( quit ) {
            break;
        }
    }

    FreeMatrix( matrix );

    return 0;
}
