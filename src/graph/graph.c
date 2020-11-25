#include "graph.h"
#include "list.h"

#include <malloc.h>


struct graph* graph_create() {
    struct graph* result = malloc(sizeof(struct graph));
    result->size = 0;
    result->current_available_id = 0;
    result->nodes = NULL;
    result->previous_on_smallest_path = NULL;
    result->root_node = NULL;
    result->visited_nodes = NULL;

    return result;
}

void graph_destroy(struct graph* graph) {
    if (graph->visited_nodes) {
        free(graph->visited_nodes);
    }

    if (graph->previous_on_smallest_path) {
        free(graph->previous_on_smallest_path);
    }

    if (graph->nodes) {
        free(graph->nodes);
    }

    node_destroy(graph->root_node);

    free(graph);
}

static
void node_set_id(struct graph* graph, struct node* node) {
    node->id = graph->current_available_id;
    graph->current_available_id++;
}


void node_add_child(struct node* node, struct node* child) {
    node->children_list = list_add_front(node->children_list, child);
    child->children_list = list_add_front(child->children_list, node);
}

struct node* node_create(struct graph* graph, entry value, struct node* parent) {
    struct node* result = malloc(sizeof(struct node));
    result->value = value;
    result->children_list = NULL;

    node_set_id(graph, result);

    if (parent) {
        node_add_child(parent, result);
        graph->nodes = realloc(graph->nodes, sizeof(struct node*) * (graph->size + 1));
    } else {
        graph->root_node = result;
        graph->nodes = malloc(sizeof(struct node*) * 1);
    }

    graph->nodes[result->id] = result;

    graph->size++;

    return result;
}

void node_destroy(struct node* node) {
    if (!node->children_list) {
        free(node);
    }

    list_destroy(node->children_list);

    free(node);
}

static
void graph_alloc_visited_nodes(struct graph* graph) {
    if (graph->visited_nodes) {
        free(graph->visited_nodes);
    }

    graph->visited_nodes = malloc(sizeof(uint8_t) * graph->size);

    for (size_t i = 0; i < graph->size; i++) {
        graph->visited_nodes[i] = 0;
    }
}

static
struct node* node_find_dfs(const struct node* node, entry target, uint8_t* visited_nodes) {
    if (visited_nodes[node->id]) {
        return NULL;
    }

    visited_nodes[node->id] = 1;

    if (node->value == target) {
        return node;
    }

    if (node->children_list) {
        struct list* current_list = node->children_list;
        struct node* result = NULL;

        while (current_list) {
            result = node_find_dfs(current_list->value, target, visited_nodes);

            if (result) {
                return result;
            }

            current_list = current_list->next;
        }
    } else {
        return NULL;
    }
}

struct node* graph_find_dfs(struct graph* graph, entry target) {
    if (!graph->size) {
        return NULL;
    }

    graph_alloc_visited_nodes(graph);

    node_find_dfs(graph->root_node, target, graph->visited_nodes);
}

static
struct node* find_in_children_list(const struct list* children_list, uint8_t* visited_nodes, entry target) {
    struct node* result = children_list->value;

    while (1) {
        if (!visited_nodes[result->id] && result->value == target) {
            return result;
        }

        if (!children_list->next) {
            return NULL;
        }

        visited_nodes[result->id] = 1;

        children_list = children_list->next;
        result = children_list->value;
    }
}

static
struct node* node_find_bfs(const struct node* node, uint8_t* visited_nodes, entry target);

static
struct node* find_bsf_for_children_list(const struct list* children_list, uint8_t* visited_nodes, entry target) {
    struct node* result = NULL;

    while (1) {
        if (visited_nodes[children_list->value->id] != 2) {
            result = node_find_bfs(children_list->value, visited_nodes, target);
            visited_nodes[children_list->value->id] = 2;
        }

        if (result) {
            return result;
        }

        if (!children_list->next) {
            return NULL;
        }

        children_list = children_list->next;
    }
}

static
struct node* node_find_bfs(const struct node* node, uint8_t* visited_nodes, entry target) {
    if (node->children_list) {
        struct node* result = find_in_children_list(node->children_list, visited_nodes, target);

        if (result) {
            return result;
        }

        visited_nodes[node->id] = 2;

        return find_bsf_for_children_list(node->children_list, visited_nodes, target);
    } else {
        return NULL;
    }
}

