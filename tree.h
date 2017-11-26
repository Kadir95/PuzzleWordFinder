#ifndef TREE_H
#define TREE_H

#define TEST    0

#include "assigment.h"

typedef struct tree_struct{
    char data;
    int valid;
    unsigned int child_num;
    struct tree_struct **nextNodeList;
}treeNode;

treeNode * create_treeNode();
treeNode * add_treeNode(treeNode *target);
treeNode * find_treeNode(treeNode *target, char finding_char);
treeNode * go_to_treeNode(treeNode *target, int *road, int size);
void add_word_to_tree(const treeNode *root, char *word);
void print_child_nodes(treeNode *target);
char * create_a_word(treeNode *target, int *road, int size);
int is_it_a_valid_word(const treeNode *root, char *word);

#endif // TREE_H
