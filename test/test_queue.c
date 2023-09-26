#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/queue.h"

/* Pointer Functions */
typedef void (* TestFunction) ();

/* Global Variables */
queue* queue_ptr;
double vals[6] = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};


/** T E S T   F U N C T I O N S **/

static void test_queue_init() {
    queue_init(queue_ptr, sizeof(double));
    assert(queue_ptr->head == NULL);
    assert(queue_ptr->tail == NULL);
    assert(queue_ptr->size == 0);
    assert(queue_ptr->element_size == sizeof(double));
    printf("test_queue_init passed!\n");
}

static void test_queue_back() {
    queue_init(queue_ptr, sizeof(double));
    queue_push(queue_ptr, &vals[0]);
    queue_push(queue_ptr, &vals[1]);
    assert(*(double *) queue_back(queue_ptr)->val == vals[1]);
    queue_clear(queue_ptr);
    printf("test_queue_back passed!\n");
}

static void test_queue_front() {
    queue_init(queue_ptr, sizeof(double));
    queue_push(queue_ptr, &vals[0]);
    queue_push(queue_ptr, &vals[1]);
    assert(*(double *) queue_front(queue_ptr)->val == vals[0]);
    queue_clear(queue_ptr);
    printf("test_queue_front passed!\n");
}

static void test_queue_push() {
    queue_init(queue_ptr, sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        queue_push(queue_ptr, &vals[i]);
    }
    assert(*(double *) queue_ptr->tail->val == vals[array_size - 1]);
    assert(queue_ptr->size == array_size);
    queue_clear(queue_ptr);
    printf("test_queue_push passed!\n");
}

static void test_queue_pop() {
    queue_init(queue_ptr, sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        queue_push(queue_ptr, &vals[i]);
    }
    queue_pop(queue_ptr);
    queue_pop(queue_ptr);
    assert(*(double *) queue_ptr->head->val == vals[2]);
    assert(queue_ptr->size == array_size - 2);
    queue_clear(queue_ptr);
    printf("test_queue_pop passed!\n");
}

static void test_queue_clear() {
    queue_init(queue_ptr, sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        queue_push(queue_ptr, &vals[i]);
    }
    queue_clear(queue_ptr);
    assert(queue_ptr->head == NULL);
    assert(queue_ptr->tail == NULL);
    assert(queue_ptr->size == 0);
    printf("test_queue_clear passed!\n");
}

static void test_queue_size() {
    queue_init(queue_ptr, sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        queue_push(queue_ptr, &vals[i]);
    }
    assert(queue_size(queue_ptr) == array_size);
    printf("test_queue_size passed!\n");
}

static void test_queue_is_empty() {
    queue_init(queue_ptr, sizeof(double));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        queue_push(queue_ptr, &vals[i]);
    }
    assert(queue_is_empty(queue_ptr) == false);
    queue_clear(queue_ptr);
    assert(queue_is_empty(queue_ptr) == true);
    printf("test_queue_is_empty passed!\n");
}

TestFunction test_functions[] = {
        test_queue_init,
        test_queue_back,
        test_queue_front,
        test_queue_push,
        test_queue_pop,
        test_queue_clear,
        test_queue_size,
        test_queue_is_empty
};

int main(int argc, char** argv) {
    size_t tests_size = sizeof(test_functions) / sizeof(TestFunction);
    queue_ptr = (queue *) malloc(sizeof(queue));
    for(size_t i = 0; i < tests_size; i++) {
        test_functions[i]();
    }
    printf("\033[0;32mAll tests passed!\n");
    free(queue_ptr);
    queue_ptr = NULL;
    return 0;
}