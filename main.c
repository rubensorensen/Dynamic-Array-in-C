#include "array.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uint32_t* arr = array_alloc(uint32_t);
    
    for (uint32_t i = 0; i < 50; ++i) {
        array_push(arr, i);
    }
    
    for (uint32_t i = 0; i < 50; ++i) {
        array_push_rval(arr, uint32_t, i * 3);
    }
    
    for (uint32_t i = 0; i < 10; ++i) {
        uint32_t val;
        array_pop(arr, &val);
        printf("Popped %u\n", val);
    }

    for (uint32_t i = 0; i < 5; ++i) {
        uint32_t index = rand() % array_size(arr);
        array_erase(arr, index);
    }
    
    for (uint32_t i = 0; i < 5; ++i) {
        uint32_t index = rand() % array_size(arr);
        array_erase_fast(arr, index);
    }
    
    for (uint32_t i = 0; i < array_size(arr); ++i) {
        printf("[%u] %u\n", i, arr[i]);
    }
    
    array_free(arr);
    
    return 0;
}
