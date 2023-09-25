#include "queue.h"

/**
 * @brief Initialize the queue.
 *
 * @param queue A pointer to the queue to be initialized.
 * @param element_size The size in bytes of each element in the queue.
 */
void queue_init(queue* queue, size_t element_size) {
    assert(queue != NULL);

    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    queue->element_size = element_size;
}

/**
 * @brief Retrieves the last node of the queue.
 *
 * @param queue A pointer to the queue whose last node will be returned.
 *
 * @return The last node of the queue.
 */
node* queue_back(const queue* queue) {
    assert(queue != NULL);

    return queue->tail;
}

/**
 * @brief Retrieves the first node of the queue.
 *
 * @param queue A pointer to the queue whose first node will be returned.
 *
 * @return The first node of the queue.
 */
node* queue_front(const queue* queue) {
    assert(queue != NULL);

    return queue->head;
}

/**
 * @brief Insert a new node with the specified value into the queue and update the tail.
 *
 * @param queue A pointer to the queue to add to.
 * @param val The value of the node to be pushed to the queue.
 */
void queue_push(queue* queue, const void* val) {
    assert(queue != NULL && val != NULL);

    node* node_ptr = (node *) malloc(sizeof(node));
    node_ptr->val = (byte *) malloc(sizeof(byte) * queue->element_size);
    node_ptr->next = NULL;
    memcpy(node_ptr->val, val, sizeof(byte) * queue->element_size);

    if(queue_is_empty(queue)) {
        queue->head = node_ptr;
    }
    else {
        queue->tail->next = node_ptr;
    }
    queue->tail = node_ptr;
    queue->size++;
}

/**
 * @brief Remove the front node of the queue and update the head.
 *
 * @param queue A pointer to the queue to remove from.
 */
void queue_pop(queue* queue) {
    assert(queue != NULL && queue->size > 0);

    node* node_ptr = queue->head;
    if(node_ptr->next == NULL)
        queue->tail = NULL;
    queue->head = queue->head->next;
    node_ptr->next = NULL;
    queue->size--;
    free(node_ptr->val);
    node_ptr->val = NULL;
    free(node_ptr);
    node_ptr = NULL;
}

/**
 * @brief Remove all the nodes from the queue.
 *
 * @param queue A pointer to the queue to remove from.
 */
void queue_clear(queue* queue) {
    assert(queue != NULL);

    while(!queue_is_empty(queue)) {
        queue_pop(queue);
    }
}

/**
 * @brief Gets the size of the specified queue.
 *
 * @param queue A pointer to the queue whose size will be returned.
 *
 * @return The size of the specified queue.
 */
size_t queue_size(const queue* queue) {
    assert(queue != NULL);

    return queue->size;
}

/**
 * @brief Checks whether or not the specified queue is empty.
 *
 * @param queue A pointer to the queue to be checked.
 *
 * @return Whether or not the specified queue is empty.
 */
bool queue_is_empty(const queue* queue) {
    assert(queue != NULL);

    return queue->size == 0;
}
