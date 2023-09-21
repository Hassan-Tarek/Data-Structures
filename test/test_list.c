#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/list.h"

/* Pointer Functions */
typedef void (* TestFunction) ();

/* Global Variables */
list* list_ptrs[3];
int vals[6] = {6, 1, 5, 2, 4, 3};


/** T E S T   F U N C T I O N S **/

static void test_list_init() {
    list_init(list_ptrs[0], sizeof(int));
    assert(list_ptrs[0]->head == NULL);
    assert(list_ptrs[0]->tail == NULL);
    assert(list_ptrs[0]->size == 0);
    assert(list_ptrs[0]->element_size == sizeof(int));
    list_clear(list_ptrs[0]);
    printf("test_list_init passed!\n");
}

static void test_list_back() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_back(list_ptrs[0], &vals[0]);
    list_push_back(list_ptrs[0], &vals[1]);
    assert(*(int *) list_back(list_ptrs[0])->val == vals[1]);
    list_clear(list_ptrs[0]);
    printf("test_list_back passed!\n");
}

static void test_list_front() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_front(list_ptrs[0], &vals[0]);
    list_push_front(list_ptrs[0], &vals[1]);
    assert(*(int *) list_front(list_ptrs[0])->val == vals[1]);
    list_clear(list_ptrs[0]);
    printf("test_list_front passed!\n");
}

static void test_list_at() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_back(list_ptrs[0], &vals[0]);
    list_push_back(list_ptrs[0], &vals[1]);
    list_push_back(list_ptrs[0], &vals[2]);
    assert(*(int *) list_at(list_ptrs[0], 0)->val == vals[0]);
    assert(*(int *) list_at(list_ptrs[0], 1)->val == vals[1]);
    assert(*(int *) list_at(list_ptrs[0], 2)->val == vals[2]);
    list_clear(list_ptrs[0]);
    printf("test_list_at passed!\n");
}

static void test_list_index_of() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_back(list_ptrs[0], &vals[0]);
    list_push_back(list_ptrs[0], &vals[1]);
    list_push_back(list_ptrs[0], &vals[2]);
    assert(list_index_of(list_ptrs[0], &vals[0]) == 0);
    assert(list_index_of(list_ptrs[0], &vals[1]) == 1);
    assert(list_index_of(list_ptrs[0], &vals[2]) == 2);
    assert(list_index_of(list_ptrs[0], &vals[3]) == -1);
    list_clear(list_ptrs[0]);
    printf("test_list_index_of passed!\n");
}

static void test_list_push_back() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_back(list_ptrs[0], &vals[0]);
    list_push_back(list_ptrs[0], &vals[1]);
    list_push_back(list_ptrs[0], &vals[2]);
    assert(*(int *) list_ptrs[0]->head->val == vals[0]);
    assert(*(int *) list_ptrs[0]->tail->val == vals[2]);
    assert(list_ptrs[0]->size == 3);
    list_clear(list_ptrs[0]);
    printf("test_list_push_back passed!\n");
}

static void test_list_push_front() {
    list_init(list_ptrs[0], sizeof(int));
    list_push_front(list_ptrs[0], &vals[0]);
    list_push_front(list_ptrs[0], &vals[1]);
    list_push_front(list_ptrs[0], &vals[2]);
    assert(*(int *) list_ptrs[0]->head->val == vals[2]);
    assert(*(int *) list_ptrs[0]->tail->val == vals[0]);
    assert(list_ptrs[0]->size == 3);
    list_clear(list_ptrs[0]);
    printf("test_list_push_front passed!\n");
}

static void test_list_insert_at() {
    list_init(list_ptrs[0], sizeof(int));
    list_insert_at(list_ptrs[0], &vals[0], 0);
    list_insert_at(list_ptrs[0], &vals[1], 1);
    list_insert_at(list_ptrs[0], &vals[2], 2);
    assert(*(int *) list_at(list_ptrs[0], 0)->val == vals[0]);
    assert(*(int *) list_at(list_ptrs[0], 1)->val == vals[1]);
    assert(*(int *) list_at(list_ptrs[0], 2)->val == vals[2]);
    assert(list_ptrs[0]->size == 3);
    list_clear(list_ptrs[0]);
    printf("test_list_insert_at passed!\n");
}

static void test_list_pop_back() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_pop_back(list_ptrs[0]);
    list_pop_back(list_ptrs[0]);
    assert(*(int *) list_ptrs[0]->tail->val == vals[3]);
    assert(list_ptrs[0]->size == array_size - 2);
    list_clear(list_ptrs[0]);
    printf("test_list_pop_back passed!\n");
}

static void test_list_pop_front() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        list_push_front(list_ptrs[0], &vals[i]);
    }
    list_pop_front(list_ptrs[0]);
    list_pop_front(list_ptrs[0]);
    assert(*(int *) list_ptrs[0]->head->val == vals[3]);
    assert(list_ptrs[0]->size == array_size - 2);
    list_clear(list_ptrs[0]);
    printf("test_list_pop_front passed!\n");
}

static void test_list_remove_at() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_remove_at(list_ptrs[0], 0);
    list_remove_at(list_ptrs[0], 1);
    list_remove_at(list_ptrs[0], 3);
    assert(*(int *) list_ptrs[0]->head->val == vals[1]);
    assert(*(int *) list_ptrs[0]->tail->val == vals[4]);
    assert(list_ptrs[0]->size == array_size - 3);
    list_clear(list_ptrs[0]);
    printf("test_list_remove_at passed!\n");
}

