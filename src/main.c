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

    graph_destroy(graph);
}