#include "graph.h"

#include <stdio.h>
#include <inttypes.h>


static
void entry_print(struct node* node) {
    printf("%" PRId64 "\n", node->value);
    printf("childs: ");

    struct list* current_list = node->children_list;

    while (current_list) {
        printf("%" PRId64 " ", current_list->value->value);

        current_list = current_list->next;
    }

    printf("\n");
}

void graph_print(struct graph* graph) {
    graph_foreach_bfs(graph, entry_print);
}