struct node* graph_find_bfs(struct graph* graph, entry target) {
    graph_alloc_visited_nodes(graph);

    if (graph->root_node->value == target) {
        return graph->root_node;
    }

    graph->visited_nodes[graph->root_node->id] = 1;

    return node_find_bfs(graph->root_node, graph->visited_nodes, target);
}

static
struct node* smallest_path_next(struct graph* graph, struct node* origin, struct node* current) {
    uint32_t previous_node_id = graph->previous_on_smallest_path[current->id];
    return graph->nodes[previous_node_id];
}

static
void reverse_path(struct node** path, size_t size) {
    for (size_t i = 0; i < size / 2; ++i) {
        struct node* tmp = path[i];
        path[i] = path[size - i - 1];
        path[size - i - 1] = tmp;
    }
}

static
struct node** smallest_path_build(struct graph* graph, struct node* origin, struct node* target, size_t* result_size) {
    struct node** path = malloc(sizeof(struct node*) * 1);

    path[0] = target;

    size_t path_size = 1;
    struct node* next = smallest_path_next(graph, origin, target);

    while(next) {
        path = realloc(path, sizeof(struct node*) * (path_size + 1));
        path[path_size] = next;

        if (next == origin) {
            break;
        }

        path_size++;
        next = smallest_path_next(graph, origin, next);
    }

    reverse_path(path, path_size);
    *result_size = path_size;

    return path;
}

static
void smallest_path_foreach_node_change_mark(struct graph* graph, struct node* node) {
    if (!node->children_list) {
        return;
    }

    struct list* current_list = node->children_list;
    struct node* current = current_list->value;

    struct list* nodes_for_checking = NULL;

    while (1) {
        if (current->path_length == -1 || current->path_length > node->path_length + 1) {
            current->path_length = node->path_length + 1;
            graph->previous_on_smallest_path[current->id] = node->id;

            if (nodes_for_checking) {
                nodes_for_checking = list_add_front(nodes_for_checking, current);
            } else {
                nodes_for_checking = list_create(current);
            }
        }

        if (!current_list->next) {
            break;
        }

        current_list = current_list->next;
        current = current_list->value;
    }

    if (!nodes_for_checking) {
        return;
    }

    while (1) {
        smallest_path_foreach_node_change_mark(graph, nodes_for_checking->value);

        if (!nodes_for_checking->next) {
            break;
        }

        nodes_for_checking = nodes_for_checking->next;
    }
}

struct node** graph_find_smallest_path(struct graph* graph, struct node* origin, struct node* target, size_t* result_size) {
    if (origin == target) {
        struct node** path = malloc(sizeof(struct node*) * 1);
        path[0] = origin;

        return path;
    }

    if (graph->previous_on_smallest_path) {
        free(graph->previous_on_smallest_path);
    }

    graph->previous_on_smallest_path = malloc(sizeof(uint32_t) * graph->size);

    for (size_t i = 0; i < graph->size; i++) {
        graph->nodes[i]->path_length = -1;
    }

    origin->path_length = 0;
    graph->previous_on_smallest_path[origin->id] = origin->id;

    smallest_path_foreach_node_change_mark(graph, origin);

    return smallest_path_build(graph, origin, target, result_size);
}

static
void node_foreach_bfs(struct graph* graph, struct node* node, uint8_t* visited_nodes, void(entry_consumer)(struct graph* context, struct node* current, struct node* previous)) {
    if (node->children_list) {
        struct list* current_list = node->children_list;

        while (1) {
            if (!visited_nodes[current_list->value->id]) {
                entry_consumer(graph, current_list->value, node);
                visited_nodes[current_list->value->id] = 1;
            }

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
        }

        current_list = node->children_list;

        visited_nodes[node->id] = 2;

        while (1) {
            if (visited_nodes[current_list->value->id] != 2) {
                node_foreach_bfs(graph, current_list->value, visited_nodes, entry_consumer);
                visited_nodes[current_list->value->id] = 2;
            }

            if (!current_list->next) {
                break;
            }

            current_list = current_list->next;
        }
    }
}

void graph_foreach_bfs(struct graph *graph, struct node* origin, void(entry_consumer)(struct graph* context, struct node* current, struct node* previous)) {
    graph_alloc_visited_nodes(graph);

    entry_consumer(graph, origin, NULL);
    graph->visited_nodes[origin->id] = 1;

    node_foreach_bfs(graph, origin, graph->visited_nodes, entry_consumer);
}