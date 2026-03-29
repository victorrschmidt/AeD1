#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1024

typedef struct {
    char   *chain;
    size_t size;
    size_t nameCount;
} NameList_t;

char buffer[MAX_BUFFER_SIZE];

/*
====================
ClearTerminal
 Limpa as informacoes do terminal.
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
 Mostra as opcoes do menu.
====================
*/
void ShowMenu( void ) {
    printf( "--------------------------\n" );
    printf( "Menu:\n" );
    printf( "1 - Adicionar nome\n" );
    printf( "2 - Remover nome\n" );
    printf( "3 - Listar nomes\n" );
    printf( "4 - Sair:\n" );
    printf( "--------------------------\n" );
}

/*
====================
ReadMenuOption
 Le a opcao do menu selecionada pelo usuario e retorna um inteiro referente
 a opcao selecionada.
====================
*/
int ReadMenuOption( void ) {
    int val;
    ShowMenu();
    while ( 1 ) {
        printf( "Digite uma opcao: " );
        scanf( "%d", &val );
        if ( 1 <= val && val <= 4 ) {
            break;
        }
        printf( "Erro: Digite um valor valido.\n" );
    }
    return val;
}

/*
====================
ReadName
 Le uma string inserida pelo usuario na entrada padrao para a variavel buffer.
====================
*/
void ReadName( void ) {
    memset( buffer, 0, sizeof( buffer ) );
    printf( "Digite um nome: " );
    scanf( "%s", buffer );
}

/*
====================
AddName
 Adiciona a string do buffer na lista de nomes.
====================
*/
void AddName( NameList_t *nameList ) {
    ReadName();
    size_t length = strlen( buffer );
    if ( nameList->size == 0 ) {
        nameList->chain = malloc( (length + 1) * sizeof( char ) );
    } else {
        nameList->chain = realloc( nameList->chain, ( nameList->size + length + 1 ) * sizeof( char ) );
    }
    for ( size_t i = nameList->size; i < nameList->size + length; i++ ) {
        nameList->chain[i] = buffer[i - nameList->size];
    }
    nameList->size += length + 1;
    nameList->nameCount++;
    printf( "Nome adicionado!\n" );
}

/*
====================
RemoveName
 Remove a primeira ocorrencia da string
 do buffer (se existir) da lista de nomes.
====================
*/
void RemoveName( NameList_t *nameList ) {
    ReadName();
    const char *ptr = nameList->chain;
    for ( size_t i = 0; i < nameList->nameCount; i++ ) {
        if ( strcmp( ptr, buffer ) == 0 ) {
            const size_t length = strlen( ptr );
            size_t l = ptr - nameList->chain;
            size_t r = l + length + 1;
            while ( r < nameList->size ) {
                nameList->chain[l] = nameList->chain[r];
                l++;
                r++;
            }
            if ( nameList->nameCount == 1 ) {
                free( nameList->chain );
            } else {
                nameList->chain = realloc( nameList->chain, ( nameList->size - length - 1 ) * sizeof( char ) );
            }
            nameList->size -= length + 1;
            nameList->nameCount--;
            printf( "Nome removido!\n" );
            return;
        }
        while ( *ptr != '\0' ) {
            ptr++;
        }
        ptr++;
    }
    printf( "Nome nao encontrado.\n" );
}

/*
====================
ShowNames
 Mostra todos os nomes contidos na lista de nomes.
====================
*/
void ShowNames( NameList_t *nameList ) {
    if ( nameList->nameCount == 0 ) {
        printf( "A lista de nomes esta vazia.\n" );
        return;
    }
    printf( "Lista de nomes:\n" );
    const char *ptr = nameList->chain;
    for ( size_t i = 0; i < nameList->nameCount; i++ ) {
        printf( "%zu - %s\n", i + 1, ptr );
        while ( *ptr != '\0' ) {
            ptr++;
        }
        ptr++;
    }
}

int main() {
    NameList_t nameList;
    nameList.size = 0;
    nameList.nameCount = 0;

    while ( 1 ) {
        int option = ReadMenuOption();
        ClearTerminal();
        if ( option == 1 ) {
            AddName( &nameList );
        } else if ( option == 2 ) {
            RemoveName( &nameList );
        } else if ( option == 3 ) {
            ShowNames( &nameList );
        } else {
            break;
        }
    }

    if ( nameList.size > 0 ) {
        free( nameList.chain );
    }

    return 0;
}
