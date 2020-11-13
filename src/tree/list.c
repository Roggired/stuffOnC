#include "list.h"
#include "tree.h"

#include <malloc.h>


struct list* list_create(struct node* value) {
    struct list* r = malloc(sizeof(struct list));
    r->value = value;
    r->next = NULL;

    return r;
}

void list_destroy(struct list* list) {
    if (!list->value) {
        node_destroy(list->value);
    }

    if (list->next) {
        list_destroy(list->next);
    }

    free(list);
}

struct list* list_add_front(struct list* list, struct node* value) {
    if (!list) {
        return list_create(value);
    }

    struct list* new_element = list_create(value);

    new_element->next = list;

    return new_element;
}