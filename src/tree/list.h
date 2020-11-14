#ifndef STEPIK_COURCE_LIST_H
#define STEPIK_COURCE_LIST_H

#include "graph.h"


struct list {
    struct node* value;
    struct list* next;
};

struct list* list_create(struct node* value);
void list_destroy(struct list* list);

struct list* list_add_front(struct list* list, struct node* value);

#endif //STEPIK_COURCE_LIST_H
