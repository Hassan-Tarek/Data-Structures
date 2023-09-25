#include "stack.h"

/**
 * @brief Initialize the stack.
 *
 * @param stack The stack to be initialized.
 * @param element_size The size in bytes of each element in the stack.
 */
void stack_init(stack* stack, size_t element_size) {
    assert(stack != NULL && element_size > 0);

    stack->top = NULL;
    stack->size = 0;
    stack->element_size = element_size;
}

/**
 * @brief Retrieves the top node of the stack.
 *
 * @param stack The stack whose top node will be returned.
 *
 * @return The top of the stack.
 */
node* stack_top(const stack* stack) {
    assert(stack != NULL);

    return stack->top;
}

/**
 * @brief Insert a new node with the specified value into the stack and update the top.
 *
 * @param stack A pointer to a stack to add to.
 * @param val The value of the node to be added to the stack.
 */
void stack_push(stack* stack, const void* val) {
    assert(stack != NULL);

    node* node_ptr = (node *) malloc(sizeof(node));
    node_ptr->val = (byte *) malloc(sizeof(byte) * stack->element_size);
    memcpy(node_ptr->val, val, sizeof(byte) * stack->element_size);
    node_ptr->prev = stack->top;
    stack->top = node_ptr;
    stack->size++;
}

/**
 * @brief Remove the top node from the stack and update the top.
 *
 * @param stack A pointer to the stack to remove from.
 */
void stack_pop(stack* stack) {
    assert(stack != NULL && stack->size != 0);

    node* temp = stack->top;
    stack->top = stack->top->prev;
    temp->prev = NULL;
    stack->size--;
    free(temp->val);
    temp->val = NULL;
    free(temp);
    temp = NULL;
}

/**
 * @brief Remove all the nodes from the stack.
 *
 * @param stack A pointer to a stack to remove from.
 */
void stack_clear(stack* stack) {
    assert(stack != NULL);

    while(!stack_is_empty(stack)) {
        stack_pop(stack);
    }
}

/**
 * @brief Gets the size of the specified stack.
 *
 * @param stack A pointer to the stack whose size will be returned.
 *
 * @return The size of the specified stack.
 */
size_t stack_size(const stack* stack) {
    assert(stack != NULL);

    return stack->size;
}

/**
 * @brief Checks whether or not the specified stack is empty.
 *
 * @param stack A pointer to the stack to be checked.
 *
 * @return Whether or not the specified stack is empty.
 */
bool stack_is_empty(const stack* stack) {
    assert(stack != NULL);

    return stack->size == 0;
}
