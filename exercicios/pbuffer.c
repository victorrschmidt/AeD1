#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
Estrutura do pBuffer, em ordem:

{int, int, int, int, char[], char[], intX, charX[], charX[], ...}

===============================================================================
VARIAVEIS

// Opcao do menu selecionada pelo usuario
int menuOption;

// Numero de pessoas armazenadas no pBuffer
int peopleCount;

// Iterador para executar loops
int iterator;
===============================================================================
BUFFER

// Armazena a idade da pessoa digitada atualmente
int ageBuffer;

// Armazena o nome da pessoa digitada atualmente
char nameBuffer[MAX_NAME_BUFFER_SIZE];

// Armazena o email da pessoa digitada atualmente
char emailBuffer[MAX_NAME_BUFFER_SIZE];
===============================================================================
"STRUCT PESSOA"

// Armazena a idade da i-esima pessoa
int age;

// Armazena o nome da i-esima pessoa
char name[MAX_NAME_BUFFER_SIZE];

// Armazena o email da i-esima pessoa
char email[MAX_NAME_BUFFER_SIZE];
===============================================================================
*/

// Mensagem padrao de erro de alocacao de memoria
#define ALLOCATION_ERROR_MESSAGE "Erro de alocacao de memoria.\n"

// Tamanho maximo da string para nome e email
#define MAX_STRING_SIZE ( 32 * sizeof( char ) )

// Tamanho da estrutura buffer e pessoa
#define M__BUFFER_SIZE       ( sizeof( int ) + 2 * MAX_STRING_SIZE )
// Tamanho inicial do pBuffer
#define M__INIT_PBUFFER_SIZE ( 4 * sizeof( int ) + 2 * MAX_STRING_SIZE )

// Atalhos para as variaveis
#define V__MENU_OPTION  ( ( int* ) pBuffer )
#define V__PEOPLE_COUNT ( ( int* ) pBuffer + 1 )
#define V__ITERATOR     ( ( int* ) pBuffer + 2 )
#define V__BUFFER_AGE   ( ( int* ) pBuffer + 3 )
#define V__BUFFER_NAME  ( ( char* ) pBuffer + 4 * sizeof( int ) )
#define V__BUFFER_EMAIL ( ( char* ) pBuffer + 4 * sizeof( int ) + MAX_STRING_SIZE )

// Retorna um ponteiro para a idade da i-esima pessoa
#define F__AGE(i, c) \
    ( ( int* ) ( ( char* ) pBuffer + M__INIT_PBUFFER_SIZE + ( *i - c ) * M__BUFFER_SIZE ) )
// Retorna um ponteiro para o nome da i-esima pessoa
#define F__NAME(i, c) \
    ( ( char* ) pBuffer + M__INIT_PBUFFER_SIZE + ( *i - c ) * M__BUFFER_SIZE + sizeof( int ) )
// Retorna um ponteiro para o email da i-esima pessoa
#define F__EMAIL(i, c) \
    ( ( char* ) pBuffer + M__INIT_PBUFFER_SIZE + ( *i - c ) * M__BUFFER_SIZE + sizeof( int ) + MAX_STRING_SIZE )

// pBuffer e um pBuffer auxiliar (para fazer reallocs e garantir que o ponteiro nao sera perdido)
void *pBuffer;
void *pBufferAux;

/*
====================
ClearTerminal
 Remove todo o conteudo do terminal
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
ShowMenu
 Mostra as opcoes do menu
====================
*/
void ShowMenu( void ) {
    printf( "1 - Adicionar pessoa\n" );
    printf( "2 - Remover pessoa pelo email\n" );
    printf( "3 - Buscar pessoa pelo email\n" );
    printf( "4 - Listar todas as pessoas\n" );
    printf( "5 - Sair\n" );
}

/*
====================
ReadInt
 Le um inteiro digitado pelo usuario para saber a operacao a ser executada
====================
*/
void ReadInt( void ) {
    while ( true ) {
        printf( "Digite uma opcao: " );
        scanf( "%d", V__MENU_OPTION );
        if ( *V__MENU_OPTION < 1 || *V__MENU_OPTION > 5 ) {
            printf( "Erro. Digite um valor valido.\n" );
        } else {
            break;
        }
    }
}

