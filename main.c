#include <stdio.h>
#include "mymemory.h"

int main()
{
    // aloca pool memoria
    mymemory_t *memory = mymemory_init(1000000);

    //int v[32];
    // int *v = malloc(sizeof(int)*32);
    int *v = mymemory_alloc(memory, sizeof(int)*64);
    for (int i = 0; i < 32; i++)
        v[i] = i+1;


    int *v2 = mymemory_alloc(memory, sizeof(int)*16);


    mymemory_display(memory);

    

     char *str = mymemory_alloc(memory, sizeof(char)*16);


    // free(v);
    mymemory_free(memory, v);

    printf("aaaaaaaaa");
    mymemory_display(memory);

    int *v3 = mymemory_alloc(memory, sizeof(int)*32);

 mymemory_display(memory);


     sprintf(str, "ola mundo");
     printf("v2: %p\n", (void*)v2);
      printf("v3: %p\n", (void*)v3);
    // libera o pool de memoria
    mymemory_release(memory);



 mymemory_display(memory);


    return 0;
}
