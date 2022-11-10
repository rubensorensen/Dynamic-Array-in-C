#ifndef _ARRAY_H
#define _ARRAY_H

#include <stdint.h>

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef double f64;
typedef float  f32;

#define DEFAULT_ARRAY_INIT_SIZE  10
#define RESIZE_SCALE_FACTOR      2

// Public API
#define array_alloc(type)              _array_alloc(DEFAULT_ARRAY_INIT_SIZE, sizeof(type))
#define array_alloc_x(type, init_size) _array_alloc(x, sizeof(type))
#define array_free(arr)                _array_free(arr)

#define array_size(arr)             _array_size(arr)
#define array_resize(arr, new_size) arr = _array_resize(arr, new_size)

#define array_push(arr, x)                    arr = _array_push(arr, (void*)&x)
#define array_push_rval(arr, type, x)         { type temp = x; array_push(arr, temp); }
#define array_push_at(arr, loc, x)            arr = _array_push_at(arr, loc, (void*)&x)
#define array_push_rval_at(arr, loc, type, x) { type temp = x; array_push_at(arr, loc, temp); }

#define array_pop(arr, dest) _array_pop(arr, dest)
#define array_pop_void(arr)  { void* temp; _array_pop(arr, temp); }

#define array_erase(arr, loc)      _array_erase(arr, loc)
#define array_erase_fast(arr, loc) _array_erase_fast(arr, loc)

// Private defitions
void* _array_alloc(u32 init_capacity, u32 stride);
void _array_free(void* arr);
u32 _array_size(void* arr);
void* _array_resize(void* arr, u32 new_capacity);
void* _array_push(void* arr, void* ptr_to_val);
void* _array_push_at(void* arr, u32 loc, void* ptr_to_val);
void _array_pop(void* arr, void* dest);
void _array_erase(void* arr, u32 loc);
void _array_erase_fast(void* arr, u32 loc);

#endif // _ARRAY_H
