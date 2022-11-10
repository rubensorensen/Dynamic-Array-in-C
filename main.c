#include "array.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    u32* arr = array_alloc(u32);
    
    for (u32 i = 0; i < 50; ++i) {
        array_push(arr, i);
    }
    
    for (u32 i = 0; i < 50; ++i) {
        array_push_rval(arr, u32, i * 3);
    }
    
    for (u32 i = 0; i < 10; ++i) {
        u32 val;
        array_pop(arr, &val);
        printf("Popped %u\n", val);
    }

    for (u32 i = 0; i < 5; ++i) {
        u32 index = rand() % array_size(arr);
        array_erase(arr, index);
    }
    
    for (u32 i = 0; i < 5; ++i) {
        u32 index = rand() % array_size(arr);
        array_erase_fast(arr, index);
    }
    
    for (u32 i = 0; i < array_size(arr); ++i) {
        printf("[%u] %u\n", i, arr[i]);
    }
    
    array_free(arr);
    
    return 0;
}
