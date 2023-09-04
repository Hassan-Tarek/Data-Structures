/**
 *
 * @file     vector.h
 *
 * @brief    The Implementation of the vector
 * @author   Hassan Tarek
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* struct type declaration */
struct vector;

/* typedefs */
typedef struct vector vector;
typedef uint8_t byte;

/**
 * define the struct needed for the vector
 */
struct vector {
    byte* data;
    size_t size;
    size_t capacity;
    size_t element_size;
};


/** F U N C T I O N S   P R O T O T Y P E S **/

/* Initialization */
void vector_init(vector* vector, size_t element_size);
void vector_init_with(vector* vector, size_t vector_length, size_t element_size, void* initial_value);

/* Accessing */
void vector_back(const vector* vector, void* dest);
void vector_front(const vector* vector, void* dest);
void vector_at(const vector* vector, size_t index, void* dest);
int vector_index_of(const vector* vector, void* val);

/* Insertion */
void vector_push_back(vector* vector, void* val);
void vector_push_front(vector* vector, void* val);
void vector_insert_at(vector* vector, void* val, size_t index);
void vector_append_array(vector* vector, void* array, size_t array_size);

/* Removal */
void vector_pop_back(vector* vector);
void vector_pop_front(vector* vector);
void vector_remove_at(vector* vector, size_t index);
void vector_remove(vector* vector, void* val);
void vector_clear(vector* vector);
void vector_destroy(vector* vector);

/* Utility */
size_t vector_size(const vector* vector);
size_t vector_capacity(const vector* vector);
bool vector_is_empty(const vector* vector);
void vector_reserve(vector* vector, size_t new_capacity);
void vector_reverse(vector* vector);
void vector_trim(vector* vector);
void vector_copy_to_array(const vector* vector, void* array);
void vector_swap(vector* lhs, vector* rhs);
void* vector_get_data(const vector* vector);
void vector_sort(vector* vector, int (* compare)(const void* lhs, const void* rhs));


/* M A C R O S */

#define VECTOR_INIT_CAPACITY 100

#define vector_for_each(index, vector_ptr) \
    for (size_t index = 0;                 \
         index < (vector_ptr)->size;       \
         ++index)

#define vector_for_each_reverse(index, vector_ptr) \
    for (size_t index = (vector_ptr)->size - 1;    \
         index >= 0;                               \
         --index)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VECTOR_H */