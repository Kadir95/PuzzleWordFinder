#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "assigment.h"

#define NEXT_NODE(a)    a->next

typedef struct linkedlistNode{
    char *data;
    int valid;
    struct linkedlistNode *next;
}linkedNode;

linkedNode * find_last_node(linkedNode *baseNode);
void set_linkedNode(linkedNode *target, char *word);
linkedNode * add_linkedNode(linkedNode *target);
linkedNode * create_linkedNode();
void print_linkedList(linkedNode *root);
char * get_word(linkedNode *target);


#endif // LINKEDLIST_H
