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
    //идея использовать массив посещенных вершин при обходе по принципу: id - посещение
    //сделать связи двунаправленными
    uint8_t * visited_nodes;
    struct node* root_node;
};

//begin create graph
/**
 * Creates an empty graph with zero size.
 */
struct graph* graph_create();

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

static
void node_add_child(struct node* node, struct node* child);
//end create graph


//begin find entry bfs
static
struct node* find_in_children_list(const struct list* children_list, uint8_t* visited_nodes, entry target);

static
struct node* node_find_bfs(const struct node* node, uint8_t* visited_nodes, entry target);

static
struct node* find_bsf_for_children_list(const struct list* children_list, uint8_t* visited_nodes, entry target);

struct node* graph_find_bfs(struct graph* graph, entry target);
//end find entry bfs


//begin find entry dfs
static
struct node* node_find_dfs(const struct node* node, entry target, uint8_t* visited_nodes);

/**
 * Finds a node with given entry value in the graph. Searching begins from graph's root_node.
 */
struct node* graph_find_dfs(struct graph* graph, entry target);
//end find entry dfs


//begin foreach bfs
static
void node_foreach_bfs(struct node* node, uint8_t* visited_nodes, void(entry_consumer)(struct node* current));

void graph_foreach_bfs(struct graph *graph, void(entry_consumer)(struct node* current));
//end foreach bfs

#endif //STEPIK_COURCE_GRAPH_H
