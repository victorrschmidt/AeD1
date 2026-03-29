#include <stdio.h>
#include <stdlib.h>

int ThirdMax( int *nums, int numsSize ) {
    int list[4];
    int listSize = 0;

    // list[0] = maior numero
    // list[1] = segundo maior numero
    // list[2] = terceiro maior numero
    // list[3] = pivo auxiliar

    for ( int i = 0; i < numsSize; i++ ) {
        // Se o numero esta na lista, ele pode ser ignorado
        char flag = 0;

        for ( int j = 0; j < listSize; j++ ) {
            if ( nums[i] == list[j] ) {
                flag = 1;
                break;
            }
        }

        // Ignorar o numero atual, pois ele ja esta na lista
        if ( flag == 1 ) {
            continue;
        }

        // O numero nao esta na lista, entao vamos inseri-lo

        // Verificar se precisamos deslocar a lista para a direita
        // a partir de uma posicao especifica para manter a lista ordenada
        for ( int j = 0; j < listSize; j++ ) {
            if ( nums[i] > list[j] ) {
                for ( int k = listSize; k > j; k-- ) {
                    list[k] = list[k - 1];
                }

                list[j] = nums[i];
                if ( listSize < 3 ) {
                    listSize++;
                }

                flag = 1;
                break;
            }
        }

        // O numero foi inserido atraves da comparacao com outro numero da lista
        if ( flag == 1 ) {
            continue;
        }

        // Inserir o numero na ultima posicao da lista
        list[listSize] = nums[i];
        if ( listSize < 3 ) {
            listSize++;
        }
    }

    // Se a lista esta cheia, retornar o terceiro maior numero.
    // Caso contrario, retornar o maior numero
    if ( listSize == 3 ) {
        return list[2];
    } else {
        return list[0];
    }
}

int main() {
    int numsSize;
    scanf( "%d", &numsSize );
    int *nums = malloc( numsSize * sizeof( int ) );

    if ( nums == NULL ) {
        printf( "Erro de memoria.\n" );
        return 1;
    }

    for ( int i = 0; i < numsSize; i++ ) {
        scanf( "%d", &nums[i] );
    }

    printf( "%d\n", ThirdMax( nums, numsSize ) );

    free( nums );

    return 0;
}
