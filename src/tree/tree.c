#include "tree.h"
#include "list.h"

#include <malloc.h>


struct node* node_create(entry value) {
    struct node* r = malloc(sizeof(struct node));
    r->value = value;
    r->leafs_list = NULL;

    return r;
}

void node_destroy(struct node* node) {
    if (!node->leafs_list) {
        free(node);
    }

    list_destroy(node->leafs_list);

    free(node);
}

void node_add_leaf(struct node* node, struct node* leaf) {
    node->leafs_list = list_add_front(node->leafs_list, leaf);
}

struct node* node_find_dfs(const struct node* node, entry target) {
    if (node->value == target) {
        return node;
    }

    if (node->leafs_list) {
        struct list* current_list = node->leafs_list;
        struct node* result = NULL;

        while (current_list) {
            result = node_find_dfs(current_list->value, target);

            if (result) {
                return result;
            }

            current_list = current_list->next;
        }
    } else {
        return NULL;
    }
}

static
struct node* _node_find_bfs(const struct node* node, entry target) {
    if (node->leafs_list) {
        struct list* current_list = node->leafs_list;
        struct node* result = current_list->value;

        while (1) {
            if (result->value == target) {
                return result;
            }

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
            result = current_list->value;
        }

        current_list = node->leafs_list;

        while (1) {
            result = _node_find_bfs(current_list->value, target);

            if (result) {
                return result;
            }

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
        }
    } else {
        return NULL;
    }
}

struct node* node_find_bfs(const struct node* node, entry target) {
    if (node->value == target) {
        return node;
    }

    return _node_find_bfs(node, target);
}

static
void _node_foreach_bfs(struct node* node, void(entry_consumer)(struct node* current)) {
    if (node->leafs_list) {
        struct list* current_list = node->leafs_list;

        while (1) {
            entry_consumer(current_list->value);

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
        }

        current_list = node->leafs_list;

        while (1) {
            _node_foreach_bfs(current_list->value, entry_consumer);

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
        }
    }
}

void node_foreach_bfs(struct node* node, void(entry_consumer)(struct node* current)) {
    entry_consumer(node);

    _node_foreach_bfs(node, entry_consumer);
}