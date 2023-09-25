/**
 * @file     stack.h
 *
 * @brief    The Implementation of the Stack.
 * @author   Hassan Tarek
 */

#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* Struct type declaration */
struct node;
struct stack;

/* Typedefs */
typedef struct node node;
typedef struct stack stack;
typedef uint8_t byte;

/**
 * Define the struct represent the node that make stack.
 */
struct node {
    void* val;
    node* prev;
};

/**
 * Define the struct represent the stack.
 */
struct stack {
    node* top;
    size_t size;
    size_t element_size;
};


/** F U N C T I O N S   P R O T O T Y P E S **/

/* Initialization */
void stack_init(stack* stack, size_t element_size);

/* Accessing */
node* stack_top(const stack* stack);

/* Insertion */
void stack_push(stack* stack, const void* val);

/* Removal */
void stack_pop(stack* stack);
void stack_clear(stack* stack);

/* Utility */
size_t stack_size(const stack* stack);
bool stack_is_empty(const stack* stack);


/* M A C R O S */

#define stack_for_each (node_ptr, stack_ptr)  \
    for (node* node_ptr = (stack_ptr)->top;   \
         node_ptr != NULL;                    \
         node_ptr = (node_ptr)->prev)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */