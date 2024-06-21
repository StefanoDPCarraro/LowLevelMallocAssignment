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