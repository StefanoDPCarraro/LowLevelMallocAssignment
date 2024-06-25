#include <stdio.h>
#include <stdlib.h>
#include "mymemory.h"

mymemory_t *mymemory_init(size_t size)
{
    mymemory_t *memory = (mymemory_t *)malloc(sizeof(mymemory_t));
    memory->pool = malloc(size);
    memory->total_size = size;
    memory->head = NULL;
    return memory;
}

void *mymemory_alloc(mymemory_t *memory, size_t size)
{

    //  Primeiro alocamento

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

    // Caso o primeiro nodo nao comecar no memory pool
    else if (memory->pool != memory->head->start)
    {
        if (memory->head->start - memory->pool > size)
        {
            allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
            newAlloc->size = size;
            newAlloc->start = memory->pool;
            newAlloc->next = memory->head;
            memory->head = newAlloc;
            return newAlloc->start;
        }
    }

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
                newAlloc->start = headAux->start + headAux->size + 1;
                return newAlloc->start;
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
            if (gap > size)
            {
                allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
                newAlloc->next = headAux->next;
                headAux->next = newAlloc;
                newAlloc->size = size;
                newAlloc->start = headAux->start + headAux->size + 1;
                return newAlloc->start;
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

// void mymemory_free(mymemory_t *memory, void *ptr)
// {

//     // Se for o primeiro elemento
//     if (memory->head->start == ptr)
//     {
//         if (memory->head->next == NULL)
//         {
//             int memorysize = memory->head->size;

//             for (int i = 0; i < memorysize - 1; i++)
//             {
//                 ((void **)memory->head->start)[i] = NULL;
//             }

//             memory->head = NULL;
//         }
//         else
//         {
//             int memorysize = memory->head->size;
//             memory->head = memory->head->next;

//             for (int i = 0; i < memorysize - 1; i++)
//             {
//                 ((void **)memory->head->start)[i] = NULL;
//             }
//         }
//     }
//     else
//     {

//         allocation_t *aux = memory->head;

//         while (1)
//         {
//             if (aux->next->start == ptr)
//             {
//                 allocation_t *aux2 = aux->next;
//                 if (aux2->next != NULL)
//                 {
//                     aux->next = aux2->next;
//                     int memorysize = aux2->size;
//                     for (int i = 0; i < memorysize - 1; i++)
//                     {
//                         ((void **)aux2->start)[i] = NULL;
//                     }
//                     break;
//                 }
//                 else
//                 {
//                     int memorysize = aux2->size;
//                     for (int i = 0; i < memorysize - 1; i++)
//                     {
//                         ((void **)aux2->start)[i] = NULL;
//                     }
//                     aux->next = NULL;
//                     break;
//                 }
//             }

//             else if (aux->next == NULL)
//             {
//                 printf("Partição inválida\n");
//                 break;
//             }
//             else
//             {
//                 aux = aux->next;
//             }
//         }
//     }
// }

void mymemory_free(mymemory_t *memory, void *ptr)
{
    if (memory == NULL || memory->head == NULL || ptr == NULL)
    {
        return;
    }

    allocation_t *headAux = memory->head;
    allocation_t *prevHead = NULL; // prevHead para arrumar a lista depois que o nodo a ser removido for encontrado

    while (headAux != NULL)
    {
        if (headAux->start == ptr) //Se encontrar a particao
        {
            if (prevHead == NULL)
            {
                memory->head = headAux->next;
            }
            else
            {
                prevHead->next = headAux->next; // Aponta para o proximo depois de de Head
            }

            free(ptr);
            free(headAux);

            return;
        }

        prevHead = headAux;
        headAux = prevHead->next;
    }

    // Caso não encontre o ptr na lista
    printf("Partição inválida\n");
}

void mymemory_display(mymemory_t *memory)
{
    if (memory->head != NULL)
    {
        allocation_t *newAlloc = (allocation_t *)malloc(sizeof(allocation_t));
        newAlloc = memory->head;
        int count = 1;
        while (1)
        {

            printf("Alocação: %d  Inicio: %p  Tamanho: %ld\n", count, newAlloc->start, newAlloc->size);
            if (newAlloc->next != NULL)
            {
                newAlloc = newAlloc->next;
                count++;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("Não há nada alocado na memória");
    }
}

void mymemory_stats(mymemory_t *memory)
{
    if (memory->pool != NULL)
    {
        if (memory->head != NULL)
        {
            allocation_t *headAux = memory->head;
            int countAllocations = 0;
            int countFragmentationMemories = 0;
            int countFreeMemory = memory->total_size;
            int biggestFreeGap = 0;

            while (headAux != NULL)
            {
                countAllocations++;
                countFreeMemory -= headAux->size;

                if (headAux->next != NULL)
                {
                    int gap = headAux->next->start - (headAux->start + headAux->size);
                    if (gap > 1)
                    {
                        countFragmentationMemories++;
                        if (biggestFreeGap < gap)
                        {
                            biggestFreeGap = gap;
                        }
                    }
                }

                headAux = headAux->next;
            }
            if (countFragmentationMemories == 0)
                countFragmentationMemories = 1;
            printf("Tamanho da memória: %ld  Número total de alocações: %d  Memória total alocada: %ld  Memória total livre: %d \nMaior bloco contiguo de memória livre: %d  Número de fragmentos de memória livre: %d\n", memory->total_size, countAllocations, memory->total_size - countFreeMemory, countFreeMemory, biggestFreeGap - 1, countFragmentationMemories);
        }
        else
        {
            printf("Memória alocadada: %ld\n", memory->total_size);
        }
    }
    else
    {
        printf("Não há memória alocadada\n");
    }
}

void mymemory_release(mymemory_t *memory)
{
    while (memory->head != NULL)
    {
        mymemory_free(memory, memory->head->start);
    }
    free(memory);
}
