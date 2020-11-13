#include "tree.h"

#include <stdio.h>
#include <inttypes.h>


static
void entry_print(struct node* node) {
    printf("%" PRId64 "\n", node->value);
    printf("leafs: ");

    struct list* current_list = node->leafs_list;

    while (current_list) {
        printf("%" PRId64 " ", current_list->value->value);

        current_list = current_list->next;
    }

    printf("\n");
}

void tree_print(const struct node* tree) {
    node_foreach_bfs(tree, entry_print);
}
