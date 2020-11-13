#ifndef STEPIK_COURCE_TREE_H
#define STEPIK_COURCE_TREE_H

#include "list.h"

#include <stdint.h>
#include <stddef.h>


typedef int64_t entry;

struct node {
    entry value;
    struct list* leafs_list;
};

struct node* node_create(entry value);
void node_destroy(struct node* node);

void node_add_leaf(struct node* node, struct node* leaf);

struct node* node_find_dfs(const struct node* node, entry target);
struct node* node_find_bfs(const struct node* node, entry target);

void node_foreach_bfs(struct node* node, void(entry_consumer)(struct node* current));

#endif //STEPIK_COURCE_TREE_H
