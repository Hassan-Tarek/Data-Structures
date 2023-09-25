#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../src/stack.h"

/* Pointer Functions */
typedef void (* TestFunction) ();

/* Global Variables */
stack* stack_ptr;
int vals[6] = {'a', 'b', 'c', 'd', 'e', 'f'};


/** T E S T   F U N C T I O N S **/

static void test_stack_init() {
    stack_init(stack_ptr, sizeof(char));
    assert(stack_ptr->top == NULL);
    assert(stack_ptr->size == 0);
    assert(stack_ptr->element_size == sizeof(char));
    printf("test_stack_init passed!\n");
}

static void test_stack_top() {
    stack_init(stack_ptr, sizeof(char));
    stack_push(stack_ptr, &vals[0]);
    stack_push(stack_ptr, &vals[1]);
    assert(*(char *) stack_top(stack_ptr)->val == vals[1]);
    stack_clear(stack_ptr);
    printf("test_stack_top passed!\n");
}

static void test_stack_push() {
    stack_init(stack_ptr, sizeof(char));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        stack_push(stack_ptr, &vals[i]);
    }
    assert(*(char *) stack_ptr->top->val == vals[array_size - 1]);
    assert(stack_ptr->size == array_size);
    stack_clear(stack_ptr);
    printf("test_stack_push passed!\n");
}

static void test_stack_pop() {
    stack_init(stack_ptr, sizeof(char));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        stack_push(stack_ptr, &vals[i]);
    }
    stack_pop(stack_ptr);
    stack_pop(stack_ptr);
    assert(*(char *) stack_ptr->top->val == vals[array_size - 3]);
    assert(stack_ptr->size == array_size - 2);
    stack_clear(stack_ptr);
    printf("test_stack_pop passed!\n");
}

static void test_stack_clear() {
    stack_init(stack_ptr, sizeof(char));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        stack_push(stack_ptr, &vals[i]);
    }
    stack_clear(stack_ptr);
    assert(stack_ptr->top == NULL);
    assert(stack_ptr->size == 0);
    printf("test_stack_clear passed!\n");
}

static void test_stack_size() {
    stack_init(stack_ptr, sizeof(char));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        stack_push(stack_ptr, &vals[i]);
    }
    assert(stack_size(stack_ptr) == array_size);
    printf("test_stack_size passed!\n");
}

static void test_stack_is_empty() {
    stack_init(stack_ptr, sizeof(char));
    size_t array_size = sizeof(vals) / sizeof(vals[0]);
    for(size_t i = 0; i < array_size; i++) {
        stack_push(stack_ptr, &vals[i]);
    }
    assert(stack_is_empty(stack_ptr) == false);
    stack_clear(stack_ptr);
    assert(stack_is_empty(stack_ptr) == true);
    printf("test_stack_is_empty passed!\n");
}

TestFunction test_functions[] = {
        test_stack_init,
        test_stack_top,
        test_stack_push,
        test_stack_pop,
        test_stack_clear,
        test_stack_size,
        test_stack_is_empty
};

int main(int argc, char** argv) {
    size_t tests_size = sizeof(test_functions) / sizeof(TestFunction);
    stack_ptr = (stack *) malloc(sizeof(stack));
    for(size_t i = 0; i < tests_size; i++) {
        test_functions[i]();
    }
    printf("\033[0;32mAll tests passed!\n");
    free(stack_ptr);
    stack_ptr = NULL;
    return 0;
}