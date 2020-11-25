#include "graph.h"

#include <stdio.h>
#include <inttypes.h>


static
void entry_print(struct graph* graph, struct node* node, struct node* previous) {
    printf("Id: %" PRId32, node->id);
    printf(" value: %" PRId64 "\n", node->value);
    printf("childs: ");

    struct list* current_list = node->children_list;

    while (current_list) {
        printf("id: %" PRId32 " ", current_list->value->id);

        current_list = current_list->next;
    }

    printf("\n");
}

void graph_print(struct graph* graph) {
    graph_foreach_bfs(graph, graph->root_node, entry_print);
}
