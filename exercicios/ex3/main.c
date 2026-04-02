#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 128

char buffer[MAX_BUFFER_SIZE];

typedef struct {
    char name[30];
    int age;
    int height;
} Person_t;

typedef struct Node_t {
    struct Node_t *next;
    Person_t *person;
} Node_t;

typedef struct {
    Node_t *head;
    size_t personCount;
} PersonList_t;

void *NewMalloc( const size_t size ) {
    void *ptr = malloc( size );
    if ( !ptr ) {
        printf( "Erro de alocacao de memoria.\n" );
        exit( 1 );
    }
    return ptr;
}

/*
====================
CreatePerson
 Cria uma struct Person_t e retorna o seu ponteiro
====================
*/
Person_t *CreatePerson( const int age, const int height ) {
    Person_t *ptr = NewMalloc( sizeof( Person_t ) );
    strcpy( ptr->name, buffer );
    ptr->age = age;
    ptr->height = height;
    return ptr;
}

/*
====================
CreateNode
 Cria uma struct Node_t e retorna o seu ponteiro
====================
*/
Node_t *CreateNode( Person_t * const person ) {
    Node_t *ptr = NewMalloc( sizeof( Node_t ) );
    ptr->person = person;
    ptr->next = NULL;
    return ptr;
}

/*
====================
CreatePersonList
 Cria uma struct PersonList_t e retorna o seu ponteiro
====================
*/
PersonList_t *CreatePersonList( void ) {
    PersonList_t *ptr = NewMalloc( sizeof( PersonList_t ) );
    ptr->personCount = 0;
    ptr->head = NULL;
    return ptr;
}

/*
====================
AddPerson
 Adiciona uma pessoa para uma lista de pessoas
====================
*/
void AddPerson( PersonList_t * const personList ) {
    int age, height;
    printf( "Digite o nome da pessoa: " );
    scanf( "%s", buffer );
    printf( "Digite a idade da pessoa: ");
    scanf( "%d", &age );
    printf( "Digite a altura da pessoa: ");
    scanf( "%d", &height );
    Person_t *person = CreatePerson( age, height );
    Node_t *node = CreateNode( person );
    node->next = personList->head;
    personList->head = node;
    personList->personCount++;
}

/*
====================
FreePersonList
 Libera a memoria alocada para uma PersonList_t
====================
*/
void FreePersonList( PersonList_t *personList ) {
    Node_t *ptr = personList->head;
    while ( ptr ) {
        Node_t *next = ptr->next;
        free( ptr->person );
        free( ptr );
        ptr = next;
    }
    free( personList );
}

/*
====================
ReadInt
 Le e retorna um valor inteiro no intervalo [min, max]
====================
*/
int ReadInt( const int min, const int max ) {
    int n;
    while ( 1 ) {
        scanf( "%d", &n );
        if ( min <= n && n <= max ) {
            break;
        }
        printf( "Erro. Digite um valor valido.\n" );
    }
    return n;
}

/*
====================
DebugPersonList
 Mostra todas as pessoas em uma PersonList_t
====================
*/
void DebugPersonList( const PersonList_t * const personList ) {
    Node_t *ptr = personList->head;
    size_t counter = 1;
    while ( ptr ) {
        printf( "-----------------------%zu-----------------------\n", counter );
        printf( "Nome: %s\n", ptr->person->name );
        printf( "Idade: %d\n", ptr->person->age );
        printf( "Altura: %d\n", ptr->person->height );
        printf( "-----------------------------------------------\n" );
        ptr = ptr->next;
        counter++;
    }
}

int main() {
    PersonList_t *personList = CreatePersonList();

    while ( 1 ) {
        printf( "Continuar?\n1 - sim\n2 - nao\n" );
        int n = ReadInt( 1, 2 );
        if ( n == 2 ) {
            break;
        }
        AddPerson( personList );
    }

    DebugPersonList( personList );
    FreePersonList( personList );

    return 0;
}
