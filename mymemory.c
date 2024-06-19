#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

typedef struct allocation
{                            // Elemento
    void *start;             // inicio da posicao da memoria
    size_t size;             // Total do tamanho da alocacao do elemento
    struct allocation *next; // proximo element
} allocation_t;

typedef struct
{                       // Lista
    void *pool;         // ponteiro para o bloco de mem´oria real
    size_t total_size;  // Tamanho total da lista
    allocation_t *head; // ponteiro para lista encadeada
} mymemory_t;

mymemory_t *mymemory_init(size_t size)
{
    mymemory_t *memory = (mymemory_t *)malloc(sizeof(size));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}

void *mymemory_alloc(mymemory_t *memory, size_t size)
{
    allocation_t *headAux = memory->head;
    size_t *acummulationSize = headAux->size;

    while (1)
    {

        if (headAux->next == NULL)
        {
            if ((acummulationSize + size) <= memory->total_size)
            {
                allocation_t *newAlloc;
                headAux->next = newAlloc;
                newAlloc->size = size;
                newAlloc->start = headAux->start + headAux->size + 1;
                break;
            }

            else{
                printf('Estouro de memoria');
                break;
            }
        }

        else
        {
            size_t gap = (headAux->next->start) - (headAux->start + headAux->size);
            if (gap < size)
            {
                allocation_t *newAlloc;
                newAlloc->next = headAux->next;
                headAux->next = newAlloc;
                newAlloc->size = size;
                newAlloc->start = headAux->start + headAux->size + 1;
                break;
            }
            else
            {

                headAux = headAux->next;
                acummulationSize += headAux->size + gap;
            }
        }
    }
}

void mymemory_free(mymemory_t *memory, void *ptr)
{
}

void mymemory_display(mymemory_t *memory)
{
}

void mymemory_stats(mymemory_t *memory)
{
}

void mymemory_release(mymemory_t *memory)
{
    free(memory);
    printf("A memória foi limpa");
}
