#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/vector.h"

/* Pointer Functions */
typedef void (* TestFunction) ();

/* Global Variables */
vector* first_vector;
vector* second_vector;
int vals[6] = {6, 1, 5, 2, 4, 3};
int rets[6];


/** T E S T   F U N C T I O N S **/

static void test_vector_init() {
    vector_init(first_vector, sizeof(int));
    assert(first_vector != NULL);
    assert(first_vector->data != NULL);
    assert(first_vector->size == 0);
    assert(first_vector->capacity == VECTOR_INIT_CAPACITY);
    assert(first_vector->element_size == sizeof(int));
    vector_destroy(first_vector);
    printf("test_vector_init passed!\n");
}

static void test_vector_init_with() {
    vector_init_with(second_vector, vals[5], sizeof(int), &vals[0]);
    vector_at(second_vector, 0, &rets[0]);
    assert(second_vector != NULL && second_vector->data != NULL);
    assert(second_vector->size == vals[5]);
    assert(second_vector->capacity == vals[5] * 2 + 1);
    assert(second_vector->element_size == sizeof(int));
    assert(rets[0] == vals[0]);
    vector_destroy(second_vector);
    printf("test_vector_init_with passed!\n");
}

static void test_vector_back() {
    vector_init(first_vector, sizeof(int));
    vector_push_back(first_vector, &vals[0]);
    vector_push_back(first_vector, &vals[1]);
    vector_back(first_vector, &rets[0]);
    assert(rets[0] == vals[1]);
    vector_destroy(first_vector);
    printf("test_vector_back passed!\n");
}

static void test_vector_front() {
    vector_init(first_vector, sizeof(int));
    vector_push_front(first_vector, &vals[0]);
    vector_push_front(first_vector, &vals[1]);
    vector_front(first_vector, &rets[0]);
    assert(rets[0] == vals[1]);
    vector_destroy(first_vector);
    printf("test_vector_front passed!\n");
}

static void test_vector_at() {
    vector_init(first_vector, sizeof(int));
    vector_push_back(first_vector, &vals[0]);
    vector_push_back(first_vector, &vals[1]);
    vector_push_front(first_vector, &vals[2]);
    vector_push_front(first_vector, &vals[3]);
    vector_at(first_vector, 0, &rets[0]);
    vector_at(first_vector, 1, &rets[1]);
    vector_at(first_vector, 2, &rets[2]);
    vector_at(first_vector, 3, &rets[3]);
    assert(rets[0] == vals[3]);
    assert(rets[1] == vals[2]);
    assert(rets[2] == vals[0]);
    assert(rets[3] == vals[1]);
    vector_destroy(first_vector);
    printf("test_vector_at passed!\n");
}

static void test_vector_index_of() {
    vector_init(first_vector, sizeof(int));
    vector_push_back(first_vector, &vals[0]);
    vector_push_back(first_vector, &vals[1]);
    vector_push_front(first_vector, &vals[2]);
    vector_push_front(first_vector, &vals[3]);
    vector_push_back(first_vector, &vals[4]);
    assert(vector_index_of(first_vector, &vals[0]) == 2);
    assert(vector_index_of(first_vector, &vals[1]) == 3);
    assert(vector_index_of(first_vector, &vals[2]) == 1);
    assert(vector_index_of(first_vector, &vals[3]) == 0);
    assert(vector_index_of(first_vector, &vals[4]) == 4);
    assert(vector_index_of(first_vector, &vals[5]) == -1);
    vector_destroy(first_vector);
    printf("test_vector_index_of passed!\n");
}

static void test_vector_push_back() {
    vector_init(first_vector, sizeof(int));
    vector_push_back(first_vector, &vals[0]);
    vector_push_back(first_vector, &vals[1]);
    vector_push_back(first_vector, &vals[2]);
    vector_push_back(first_vector, &vals[3]);
    vector_back(first_vector, &rets[0]);
    assert(first_vector->size == 4);
    assert(rets[0] == vals[3]);
    vector_destroy(first_vector);
    printf("test_vector_push_back passed!\n");
}

static void test_vector_push_front() {
    vector_init(first_vector, sizeof(int));
    vector_push_front(first_vector, &vals[0]);
    vector_push_front(first_vector, &vals[1]);
    vector_push_front(first_vector, &vals[2]);
    vector_push_front(first_vector, &vals[3]);
    vector_front(first_vector, &rets[0]);
    assert(first_vector->size == 4);
    assert(rets[0] == vals[3]);
    vector_destroy(first_vector);
    printf("test_vector_push_front passed!\n");
}

