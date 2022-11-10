#include "array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum _ARRAY_FIELD {
    ARRAY_FIELD_STRIDE = 0,
    ARRAY_FIELD_CAPACITY,
    ARRAY_FIELD_SIZE,
    ARRAY_FIELD_ENUM_COUNT
} ARRAY_FIELD;

#define HEADER_SIZE (sizeof(u32) * ARRAY_FIELD_ENUM_COUNT)

#define _array_get_stride(arr)    _array_get_field(arr, ARRAY_FIELD_STRIDE)
#define _array_get_capacity(arr)  _array_get_field(arr, ARRAY_FIELD_CAPACITY)
#define _array_get_size(arr)      _array_get_field(arr, ARRAY_FIELD_SIZE)

u32
_array_get_field(void* arr, ARRAY_FIELD field)
{
    return ((u32*)arr - ARRAY_FIELD_ENUM_COUNT)[field];
}

u32
_array_size(void* arr)
{
    return _array_get_size(arr);
}

#define _array_set_stride(arr, val)    _array_set_field(arr, ARRAY_FIELD_STRIDE, val)
#define _array_set_capacity(arr, val)  _array_set_field(arr, ARRAY_FIELD_CAPACITY, val)
#define _array_set_size(arr, val)      _array_set_field(arr, ARRAY_FIELD_SIZE, val)

void
_array_set_field(void* arr, ARRAY_FIELD field, u32 val)
{
    ((u32*)arr - ARRAY_FIELD_ENUM_COUNT)[field] = val;
}

void*
_array_alloc(u32 init_capacity, u32 stride) {
    u32 array_size = init_capacity * stride;
    u32* array = (u32*)malloc(HEADER_SIZE + array_size);
    
    array[ARRAY_FIELD_STRIDE]   = stride;
    array[ARRAY_FIELD_CAPACITY] = init_capacity;
    array[ARRAY_FIELD_SIZE]     = 0;
    
    return (void*)(array + ARRAY_FIELD_ENUM_COUNT);
}

void
_array_free(void* arr)
{
    if (arr != 0) {
        char* ptr = (char*)arr - HEADER_SIZE;
        if (ptr) {
            free(ptr);
        }
    }
}

void*
_array_resize(void* arr, u32 new_capacity)
{
    u32 stride  = _array_get_stride(arr);
    u32 size    = _array_get_size(arr);
    
    assert(size <= new_capacity);
    
    void* temp = _array_alloc(new_capacity, stride);
    memcpy(temp, arr, size * stride);
    _array_set_size(temp, size);
    _array_free(arr);
    
    return temp;
}

void*
_array_push(void* arr, void* ptr_to_val)
{
    u32 size   = _array_get_size(arr);
    u32 cap    = _array_get_capacity(arr);
    u32 stride = _array_get_stride(arr);
    
    if (size >= cap) {
        arr = _array_resize(arr, cap * RESIZE_SCALE_FACTOR);
    }
    
    char* dest = ((char*)arr) + size * stride;
    memcpy(dest, ptr_to_val, stride);
    _array_set_size(arr, size + 1);
    
    return arr;
}

void*
_array_push_at(void* arr, u32 loc, void* ptr_to_val)
{
    u32 size   = _array_get_size(arr);
    u32 cap    = _array_get_capacity(arr);
    u32 stride = _array_get_stride(arr);
    
    if (size >= cap) {
        arr = _array_resize(arr, cap * RESIZE_SCALE_FACTOR);
    }
    
    u32 i = _array_get_size(arr);
    while (i > loc) {
        memcpy((char*)arr + (i * stride), (char*)arr + ((i - 1) * stride), stride);
        i -= 1;
    }
    
    char* dest = ((char*)arr) + loc * stride;
    memcpy(dest, ptr_to_val, stride);
    _array_set_size(arr, size + 1);
    
    return arr;
}

void
_array_pop(void* arr, void* dest)
{
    u32 size = _array_get_size(arr);
    u32 stride = _array_get_stride(arr);
    
    assert(size > 0);
    memcpy(dest, (char*)arr + ((size - 1) * stride), stride);
    _array_set_size(arr, size - 1);
}

// array_erase preserves order
void
_array_erase(void* arr, u32 loc)
{
    u32 size = _array_get_size(arr);
    u32 stride = _array_get_stride(arr);
    
    while (loc < size - 1) {
        memcpy((char*)arr + (loc * stride), (char*)arr + ((loc + 1) * stride), stride);
        loc += 1;
    }
    _array_set_size(arr, size - 1);
}

// array_erase_fast does NOT preserve order
void
_array_erase_fast(void* arr, u32 loc)
{
    u32 size = _array_get_size(arr);
    u32 stride = _array_get_stride(arr);
    
    if (loc >= size) {
        return;
    }
    
    memcpy((char*)arr + (loc * stride), (char*)arr + ((size - 1) * stride), stride);
    _array_set_size(arr, size - 1);
}
