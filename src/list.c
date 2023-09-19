#include "list.h"

/**
 * @brief Create a new node.
 *
 * @param val The value of the node.
 * @param size The size in bytes of the specified value.
 * @param next A pointer to the next node.
 * @param prev A pointer to the previous node.
 *
 * @return A pointer to the newly created node.
 */
static node* list_create_node(const void* val, size_t size, node* next, node* prev) {
    assert(val != NULL);

    node* node_ptr = (node *) malloc(sizeof(node));
    node_ptr->val = (byte *) malloc(size);
    memcpy(node_ptr->val, val, size);
    node_ptr->next = next;
    node_ptr->prev = prev;
    return node_ptr;
}

/**
 * @brief Deallocate the memory of the specified node.
 *
 * @param node The node wanted to be freed.
 */
static void list_free_node(node** node) {
    assert(node != NULL && *node != NULL);

    if ((*node)->val != NULL) {
        free((*node)->val);
        (*node)->val = NULL;
    }
    free(*node);
    *node = NULL;
}

/**
 * @brief Initialize the list.
 *
 * @param list The list to be initialized.
 * @param element_size The size in bytes of each element in the list.
 */
void list_init(list* list, size_t element_size) {
    assert(list != NULL);

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->element_size = element_size;
}

/**
 * @brief Retrieves the last node of the specified list.
 *
 * @param list The list whose last node wanted to be retrieved.
 *
 * @return The last node of the specified list.
 */
node* list_back(const list* list) {
    assert(list != NULL);

    return list->tail;
}

/**
 * @brief Retrieves the first node of the specified list.
 *
 * @param list The list whose first node wanted to be retrieved.
 *
 * @return The first node of the specified list.
 */
node* list_front(const list* list) {
    assert(list != NULL);

    return list->head;
}

/**
 * @brief Retrieves the node at the specified index from the specified list.
 *
 * @param list The list from which the node at the specified index will be retrieved.
 * @param index The index of the node to retrieve.
 *
 * @return The node at the specified index.
 */
node* list_at(const list* list, size_t index) {
    assert(list != NULL && index < list->size);

    size_t offset = 0;
    list_for_each(node, list) {
        if(offset == index) {
            return node;
        }
        offset++;
    }
    return NULL;
}

/**
 * @brief Retrieves the index of the specified value or -1 if it's not found.
 *
 * @param list The list to be searched.
 * @param val The value to be searched for.
 *
 * @return The index of the specified value or -1 if it's not found.
 */
int list_index_of(const list* list, const void* val) {
    assert(list != NULL && val != NULL);

    int offset = 0;
    list_for_each(node, list) {
        int cmp = memcmp(node->val, val, list->element_size);
        if(cmp == 0) {
            return offset;
        }
        offset++;
    }
    return -1;
}

/**
 * @brief Insert a new node with the specified value into the end of the list.
 *
 * @param list A pointer to a list to add to.
 * @param val The value of the node to be added to the list.
 */
void list_push_back(list* list, const void* val) {
    assert(list != NULL && val != NULL);

    node* node_ptr = list_create_node(val, list->element_size, NULL, list->tail);
    if(list->size == 0)
        list->head = node_ptr;
    else
        list->tail->next = node_ptr;
    list->tail = node_ptr;
    list->size++;
}

/**
 * @brief Insert a new node with the specified value into the front of the list.
 *
 * @param list A pointer to a list to add to.
 * @param val The value of the node to be added to the list.
 */
void list_push_front(list* list, const void* val) {
    assert(list != NULL && val != NULL);

    node* node_ptr = list_create_node(val, list->element_size, list->head, NULL);
    if(list->size == 0)
        list->tail = node_ptr;
    else
        list->head->prev = node_ptr;
    list->head = node_ptr;
    list->size++;
}

/**
 * @brief Insert a new node with the specified value into the specified index of the list.
 *
 * @param list A pointer to a list to add to.
 * @param val The value of the node to be added to the list.
 * @param index The index at which the node should be inserted.
 */
void list_insert_at(list* list, const void* val, size_t index) {
    assert(list != NULL && val != NULL && index <= list->size);

    if (list->size == 0) {
        list_push_front(list, val);
    }
    else if(index == list->size) {
        list_push_back(list, val);
    }
    else {
        size_t offset = 0;
        node* cur = list->head;
        while(offset < index) {
            cur = cur->next;
            offset++;
        }
        node* node_ptr = list_create_node(val, list->element_size, cur, cur->prev);
        cur->prev->next = node_ptr;
        cur->prev = node_ptr;
        list->size++;
    }
}

/**
 * @brief Remove the last node from the list.
 *
 * @param list A pointer to the list to remove from.
 */
