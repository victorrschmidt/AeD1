#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *chain;
    size_t size;
    size_t name_count;
} NameList;

char buffer[MAX_BUFFER_SIZE];
NameList names;

void show_menu() {
    printf("--------------------------\n");
    printf("Menu:\n");
    printf("1 - Adicionar nome\n");
    printf("2 - Remover nome\n");
    printf("3 - Listar nomes\n");
    printf("4 - Sair:\n");
    printf("--------------------------\n");
}

int read_menu_option() {
    int val;
    show_menu();
    while (1) {
        printf("Digite uma opcao: ");
        scanf("%d", &val);
        if (1 <= val && val <= 4) break;
        printf("Erro: Digite um valor valido.\n");
    }
    return val;
}

void read_name() {
    memset(buffer, 0, sizeof(buffer));
    printf("Digite um nome: ");
    scanf("%s", buffer);
}

void add_name() {
    read_name();
    size_t length = strlen(buffer);
    names.chain = realloc(names.chain, names.size + length + 1);
    for (size_t i = names.size; i < names.size + length; i++) {
        names.chain[i] = buffer[i - names.size];
    }
    names.size += length + 1;
    names.name_count++;
    printf("Nome adicionado!\n");
}

void remove_name() {
    read_name();
    char *ptr = names.chain;
    for (size_t i = 0; i < names.name_count; i++) {
        if (strcmp(ptr, buffer) == 0) {
            size_t length = strlen(ptr);
            size_t l = ptr - names.chain;
            size_t r = l + length + 1;
            while (r < names.size) {
                names.chain[l] = names.chain[r];
                l++;
                r++;
            }
            names.chain = realloc(names.chain, names.size - length - 1);
            names.size -= length + 1;
            names.name_count--;
            printf("Nome removido!\n");
            return;
        }
        while (*ptr != '\0') ptr++;
        ptr++;
    }
    printf("Nome nao encontrado.\n");
}

void show_names() {
    if (names.name_count == 0) {
        printf("A lista de nomes esta vazia.\n");
        return;
    }
    printf("Lista de nomes:\n");
    char *ptr = names.chain;
    for (size_t i = 0; i < names.name_count; i++) {
        printf("%zu - %s\n", i + 1, ptr);
        while (*ptr != '\0') ptr++;
        ptr++;
    }
}

int main() {
    names.chain = malloc(0);
    names.size = 0;
    names.name_count = 0;

    while (1) {
        int option = read_menu_option();
        if (option == 1) {
            add_name();
        }
        else if (option == 2) {
            remove_name();
        }
        else if (option == 3) {
            show_names();
        }
        else {
            break;
        }
    }

    free(names.chain);

    return 0;
}