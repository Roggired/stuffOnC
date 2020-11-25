#include "graph/graph.h"
#include "graph/graph_writer.h"

#include <stdio.h>
#include <inttypes.h>


struct graph* create_test_graph() {
    struct graph* graph = graph_create();
    struct node* node1 = node_create(graph, 1, NULL);
    struct node* node2 = node_create(graph, 2, node1);
    struct node* node3 = node_create(graph, 3, node1);
    struct node* node4 = node_create(graph, 4, node2);
    struct node* node5 = node_create(graph, 5, node4);

    return graph;
}

void test_dsf_find(struct graph* graph, entry value) {
    struct node* result = graph_find_dfs(graph, value);
    if (result) printf("Found dfs: %" PRId64 "\n", result->value);
}

void test_bfs_find(struct graph* graph, entry value) {
    struct node* result = graph_find_bfs(graph, value);
    if (result) printf("Found bfs: %" PRId64 "\n", result->value);
}

int main() {
    struct graph* graph = create_test_graph();

    graph_print(graph);

    printf("\n");

    test_dsf_find(graph, 1);
    test_dsf_find(graph, 2);
    test_dsf_find(graph, 3);
    test_dsf_find(graph, 4);
    test_dsf_find(graph, 5);

    printf("\n");

    test_bfs_find(graph, 1);
    test_bfs_find(graph, 2);
    test_bfs_find(graph, 3);
    test_bfs_find(graph, 4);
    test_bfs_find(graph, 5);

    printf("\n");

    struct node* node6 = node_create(graph, 10, graph->root_node);
    struct node* node7 = node_create(graph, 20, node6);
    struct node* node8 = node_create(graph, 30, node7);
    node_add_child(node8, graph->nodes[4]);

    graph_print(graph);

    printf("\n");

    for (size_t i = 0; i < graph->size; i++) {
        printf("%" PRId32 " ", graph->nodes[i]->id);
    }

    printf("\n");
    printf("\n");

    printf("Smallest path:" "\n");

    size_t path_size = 0;
    struct node** path = graph_find_smallest_path(graph, graph->nodes[0], graph->nodes[7], &path_size);

    if (!path) {
        printf("There is no path!\n");
    } else {
        for (size_t i = 0; i < path_size; i++) {
            printf("%" PRId32 " ", path[i]->id);
        }

        printf("\n");
    }

    printf("\n");

    for (size_t i = 0; i < graph->size; i++) {
        printf("%" PRId32 " ", graph->nodes[i]->path_length);
    }

    graph_destroy(graph);
}