#ifndef STEPIK_COURCE_LIST_H
#define STEPIK_COURCE_LIST_H

#include "graph.h"


struct list {
    struct node* value;
    struct list* next;
};

/**
 * Creates a list element with given node value.
 * Use this method only for creating a new list.
 */
struct list* list_create(struct node* value);

/**
 * Destroys given list element, node value and next list element.
 * Means that calling this method on first element in a list destroys
 * whole list.
 */
void list_destroy(struct list* list);

/**
 * Creates a list element with given node as value and add given list as next element for created one.
 * Returns created list element.
 *
 * If give list is NULL, then firstly creates a list via list_create().
 */
struct list* list_add_front(struct list* list, struct node* value);

#endif //STEPIK_COURCE_LIST_H
