#include <stdio.h>
#ifndef MYMEMORY_H
#define MYMEMORY_H


typedef struct allocation { //Elemento
    void *start; 
    size_t size;
    struct allocation *next;
} allocation_t;

typedef struct { //Lista
    void *pool; // ponteiro para o bloco de mem´oria real
    size_t total_size;
    allocation_t *head; // ponteiro para lista encadeada
} mymemory_t;

mymemory_t* mymemory_init(size_t size);

void* mymemory_alloc(mymemory_t *memory, size_t size);

void mymemory_free(mymemory_t *memory, void *ptr);

void mymemory_display(mymemory_t *memory);

void mymemory_stats(mymemory_t *memory);

void mymemory_release(mymemory_t *memory);



#endif