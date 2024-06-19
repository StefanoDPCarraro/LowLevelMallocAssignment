#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

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
    // Primeiro alocamento
    if (memory->head == NULL)
    {
        if (memory->total_size > size)
        {
            allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
            newAlloc->size = size;
            newAlloc->start = memory->pool;
            memory->head = newAlloc;
            return newAlloc->start;
        }
        else
        {
            printf("Estouro de memoria");
            return NULL;
        }
    }

    else
    {

        allocation_t *headAux = memory->head;
        size_t acummulationSize = headAux->size;

        while (1)
        {

            if (headAux->next == NULL)
            {
                if ((acummulationSize + size) <= memory->total_size)
                {
                    allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
                    headAux->next = newAlloc;
                    newAlloc->size = size;
                    return newAlloc->start = headAux->start + headAux->size + 1;
                    break;
                }

                else
                {
                    printf("Estouro de memoria");
                    return NULL;
                    break;
                }
            }

            else
            {
                size_t gap = (headAux->next->start) - (headAux->start + headAux->size);
                if (gap < size)
                {
                    allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
                    newAlloc->next = headAux->next;
                    headAux->next = newAlloc;
                    newAlloc->size = size;
                    return newAlloc->start = headAux->start + headAux->size + 1;
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
