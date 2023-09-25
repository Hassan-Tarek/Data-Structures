/**
 * @file     queue.h
 *
 * @brief    The Implementation of the Queue.
 * @author   Hassan Tarek
 */

#ifndef QUEUE_H
#define QUEUE_H

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
struct queue;

/* Typedefs */
typedef struct node node;
typedef struct queue queue;
typedef uint8_t byte;

/**
 * Define the struct represent the node that make queue.
 */
struct node {
    void* val;
    node* next;
};

/**
 * Define the struct represent the queue.
 */
struct queue {
    node* head;
    node* tail;
    size_t size;
    size_t element_size;
};


/** F U N C T I O N S   P R O T O T Y P E S **/

/* Initialization */
void queue_init(queue* queue, size_t element_size);

/* Accessing */
node* queue_back(const queue* queue);
node* queue_front(const queue* queue);

/* Insertion */
void queue_push(queue* queue, const void* val);

/* Removal */
void queue_pop(queue* queue);
void queue_clear(queue* queue);

/* Utility */
size_t queue_size(const queue* queue);
bool queue_is_empty(const queue* queue);


/* M A C R O S */

#define queue_for_each (node_ptr, queue_ptr)  \
    for (node* node_ptr = (queue_ptr)->head;  \
         node_ptr != NULL;                    \
         node_ptr = (node_ptr)->next)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */