/**
 * @file     list.h
 *
 * @brief    The Implementation of Doubly Linked List
 * @author   Hassan Tarek
 */

#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

/* Struct type declaration */
struct node;
struct list;

/* Typedefs */
typedef struct node node;
typedef struct list list;

/**
 * Define the struct represent the node that make list.
 */
struct node {
    void* val;
    node* next;
    node* prev;
};

/**
 * Define the struct represent doubly linked list.
 */
struct list {
    node* head;
    node* tail;
    size_t size;
};


/** F U N C T I O N S   P R O T O T Y P E S **/

/* Initialization */
void list_init(list* list);

/* Accessing */
node* list_back(const list* list);
node* list_front(const list* list);
node* list_at(const list* list, size_t index);
int list_index_of(const list* list, const void* val);

/* Insertion */
void list_push_back(list* list, const void* val);
void list_push_front(list* list, const void* val);
void list_insert_at(list* list, const void* val, size_t index);

/* Removal */
void list_pop_back(list* list);
void list_pop_front(list* list);
void list_remove_at(list* list, size_t index);
void list_remove(list* list, const void* val);
void list_clear(list* list);

/* Utility */
size_t list_size(const list* list);
bool list_is_empty(const list* list);
void list_merge(const list* lhs, const list* rhs, list* dest);
void list_reverse(list* list);
void list_copy_to_array(const list* list, void* array);
void list_sort(list* list, int (*compare)(const void* right, const void* left));


/* M A C R O S */

#define list_for_each(node_ptr, list_ptr)     \
    for (node* node_ptr = (list_ptr)->head;   \
         node_ptr != (list_ptr)->tail->next;  \
         node_ptr = (node_ptr)->next)

#define list_for_each_reverse(node_ptr, list_ptr)  \
    for (node* node_ptr = (list_ptr)->tail;        \
         node_ptr != (list_ptr)->head->prev;       \
         node_ptr = (node_ptr)->prev)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIST_H */