/*
====================
AddPerson
 Le e adiciona uma pessoa ao pBuffer
====================
*/
void AddPerson( void ) {
    // Le as informacoes da pessoa
    printf( "Digite o nome: " );
    scanf( "%s", V__BUFFER_NAME );
    printf( "Digite o email: " );
    scanf( "%s", V__BUFFER_EMAIL );
    printf( "Digite a idade: " );
    scanf( "%d", V__BUFFER_AGE );

    // Verifica se o email ja existe. Se sim, a funcao nao adiciona a pessoa
    for ( *V__ITERATOR = 1; *V__ITERATOR <= *V__PEOPLE_COUNT; *V__ITERATOR += 1 ) {
        if ( strcmp( V__BUFFER_EMAIL, F__EMAIL( V__ITERATOR, 1 ) ) == 0 ) {
            printf( "Email ja registrado.\n" );
            return;
        }
    }

    // Aumentar o pBuffer para caber mais uma pessoa
    *V__PEOPLE_COUNT += 1;
    pBufferAux = realloc( pBuffer, M__INIT_PBUFFER_SIZE + ( *V__PEOPLE_COUNT ) * M__BUFFER_SIZE );

    // Verifica possivel erro de alocacao
    if ( !pBufferAux ) {
        printf( ALLOCATION_ERROR_MESSAGE );
        free( pBuffer );
        exit( 1 );
    }

    pBuffer = pBufferAux;
    pBufferAux = NULL;

    // Copia as infos do buffer para as ultimas posicoes do pBuffer
    memcpy( F__AGE( V__PEOPLE_COUNT, 1 ), V__BUFFER_AGE, M__BUFFER_SIZE );

    printf( "Pessoa adicionada com sucesso!\n" );
}

/*
====================
RemovePerson
 Le um email e remove a primeira ocorrencia desse email
====================
*/
void RemovePerson( void ) {
    printf( "Digite o email a ser removido: " );
    scanf( "%s", V__BUFFER_EMAIL );

    for ( *V__ITERATOR = 1; *V__ITERATOR <= *V__PEOPLE_COUNT; *V__ITERATOR += 1 ) {
        if ( strcmp( V__BUFFER_EMAIL, F__EMAIL( V__ITERATOR, 1 ) ) == 0 ) {
            // Cada pessoa passa a ter as informacoes da pessoa da frente na lista
            while ( *V__ITERATOR < *V__PEOPLE_COUNT ) {
                memcpy( F__AGE( V__ITERATOR, 1 ), F__AGE( V__ITERATOR, 0 ), M__BUFFER_SIZE );
                *V__ITERATOR += 1;
            }

            // Diminuir o pBuffer
            *V__PEOPLE_COUNT -= 1;
            pBufferAux = realloc( pBuffer, M__INIT_PBUFFER_SIZE + ( *V__PEOPLE_COUNT ) * M__BUFFER_SIZE );

            // Verifica possivel erro de alocacao
            if ( !pBufferAux ) {
                printf( ALLOCATION_ERROR_MESSAGE );
                free( pBuffer );
                exit( 1 );
            }

            pBuffer = pBufferAux;
            pBufferAux = NULL;
            printf( "Pessoa removida com sucesso!\n" );

            return;
        }
    }

    printf( "Email nao encontrado.\n" );
}

/*
====================
ShowPerson
 Mostra a i-esima pessoa do pBuffer
====================
*/
void ShowPerson( const int *const i ) {
    printf( "%d ------------------------------\n", *i );
    printf( "Nome: %s\nEmail: %s\nIdade: %d\n", F__NAME( i, 1 ), F__EMAIL( i, 1 ), *F__AGE( i, 1 ) );
    printf( "---------------------------------\n" );
}

/*
====================
SearchPerson
 Pesquisa uma pessoa pelo email e retorna todas as ocorrencias desse email
====================
*/
void SearchPerson( void ) {
    printf( "Digite o email a ser buscado: " );
    scanf( "%s", V__BUFFER_EMAIL );
    printf( "Resultado:\n" );

    for ( *V__ITERATOR = 1; *V__ITERATOR <= *V__PEOPLE_COUNT; *V__ITERATOR += 1 ) {
        if ( strcmp( V__BUFFER_EMAIL, F__EMAIL( V__ITERATOR, 1 ) ) == 0 ) {
            ShowPerson( V__ITERATOR );
            break;
        }
    }

    printf( "---------------------------------\n" );
}

/*
====================
ShowAllPeople
 Mostra todas as pessoas armazenadas no pBuffer
====================
*/
void ShowAllPeople( void ) {
    for ( *V__ITERATOR = 1; *V__ITERATOR <= *V__PEOPLE_COUNT; *V__ITERATOR += 1 ) {
        ShowPerson( V__ITERATOR );
    }
}

int main( void ) {
    pBuffer = NULL;
    pBufferAux = NULL;
    pBuffer = malloc( M__INIT_PBUFFER_SIZE );

    if ( !pBuffer ) {
        printf( ALLOCATION_ERROR_MESSAGE );
        return 1;
    }

    *V__PEOPLE_COUNT = 0;

    while ( true ) {
        ShowMenu();
        ReadInt();
        ClearTerminal();

        if ( *V__MENU_OPTION == 1 ) {
            AddPerson();
        } else if ( *V__MENU_OPTION == 2 ) {
            RemovePerson();
        } else if ( *V__MENU_OPTION == 3 ) {
            SearchPerson();
        } else if ( *V__MENU_OPTION == 4 ) {
            ShowAllPeople();
        } else {
            break;
        }
    }

    free( pBuffer );

    return 0;
}
