/** 
#include <stdio.h>
#include "mymemory.h"

int main()
{
    // aloca pool memoria
    mymemory_t *memory = mymemory_init(1000000);

    //int v[32];
    // int *v = malloc(sizeof(int)*32);
    int *v = mymemory_alloc(memory, sizeof(int)*64);


    int *v2 = mymemory_alloc(memory, sizeof(int)*16);

    //char *str = mymemory_alloc(memory, sizeof(char)*16);


    // free(v);


    int *v3 = mymemory_alloc(memory, sizeof(int)*32);

    mymemory_display(memory);

    mymemory_free(memory, v3);

    mymemory_display(memory);


    
    printf("v: %p\n", (void*)v);
    //sprintf(str, "ola mundo");
    printf("v2: %p\n", (void*)v2);
    printf("v3: %p\n", (void*)v3);
    // libera o pool de memoria
    //mymemory_release(memory);


    return 0;

}
*/

#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

void print_menu() {
    printf("\nMenu:\n");
    printf("1. Inicializar memória\n");
    printf("2. Alocar memória\n");
    printf("3. Liberar memória\n");
    printf("4. Exibir memória\n");
    printf("5. Estatísticas da memória\n");
    printf("6. Liberar memória\n");
    printf("Escolha uma opção: ");
}

int main() {
    int choice;
    size_t size;
    mymemory_t *memory = NULL;
    void *ptr;

    while (1) {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Digite o tamanho total da memória para inicializar: ");
                scanf("%zu", &size);
                memory = mymemory_init(size);
                if (memory) {
                    printf("Memória inicializada com sucesso.\n");
                } else {
                    printf("Falha ao inicializar memória.\n");
                }
                break;

            case 2:
                if (!memory) {
                    printf("Memória não inicializada. Por favor, inicialize a memória primeiro.\n");
                    break;
                }
                printf("Digite o tamanho da memória para alocar: ");
                scanf("%zu", &size);
                ptr = mymemory_alloc(memory, size);
                if (ptr) {
                    printf("Memória alocada com sucesso.\n");
                } else {
                    printf("Falha ao alocar memória.\n");
                }
                break;

            case 3:
                if (!memory) {
                    printf("Memória não inicializada. Por favor, inicialize a memória primeiro.\n");
                    break;
                }
                printf("Digite o ponteiro da memória para liberar: ");
                scanf("%p", &ptr);
                mymemory_free(memory, ptr);
                printf("Memória liberada.\n");
                break;

            case 4:
                if (!memory) {
                    printf("Memória não inicializada. Por favor, inicialize a memória primeiro.\n");
                    break;
                }
                mymemory_display(memory);
                break;

            case 5:
                if (!memory) {
                    printf("Memória não inicializada. Por favor, inicialize a memória primeiro.\n");
                    break;
                }
                mymemory_stats(memory);
                break;

            case 6:
                if (memory) {
                    mymemory_release(memory);
                    printf("Memória liberada\n");
                    break;
                }


                return 0;

            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        }
    }

    return 0;
}