void list_pop_back(list* list) {
    assert(list != NULL && list->size > 0);

    node* temp = list->tail;
    if(temp != list->head) { // list contains more than one node
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else {
        list->head = NULL;
        list->tail = NULL;
    }
    list_free_node(&temp);
    list->size--;
}

/**
 * @brief Remove the first node from the list.
 *
 * @param list A pointer to the list to remove from.
 */
void list_pop_front(list* list) {
    assert(list != NULL && list->size > 0);

    node* temp = list->head;
    if (temp != list->tail) { // list contains more than one node
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    else {
        list->head = NULL;
        list->tail = NULL;
    }
    list_free_node(&temp);
    list->size--;
}

/**
 * @brief Remove the node at the specified index from the list.
 *
 * @param list A pointer to the list to remove from.
 * @param index The index of the node wanted to be removed from the list.
 */
void list_remove_at(list* list, size_t index) {
    assert(list != NULL && index < list->size);

    if(index == 0) {
        list_pop_front(list);
    }
    else if(index == list->size - 1) {
        list_pop_back(list);
    }
    else {
        size_t offset = 0;
        node* cur = list->head;
        while (offset < index) {
            cur = cur->next;
            offset++;
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        cur->next = NULL;
        cur->prev = NULL;
        list_free_node(&cur);
        list->size--;
    }
}

/**
 * @brief Remove all occurrences of the specified node's value from the list.
 *
 * @param list A pointer to a list to remove from.
 * @param val A pointer to the value to be removed from the list.
 */
void list_remove(list* list, const void* val) {
    assert(list != NULL && val != NULL);

    size_t offset = 0;
    node* cur = list->head;
    while(cur != NULL && offset < list->size) {
        int cmp = memcmp(cur->val, val, list->element_size);
        if(cmp == 0) {
            cur = cur->next;
            list_remove_at(list, offset);
        }
        offset++;
    }
}

/**
 * @brief Remove all the nodes from the specified list.
 *
 * @param list A pointer to a list to remove from.
 */
void list_clear(list* list) {
    assert(list != NULL);

    while(list->size > 0) {
        list_pop_back(list);
    }
}

/**
 * @brief Gets the size of the specified list.
 *
 * @param list The list whose size will be returned.
 *
 * @return The size of the specified list.
 */
size_t list_size(const list* list) {
    assert(list != NULL);

    return list->size;
}

/**
 * @brief Checks whether or not the specified list is empty.
 *
 * @param list The list to be checked.
 *
 * @return Whether or not the list is empty.
 */
bool list_is_empty(const list* list) {
    assert(list != NULL);

    return list->size == 0;
}

/**
 * @brief Merge a two specified lists into the dest list.
 *
 * @param lhs A pointer to the first list.
 * @param rhs A pointer to the second list.
 * @param dest A pointer to the destination list.
 */
void list_merge(const list* lhs, const list* rhs, list* dest) {
    assert(lhs != NULL && rhs != NULL && dest != NULL);

    list_for_each(node, lhs) {
        list_push_back(dest, node->val);
    }
    list_for_each(node, rhs) {
        list_push_back(dest, node->val);
    }
}

/**
 * @brief Reverses the specified list in place.
 *
 * @param list A pointer to the list will be reversed.
 */
void list_reverse(list* list) {
    assert(list != NULL);

    node* cur = list->head;
    while(cur != NULL) {
        node* temp = cur->next;
        cur->next = cur->prev;
        cur->prev = temp;
        cur = temp;
    }
    node* temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

/**
 * @brief Copies the specified list to the specified array.
 *
 * @param list The list will be copied to the specified array.
 * @param array A pointer to the array where the values will be copied.
 */
void list_copy_to_array(const list* list, void* array) {
    assert(list != NULL && array != NULL);

    size_t offset = 0;
    list_for_each(node, list) {
        memcpy(array + offset * sizeof(*node->val), node->val, sizeof(*node->val));
        offset++;
    }
}

/**
 * @brief Sorts the specified list in place.
 *
 * @param list The list will be sorted.
 * @param compare The compare function used to sort the list.
 */
void list_sort(list* list, int (*compare)(const void* right, const void* left)) {
    assert(list != NULL && compare != NULL);

    node** node_arr = (node **) malloc(sizeof(node *) * list->size);
    size_t offset = 0;
    list_for_each(node, list) {
        node_arr[offset] = node;
        offset++;
    }
    qsort(node_arr, list->size,
          list->size * sizeof(node), compare);

    node* cur = node_arr[0];
    list->head = cur;
    list->head->prev = NULL;
    for(size_t i = 1; i < list->size; i++) {
        node_arr[i]->prev = cur;
        cur->next = node_arr[i];
        cur = cur->next;
    }
    list->tail = cur;
    list->tail->next = NULL;

    free(node_arr);
    node_arr = NULL;
}