static void test_vector_insert_at() {
    vector_init(first_vector, sizeof(int));
    vector_insert_at(first_vector, &vals[0], 0);
    vector_insert_at(first_vector, &vals[1], 1);
    vector_insert_at(first_vector, &vals[2], 1);
    vector_insert_at(first_vector, &vals[3], 0);
    vector_front(first_vector, &rets[0]);
    vector_back(first_vector, &rets[1]);
    assert(first_vector->size == 4);
    assert(rets[0] == vals[3]);
    assert(rets[1] == vals[1]);
    vector_destroy(first_vector);
    printf("test_vector_insert_at passed!\n");
}

static void test_vector_append_array() {
    vector_init(first_vector, sizeof(int));
    vector_append_array(first_vector, vals, sizeof(vals) / sizeof(vals[0]));
    vector_at(first_vector, 0, &rets[0]);
    assert(first_vector->size == sizeof(vals) / sizeof(vals[0]));
    assert(rets[0] == vals[0]);
    vector_destroy(first_vector);
    printf("test_vector_append_array passed!\n");
}

static void test_vector_pop_back() {
    vector_init(first_vector, sizeof(int));
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    vector_pop_back(first_vector);
    vector_pop_back(first_vector);
    vector_back(first_vector, &rets[0]);
    assert(first_vector->size == (array_size - 2));
    assert(rets[0] == vals[3]);
    vector_destroy(first_vector);
    printf("test_vector_pop_back passed!\n");
}

static void test_vector_pop_front() {
    vector_init(first_vector, sizeof(int));
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    vector_pop_front(first_vector);
    vector_pop_front(first_vector);
    vector_front(first_vector, &rets[0]);
    assert(first_vector->size == (array_size - 2));
    assert(rets[0] == vals[2]);
    vector_destroy(first_vector);
    printf("test_vector_pop_front passed!\n");
}

static void test_vector_remove_at() {
    vector_init(first_vector, sizeof(int));
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    vector_remove_at(first_vector, 2);
    vector_remove_at(first_vector, 3);
    vector_at(first_vector, 2, &rets[0]);
    assert(first_vector->size == (array_size - 2));
    assert(rets[0] == vals[3]);
    vector_destroy(first_vector);
    printf("test_vector_remove_at passed!\n");
}

static void test_vector_remove() {
    vector_init(first_vector, sizeof(int));
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    vector_remove(first_vector, &vals[2]);
    vector_remove(first_vector, &vals[3]);
    vector_at(first_vector, 2, &rets[0]);
    assert(first_vector->size == (array_size - 2));
    assert(rets[0] == vals[4]);
    vector_destroy(first_vector);
    printf("test_vector_remove passed!\n");
}

static void test_vector_clear() {
    vector_init_with(second_vector, vals[5], sizeof(vals[0]), &vals[1]);
    vector_clear(second_vector);
    assert(second_vector->size == 0);
    assert(second_vector->data != NULL);
    vector_destroy(second_vector);
    printf("test_vector_clear passed!\n");
}

static void test_vector_destroy() {
    vector_init_with(second_vector, vals[5], sizeof(vals[0]), &vals[0]);
    vector_destroy(second_vector);
    assert(second_vector->data == NULL);
    printf("test_vector_destroy passed!\n");
}

static void test_vector_size() {
    vector_init(first_vector, sizeof(int));
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    assert(vector_size(first_vector) == array_size);
    vector_destroy(first_vector);
    printf("test_vector_size passed!\n");
}

static void test_vector_capacity() {
    vector_init(first_vector, sizeof(int));
    vector_init_with(second_vector, vals[5], sizeof(vals[0]), &vals[5]);
    int array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    assert(vector_capacity(first_vector) == VECTOR_INIT_CAPACITY);
    assert(vector_capacity(second_vector) == vals[5] * 2 + 1);
    vector_destroy(first_vector);
    vector_destroy(second_vector);
    printf("test_vector_capacity passed!\n");
}

static void test_vector_is_empty() {
    vector_init(first_vector, sizeof(int));
    assert(vector_is_empty(first_vector) == true);
    vector_push_back(first_vector, &vals[0]);
    assert(vector_is_empty(first_vector) == false);
    vector_destroy(first_vector);
    printf("test_vector_is_empty passed!\n");
}

