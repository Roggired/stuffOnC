// Решаемая задача: поиск в глубину и поиск в ширину на дереве.
// Нужно реализовать граф. Вершина может иметь любое число соседей.
// Дерево заведомо без циклов.

// Добавить обработку циклов

#include "tree/tree.h"
#include "tree/tree_writer.h"

#include <stdio.h>
#include <inttypes.h>


struct node* create_test_tree() {
    struct node* tree = node_create(1);
    struct node* node2 = node_create(2);
    struct node* node3 = node_create(3);
    struct node* node4 = node_create(4);
    struct node* node5 = node_create(5);
    node_add_leaf(tree, node2);
    node_add_leaf(tree, node3);
    node_add_leaf(node2, node4);
    node_add_leaf(node4, node5);

    return tree;
}

void test_dsf_find(struct node* tree, entry value) {
    struct node* result = node_find_dfs(tree, value);
    if (result) printf("%" PRId64 "\n", result->value);
}

void test_bfs_find(struct node* tree, entry value) {
    struct node* result = node_find_bfs(tree, value);
    if (result) printf("%" PRId64 "\n", result->value);
}

int main() {
    struct node* tree = create_test_tree();

    tree_print(tree);

    printf("\n");

    test_dsf_find(tree, 1);
    test_dsf_find(tree, 2);
    test_dsf_find(tree, 3);
    test_dsf_find(tree, 4);
    test_dsf_find(tree, 5);

    printf("\n");

    test_bfs_find(tree, 1);
    test_bfs_find(tree, 2);
    test_bfs_find(tree, 3);
    test_bfs_find(tree, 4);
    test_bfs_find(tree, 5);

    node_destroy(tree);
}