static void test_list_remove() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_remove(list_ptrs[0], &vals[0]);
    list_remove(list_ptrs[0], &vals[3]);
    list_remove(list_ptrs[0], &vals[5]);
    assert(*(int *) list_ptrs[0]->head->val == vals[1]);
    assert(*(int *) list_ptrs[0]->tail->val == vals[4]);
    assert(list_ptrs[0]->size == array_size - 3);
    list_clear(list_ptrs[0]);
    printf("test_list_remove passed!\n");
}

static void test_list_clear() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_clear(list_ptrs[0]);
    assert(list_ptrs[0]->head == NULL);
    assert(list_ptrs[0]->tail == NULL);
    assert(list_ptrs[0]->size == 0);
    printf("test_list_clear passed!\n");
}

static void test_list_size() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    assert(list_size(list_ptrs[0]) == array_size);
    list_clear(list_ptrs[0]);
    printf("test_list_size passed!\n");
}

static void test_list_is_empty() {
    list_init(list_ptrs[0], sizeof(int));
    list_init(list_ptrs[1], sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    assert(list_is_empty(list_ptrs[0]) == false);
    assert(list_is_empty(list_ptrs[1]) == true);
    list_clear(list_ptrs[0]);
    list_clear(list_ptrs[1]);
    printf("test_list_is_empty passed!\n");
}

static void test_list_merge() {
    for(size_t i = 0; i < sizeof(list_ptrs) / sizeof(list_ptrs[0]); i++) {
        list_init(list_ptrs[i], sizeof(int));
    }
    list_push_back(list_ptrs[0], &vals[0]);
    list_push_back(list_ptrs[0], &vals[1]);
    list_push_back(list_ptrs[0], &vals[2]);
    list_push_back(list_ptrs[1], &vals[3]);
    list_push_back(list_ptrs[1], &vals[4]);
    list_push_back(list_ptrs[1], &vals[5]);
    list_merge(list_ptrs[0], list_ptrs[1], list_ptrs[2]);
    size_t offset = 0;
    list_for_each(node, list_ptrs[2]) {
        assert(*(int *) node->val == vals[offset]);
        offset++;
    }
    assert(list_ptrs[2]->size == list_ptrs[0]->size + list_ptrs[1]->size);
    for(size_t i = 0; i < sizeof(list_ptrs) / sizeof(list_ptrs[0]); i++) {
        list_clear(list_ptrs[i]);
    }
    printf("test_list_merge passed!\n");
}

static void test_list_reverse() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_reverse(list_ptrs[0]);
    size_t offset = 0;
    list_for_each_reverse(node, list_ptrs[0]) {
        assert(*(int *) node->val == vals[offset]);
        offset++;
    }
    list_clear(list_ptrs[0]);
    printf("test_list_reverse passed!\n");
}

static void test_list_copy_to_array() {
    list_init(list_ptrs[0], sizeof(int));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for (size_t i = 0; i < array_size; i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    int* array = (int *) malloc(sizeof(int) * array_size);
    list_copy_to_array(list_ptrs[0], array);
    for(size_t i = 0; i < array_size; i++) {
        assert(vals[i] == array[i]);
    }
    list_clear(list_ptrs[0]);
    free(array);
    array = NULL;
    printf("test_list_copy_to_array passed!\n");
}

static int compare_nodes(const void* left, const void* right) {
    const node* left_node = *(const node**) left;
    const node* right_node = *(const node**) right;

    int left_val = *(int*) (left_node->val);
    int right_val = *(int*) (right_node->val);

    return left_val - right_val;
}

static void test_list_sort() {
    list_init(list_ptrs[0], sizeof(int));
    for (size_t i = 0; i < sizeof(vals) / sizeof(vals[0]); i++) {
        list_push_back(list_ptrs[0], &vals[i]);
    }
    list_sort(list_ptrs[0], compare_nodes);
    list_for_each(node, list_ptrs[0]) {
        if (node->prev) {
            assert(*(int *) node->prev->val <= *(int *) node->val);
        }
    }
    list_clear(list_ptrs[0]);
    printf("test_list_sort passed!\n");
}

TestFunction test_functions[] = {
        test_list_init,
        test_list_back,
        test_list_front,
        test_list_at,
        test_list_index_of,
        test_list_push_back,
        test_list_push_front,
        test_list_insert_at,
        test_list_pop_back,
        test_list_pop_front,
        test_list_remove_at,
        test_list_remove,
        test_list_clear,
        test_list_size,
        test_list_is_empty,
        test_list_merge,
        test_list_reverse,
        test_list_copy_to_array,
        test_list_sort
};

int main(int argc, char** argv) {
    size_t tests_size = sizeof(test_functions) / sizeof(TestFunction);
    size_t lists_size = sizeof(list_ptrs) / sizeof(list_ptrs[0]);
    for(size_t i = 0; i < lists_size; i++) {
        list_ptrs[i] = (list *) malloc(sizeof(list));
    }
    for(size_t i = 0; i < tests_size; i++) {
        test_functions[i]();
    }
    printf("\033[0;32mAll tests passed!\n");
    for(size_t i = 0; i < lists_size; i++) {
        free(list_ptrs[i]);
        list_ptrs[i] = NULL;
    }
    return 0;
}