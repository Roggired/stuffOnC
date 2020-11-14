#ifndef STEPIK_COURCE_GRAPH_H
#define STEPIK_COURCE_GRAPH_H

#include "list.h"

#include <stdint.h>
#include <stddef.h>


typedef int64_t entry;

struct node {
    uint32_t id;
    entry value;
    struct list* children_list;
};

struct graph {
    size_t size;
    uint32_t current_available_id;
    uint8_t * visited_nodes;
    struct node* root_node;
};

/**
 * Creates an empty graph with zero size.
 */
struct graph* graph_create();

/**
 * Destroys the graph and each node in it.
 */
void graph_destroy(struct graph* graph);

/**
 * Creates a node and add this node to the parent. Also changes the state of a graph.
 * If the parent is null, then set created node like root_node in the graph.
 */
struct node* node_create(struct graph* graph, entry value, struct node* parent);

/**
 * Only for inner usages. For graph destroying use graph_destroy.
 */
void node_destroy(struct node* node);

/**
 * Finds a node with given entry value in the graph using bfs algorithm. Searching begins from graph's root_node.
 */
struct node* graph_find_bfs(struct graph* graph, entry target);

/**
 * Finds a node with given entry value in the graph using dfs algorithm. Searching begins from graph's root_node.
 */
struct node* graph_find_dfs(struct graph* graph, entry target);

/**
 * Apply an entry_consumer for each node in the graph using bfs algorithm.
 */
void graph_foreach_bfs(struct graph *graph, void(entry_consumer)(struct node* current));

#endif //STEPIK_COURCE_GRAPH_H
