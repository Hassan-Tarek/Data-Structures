#include "vector.h"

/**
 * @brief Initializes the vector.
 *
 * @param vector The vector to be initialized.
 * @param element_size The size in bytes of each element in the vector.
 */
void vector_init(vector* vector, size_t element_size) {
    assert(vector != NULL && element_size > 0);

    vector->data = (byte *)malloc(VECTOR_INIT_CAPACITY * sizeof(byte) * element_size);
    vector->size = 0;
    vector->capacity = VECTOR_INIT_CAPACITY;
    vector->element_size = element_size;
}

/**
 * @brief Initializes the vector with a default value.
 *
 * @param vector The vector to be initialized.
 * @param vector_length The initial length of the vector.
 * @param element_size The size in bytes of each element in the vector.
 * @param initial_value The default value the vector will be initialized with.
 */
void vector_init_with(vector* vector, size_t vector_length, size_t element_size, void* initial_value) {
    assert(vector != NULL && element_size > 0);
    vector->data = malloc(sizeof(byte) * (2 * vector_length + 1) * element_size);

    assert(vector->data != NULL);
    vector->size = vector_length;
    vector->capacity = vector_length * 2 + 1;
    vector->element_size = element_size;
    for(size_t i = 0; i < vector_length; i++) {
        memcpy(vector->data + i * vector->element_size, initial_value, sizeof(byte) * vector->element_size);
    }
}

/**
 * @brief Copies the element data at the end from a vector to a pre-allocated memory block.
 *
 * @param vector The vector from which the last element will be retrieved.
 * @param dest Index of the element to retrieve.
 */
void vector_back(const vector* vector, void* dest) {
    vector_at(vector, vector->size - 1, dest);
}

/**
 * @brief Copies the element data at the begin from a vector to a pre-allocated memory block.
 *
 * @param vector The vector from which the first element will be retrieved.
 * @param dest Index of the element to retrieve.
 */
void vector_front(const vector* vector, void* dest) {
    vector_at(vector, 0, dest);
}

/**
 * @brief Copies the element data at the specified index from a vector to a pre-allocated memory block.
 *
 * @param vector The vector from which the element at the specified index will be returned.
 * @param index The index of the wanted element.
 * @param dest Index of the element to retrieve.
 */
void vector_at(const vector* vector, size_t index, void* dest) {
    assert(vector != NULL && vector->data != NULL && index < vector->size && dest != NULL);

    memcpy(dest, vector->data + index * vector->element_size,
           sizeof(byte) * vector->element_size);
}


/**
 * @brief Retrieves the index of the specified value or -1 if it's not found.
 *
 * @param vector The vector to be searched.
 * @param val The value to be searched for.
 *
 * @return The index of the specified value or -1 if it's not found.
 */
int vector_index_of(const vector* vector, void* val) {
    assert(vector != NULL && vector->data != NULL && val != NULL);

    vector_for_each(index, vector) {
        int cmp = memcmp(vector->data + index * vector->element_size, val,
                         sizeof(byte) * vector->element_size);
        if(cmp == 0) {
            return (int) index;
        }
    }
    return -1;
}

/**
 * @brief Insert the specified value into the end of the vector.
 *
 * @param vector A pointer to a vector to add to.
 * @param val The value to be added to the vector.
 */
void vector_push_back(vector* vector, void* val) {
    assert(vector != NULL && vector->data != NULL && val != NULL);

    vector_insert_at(vector, val, vector->size);
}

/**
 * @brief Insert the specified value into the front of the vector.
 *
 * @param vector A pointer to a vector to add to.
 * @param val The value to be added to the vector.
 */
void vector_push_front(vector* vector, void* val) {
    assert(vector != NULL && vector->data != NULL && val != NULL);

    vector_insert_at(vector, val, 0);
}

/**
 * @brief Insert the specified value into the specified index of the vector.
 *
 * @param vector A pointer to a vector to add to.
 * @param val The value to be added to the vector.
 * @param index The index at which the value should be inserted.
 */
void vector_insert_at(vector* vector, void* val, size_t index) {
    assert(vector != NULL && vector->data != NULL && val != NULL && index <= vector->size);

    if (vector->capacity <= vector->size * 2) {
        vector_reserve(vector, (vector->size * 2) + 1);
    }

    if (index != vector->size) {
        memmove(vector->data + (index + 1) * vector->element_size,
                vector->data + index * vector->element_size,
                sizeof(byte) * (vector->size - index) * vector->element_size);
    }
    memcpy(vector->data + index * vector->element_size,
           val, vector->element_size);
    vector->size += 1;
}

/**
 * @brief Append the specified array to the end of the vector.
 *
 * @param vector A pointer to a vector to add to.
 * @param array The array to be appended to the vector.
 * @param array_size The number of elements in the specified array.
 */
void vector_append_array(vector* vector, void* array, size_t array_size) {
    assert(vector != NULL && vector->data != NULL && array != NULL);

    if(vector->capacity <= (vector->size + array_size) * 2)
        vector_reserve(vector, (vector->size + array_size) * 2 + 1);
    memcpy(vector->data + vector->size * vector->element_size,
           array, array_size * vector->element_size);
    vector->size += array_size;
}

/**
 * @brief Remove the last element from the vector.
 *
 * @param vector A pointer to the vector to remove from.
 */
void vector_pop_back(vector* vector) {
    vector_remove_at(vector, vector->size - 1);
}

/**
 * @brief Remove the first element from the vector.
 *
 * @param vector A pointer to the vector to remove from.
 */