static void test_vector_reserve() {
    vector_init(first_vector, sizeof(int));
    vector_reserve(first_vector, VECTOR_INIT_CAPACITY * 2);
    assert(vector_capacity(first_vector) == VECTOR_INIT_CAPACITY * 2);
    vector_destroy(first_vector);
    printf("test_vector_reserve passed!\n");
}

static void test_vector_reverse() {
    vector_init(first_vector, sizeof(int));
    vector_append_array(first_vector, vals, sizeof(vals) / sizeof(vals[0]));
    vector_reverse(first_vector);
    vector_front(first_vector, &rets[0]);
    vector_back(first_vector, &rets[1]);
    assert(rets[0] == vals[5]);
    assert(rets[1] == vals[0]);
    vector_destroy(first_vector);
    printf("test_vector_reverse passed!\n");
}

static void test_vector_trim() {
    vector_init(first_vector, sizeof(int));
    vector_trim(first_vector);
    assert(vector_capacity(first_vector) == 0);
    vector_destroy(first_vector);
    printf("test_vector_trim passed!\n");
}

static void test_vector_copy_to_array() {
    vector_init(first_vector, sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    vector_copy_to_array(first_vector, rets);
    for(int i = 0; i < array_size; i++) {
        assert(rets[i] == vals[i]);
    }
    vector_destroy(first_vector);
    printf("test_vector_copy_to_array passed!\n");
}

static void test_vector_swap() {
    vector_init(first_vector, sizeof(int));
    vector_init_with(second_vector, vals[5], sizeof(vals[0]), &vals[5]);
    vector_append_array(first_vector, vals, sizeof(vals) / sizeof(vals[0]));
    vector_swap(first_vector, second_vector);
    assert(vector_size(first_vector) == vals[5]);
    assert(vector_size(second_vector) == sizeof(vals) / sizeof(vals[0]));
    assert(vector_capacity(first_vector) == vals[5] * 2 + 1);
    assert(vector_capacity(second_vector) == VECTOR_INIT_CAPACITY);
    vector_copy_to_array(first_vector, rets);
    vector_for_each(index, first_vector) {
        assert(rets[index] == vals[5]);
    }
    vector_copy_to_array(second_vector, rets);
    vector_for_each(index, second_vector) {
        assert(rets[index] == vals[index]);
    }
    vector_destroy(first_vector);
    vector_destroy(second_vector);
    printf("test_vector_swap passed!\n");
}

static void test_vector_get_data() {
    vector_init(first_vector, sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    vector_append_array(first_vector, vals, array_size);
    int* data = (int *) vector_get_data(first_vector);
    for(size_t i = 0; i < array_size; i++) {
        assert(data[i] == vals[i]);
    }
    vector_destroy(first_vector);
    printf("test_vector_get_data passed!\n");
}

static int int_comparator(const void* lhs,  const void* rhs) {
    int left = *(const int *) lhs;
    int right = *(const int *) rhs;
    return left - right;
}

static void test_vector_sort() {
    vector_init(first_vector, sizeof(int));
    vector_append_array(first_vector, vals, sizeof(vals) / sizeof(vals[0]));
    vector_sort(first_vector, int_comparator);
    int* sorted_data = vector_get_data(first_vector);
    for(size_t i = 1; i < first_vector->size; i++) {
        assert(sorted_data[i] >= sorted_data[i - 1]);
    }
    vector_destroy(first_vector);
    printf("test_vector_sort passed!\n");
}


TestFunction test_functions[] = {
        test_vector_init,
        test_vector_init_with,
        test_vector_back,
        test_vector_front,
        test_vector_at,
        test_vector_index_of,
        test_vector_push_back,
        test_vector_push_front,
        test_vector_insert_at,
        test_vector_append_array,
        test_vector_pop_back,
        test_vector_pop_front,
        test_vector_remove_at,
        test_vector_remove,
        test_vector_clear,
        test_vector_destroy,
        test_vector_size,
        test_vector_capacity,
        test_vector_is_empty,
        test_vector_reserve,
        test_vector_reverse,
        test_vector_trim,
        test_vector_copy_to_array,
        test_vector_swap,
        test_vector_get_data,
        test_vector_sort
};

int main(int argc, char** argv) {
    size_t size = sizeof(test_functions) / sizeof(TestFunction);
    first_vector = (vector *) malloc(sizeof(vector));
    second_vector = (vector *) malloc(sizeof(vector));
    for(size_t i = 0; i < size; i++) {
        test_functions[i]();
    }
    printf("\033[0;32mAll tests passed!\n");
    free(first_vector);
    first_vector = NULL;
    free(second_vector);
    second_vector = NULL;
}