void vector_pop_front(vector* vector) {
    vector_remove_at(vector, 0);
}

/**
 * @brief Remove the element at the specified index from the vector.
 *
 * @param vector A pointer to the vector to remove from.
 * @param index The index of the value wanted to be removed from the vector.
 */
void vector_remove_at(vector* vector, size_t index) {
    assert(vector != NULL && vector->data != NULL && index < vector->size);

    memmove(vector->data + index * vector->element_size,
            vector->data + (index + 1) * vector->element_size,
            sizeof(byte) * (vector->size - index - 1) * vector->element_size);
    vector->size -= 1;
}

/**
 * @brief Remove all occurrences of the specified value from the vector.
 *
 * @param vector A pointer to the vector to remove from.
 * @param val the value to be removed from the vector.
 */
void vector_remove(vector* vector, void* val) {
    assert(vector != NULL && vector->data != NULL && val != NULL);

    vector_for_each(index, vector) {
        int cmp = memcmp(vector->data + index * vector->element_size, val,
                         sizeof(byte) * vector->element_size);
        if(cmp == 0) {
            vector_remove_at(vector, index);
        }
    }
}

/**
 * @brief Remove all the vector elements.
 *
 * @param vector A pointer to the vector to remove from.
 */
void vector_clear(vector* vector) {
    assert(vector != NULL && vector->data != NULL);

    while(vector->size > 0) {
        vector_pop_back(vector);
    }
}

/**
 * @brief Frees the memory allocated for the vector data.
 *
 * @param vector A pointer to the vector to free from.
 */
void vector_destroy(vector* vector) {
    assert(vector != NULL);

    if(vector) {
        free(vector->data);
        vector->data = NULL;
    }
}

/**
 * @brief Gets the size of the specified vector.
 *
 * @param vector The vector whose size will be returned.
 *
 * @return The size of the specified vector.
 */
size_t vector_size(const vector* vector) {
    assert(vector != NULL);

    return vector->size;
}

/**
 * @brief Gets the capacity of the vector.
 *
 * @param vector The vector whose capacity will be returned.
 *
 * @return The capacity of the specified vector.
 */
size_t vector_capacity(const vector* vector) {
    assert(vector != NULL);

    return vector->capacity;
}

/**
 * @brief Checks whether the vector is empty or not.
 *
 * @param vector The vector to be checked.
 *
 * @return Whether or not the vector is empty.
 */
bool vector_is_empty(const vector* vector) {
    assert(vector != NULL);

    return vector->size == 0;
}

/**
 * @brief Reserves the required space for the specified vector.
 *
 * @param vector The vector for which we will reserve a space.
 * @param new_capacity The new capacity to reserve for the vector.
 */
void vector_reserve(vector* vector, size_t new_capacity) {
    assert(vector != NULL);

    vector->data = realloc(vector->data, sizeof(byte) * new_capacity * vector->element_size);
    vector->capacity = new_capacity;
}

/**
 * @brief Reverses the vector data.
 *
 * @param vector The vector whose data will be reversed.
 */
void vector_reverse(vector* vector) {
    assert(vector != NULL && vector->data != NULL);

    size_t left = 0;
    size_t right = vector->size - 1;
    void* temp = (void *) malloc(vector->element_size);
    while(left < right) {
        void* left_ptr = vector->data + left * vector->element_size;
        void* right_ptr = vector->data + right * vector->element_size;
        mempcpy(temp, left_ptr, vector->element_size);
        memcpy(left_ptr, right_ptr, vector->element_size);
        memcpy(right_ptr, temp, vector->element_size);

        left++;
        right--;
    }
    free(temp);
    temp = NULL;
}

/**
 * @brief Deallocates the unused memory
 *
 * @param vector The vector to trim from.
 */
void vector_trim(vector* vector) {
    assert(vector != NULL);

    vector->data = realloc(vector->data, sizeof(byte) * vector->size * vector->element_size);
    vector->capacity = vector->size;
}

/**
 * @brief Copies the vector data to the specified array.
 *
 * @param vector The vector that the specified array wil be copied into.
 * @param array The array to be copied to the specified vector.
 */
void vector_copy_to_array(const vector* vector, void* array) {
    assert(vector != NULL && array != NULL);

    memcpy(array, vector->data, vector->size * vector->element_size);
}

/**
 * @brief Swaps two vectors.
 *
 * @param lhs A pointer to the first vector.
 * @param rhs A pointer to the second vector.
 */
void vector_swap(vector* lhs, vector* rhs) {
    assert(lhs != NULL && rhs != NULL && lhs->element_size == rhs->element_size);

    void* temp_data = lhs->data;
    lhs->data = rhs->data;
    rhs->data = temp_data;

    size_t temp_size = lhs->size;
    lhs->size = rhs->size;
    rhs->size = temp_size;

    size_t temp_capacity = lhs->capacity;
    lhs->capacity = rhs->capacity;
    rhs->capacity = temp_capacity;
}

/**
 * @brief Gets the vector data.
 *
 * @param vector The vector whose data will be returned.
 *
 * @return The data of the specified vector.
 */
void* vector_get_data(const vector* vector) {
    assert(vector != NULL);

    return vector->data;
}

/**
 * @brief Sorts the specified vector.
 *
 * @param vector The vector whose data will be sorted.
 * @param compare The compare function used to sort the vector.
 */
void vector_sort(vector* vector, int (* compare)(const void* lhs, const void* rhs)) {
    assert(vector != NULL);

    qsort(vector->data, vector->size,
          sizeof(byte) * vector->element_size,compare);
}
